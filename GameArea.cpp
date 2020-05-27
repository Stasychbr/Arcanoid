#include "GameArea.h"
#include <QKeyEvent>
#include <windows.h>
#include <random>
#include <QRandomGenerator>
#include <QPainter>
#include <QMessageBox>
#include "EnlargePlatformBonus.h"
#include "ReduceBallSpeed.h"
#include "StickToPlatform.h"
#include "BottomBlock.h"
#include "BottomBonus.h"
#include "ChangeTrajectoryBonus.h"
#include "MovingBlock.h"
#include "SecondBallBonus.h"

GameArea::GameArea(QRectF& area) {
    _area = area;
    _platform = new Platform(this, QPointF(_area.width() / 2, _area.height() - 3 * _platform->height() / 2));
    _ball = new Ball(_platform, QPointF(0, -_platform->height() / 2 - _ball->radius()));
    _blocksGrid = new Grid(this, QRectF(_blocksMargin, _blocksMargin, area.width() - 2 * _blocksMargin, _blocksHeightCoef * area.height()));
    _blocksGrid->setPos(_blocksMargin, _blocksMargin);
    _timerID = startTimer(_timerPeriod);
}

GameArea::~GameArea() {
    delete _blocksGrid;
    delete _ball;
    delete _platform;
    delete _bonusBall;
    deleteBonuses();
    deleteBonusBlocks();
}

Platform* GameArea::platform() {
    return _platform;
}

Ball* GameArea::ball() {
    return _ball;
}

QRectF GameArea::boundingRect() const {
    return _area;
}

void GameArea::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
}

void GameArea::timerEvent(QTimerEvent* e) {
    managePlatform();
    manageBall(_ball);
    manageCollisions(_ball);
    if (_bonusBall) {
        manageBall(_bonusBall);
        manageCollisions(_bonusBall);
    }
    manageBallsCollisions();
    manageBonuses();
    manageFallOut();
}

void GameArea::managePlatform() {
    if (GetAsyncKeyState(VK_LEFT)) {
        if (_platform->x() - _platform->width() / 2 >= 0) {
            _platform->moveLeft();
        }
    }
    if (GetAsyncKeyState(VK_RIGHT)) {
        if (_platform->x() + _platform->width() / 2 <= _area.width()) {
            _platform->moveRight();
        }
    }
}

void GameArea::manageBall(Ball* ball) {
    ball->move();
    if (GetAsyncKeyState(VK_SPACE)) {
        ball->launch(this);
    }
    if (ball->x() + ball->radius() >= _area.width()) {
        ball->changeDirection(Ball::CollideSide::RIGHT);
    }
    if (ball->x() - ball->radius() <= 0) {
        ball->changeDirection(Ball::CollideSide::LEFT);
    }
    if (ball->y() - ball->radius() <= 0) {
        ball->changeDirection(Ball::CollideSide::UP);
    }
}

void GameArea::manageFallOut() {
    if (_ball->y() >= _area.height()) {
        if (!_bonusBall) {
            startNewLife();
        }
        else {
            delete _ball;
            _ball = _bonusBall;
            _bonusBall = nullptr;
            _ball->makeMainBall();
        }
    }
    else if (_bonusBall && _bonusBall->y() >= _area.height()) {
        delete _bonusBall;
        _bonusBall = nullptr;
    }
}

void GameArea::manageCollisions(Ball* ball) {
    if (_platform->collidesWithItem(ball)) {
        double platformPlace = 2 * (ball->x() - _platform->x()) / _platform->width();
        ball->changeDirection(Ball::CollideSide::PLATFORM, platformPlace);
        doHitToPlatformQuery();
    }
    Block* collidingBlock = _blocksGrid->ballCollision(ball);
    if (!collidingBlock) {
        collidingBlock = checkBonusBlocksCollisions(ball);
    }
    if (collidingBlock) {
        QPointF blockCoords = mapFromItem(_blocksGrid, collidingBlock->pos());
        double dx = ball->x() - blockCoords.x();
        double dy = ball->y() - blockCoords.y();
        bool check = false;
        if (dx >= -collidingBlock->width() / 2 - Ball::radius() && dx <= collidingBlock->width() / 2 + Ball::radius()) {
            if (dy < 0) {
                check = ball->changeDirection(Ball::CollideSide::DOWN);
            }
            else {
                check = ball->changeDirection(Ball::CollideSide::UP);
            }
        }
        else if (dy >= -collidingBlock->height() / 2 - Ball::radius() && dy <= collidingBlock->height() / 2 + Ball::radius()) {
            if (dx < 0) {
                check = ball->changeDirection(Ball::CollideSide::RIGHT);
            }
            else {
                check = ball->changeDirection(Ball::CollideSide::LEFT);
            }
        }
        if (check) {
            _score += collidingBlock->hit(ball);
            if (_blocksGrid->isAllDestroyed()) {
                victory();
            }
            if (collidingBlock->hasBonus()) {
                spawnBonus(collidingBlock);
            }
        }
    }
}

void GameArea::manageBallsCollisions() {
    if (_bonusBall) {
        if (_ball->collidesWithItem(_bonusBall)) {
            _ball->ballCollision(_bonusBall);
        }
    }
}

void GameArea::spawnBonus(Block* block) {
    std::geometric_distribution<int> blocksDistr(0.5);
    switch (blocksDistr(*QRandomGenerator::global())) {
    case 1:
        _bonuses.push_back((Bonus*)new SecondBallBonus(this, mapFromItem(_blocksGrid, _blocksGrid->findBonusPlace(block))));
        break;
    case 2:
        _bonuses.push_back((Bonus*)new ChangeTrajectoryBonus(this, mapFromItem(_blocksGrid, _blocksGrid->findBonusPlace(block))));
        break;
    case 3:
        _bonuses.push_back((Bonus*)new BottomBonus(this, mapFromItem(_blocksGrid, _blocksGrid->findBonusPlace(block))));
        break;
    case 4:
        _bonuses.push_back((Bonus*)new ReduceBallSpeed(this, mapFromItem(_blocksGrid, _blocksGrid->findBonusPlace(block))));
        break;
    case 5:
        _bonuses.push_back((Bonus*)new StickToPlatform(this, mapFromItem(_blocksGrid, _blocksGrid->findBonusPlace(block))));
        break;
    default:
        _bonuses.push_back((Bonus*)new EnlargePlatformBonus(this, mapFromItem(_blocksGrid, _blocksGrid->findBonusPlace(block))));
    }
}

void GameArea::spawnBottomBlock() {
    Block* block = new BottomBlock(this, _platform->height(), _area.width() + 10, QPointF(_area.width() / 2, _area.height()));
    _bonusBlocks.push_back(block);
}

void GameArea::spawnSecondBall() {
    if (!_bonusBall) {
        _bonusBall = new Ball(_ball);
    }
}

//void GameArea::spawnMovingBlock() {
//    QPointF start, end;
//    int blockHeight, blockWidth;
//    if (_blocksGrid->findFreeSpace(start, end)) {
//        start = mapFromItem(_blocksGrid, start);
//        end = mapFromItem(_blocksGrid, end);
//        _blocksGrid->blockSize(blockHeight, blockWidth);
//        _bonusBlocks.push_back(new MovingBlock(this, blockHeight, blockWidth, start, end));
//    }
//}



Block* GameArea::checkBonusBlocksCollisions(Ball* ball) {
    for (auto it = _bonusBlocks.begin(); it != _bonusBlocks.end();) {
        auto block = *it;
        if (block->hp() == 0) {
            it = _bonusBlocks.erase(it);
            delete block;
        }
        else if (block->collidesWithItem(ball)) {
            return block;
        }
        else {
            it++;
        }
    }
    return nullptr;
}

void GameArea::gameOver() {
    killTimer(_timerID);
    QMessageBox message;
    QString scoreString;
    scoreString.setNum(_score);
    message.setWindowTitle("You lose :(");
    message.setText("Your score " + scoreString);
    message.resize({ 400, 400 });
    message.exec();
}

void GameArea::victory() {
    killTimer(_timerID);
    QMessageBox message;
    QString scoreString;
    scoreString.setNum(_score);
    message.setWindowTitle("You won!");
    message.setText("Your score " + scoreString);
    message.resize({ 400, 400 });
    message.exec();
}

void GameArea::deleteBonuses() {
    for (auto it = _bonuses.begin(); it != _bonuses.end();) {
        delete* it;
        it = _bonuses.erase(it);
    }
}

void GameArea::deleteBonusBlocks() {
    for (auto it = _bonusBlocks.begin(); it != _bonusBlocks.end(); it++) {
        delete* it;
    }
}

void GameArea::manageBonuses() {
    for (auto it = _bonuses.begin(); it != _bonuses.end();) {
        auto bonus = *it;
        bonus->move();
        if (bonus->collidesWithItem(_platform)) {
            if (bonus->type() == Bonus::BonusType::INSTANT) {
                bonus->effect(this);
                it = _bonuses.erase(it);
                delete bonus;
            }
            else {
                _hitToPlatformQuery.push_back(bonus);
                it = _bonuses.erase(it);
                bonus->hide();
            }
        }
        else if (bonus->y() > _area.height() + bonus->size()) {
            it = _bonuses.erase(it);
            delete bonus;
        }
        else {
            it++;
        }
    }
}

void GameArea::startNewLife() {
    deleteBonuses();
    _platform->setPos(QPointF(_area.width() / 2, _area.height() - 3 * _platform->height() / 2));
    _platform->shorten();
    if (_platform->tooShort()) {
        gameOver();
    }
    _ball->setPos(QPointF(_platform->x(), _platform->y() - _platform->height() / 2 - _ball->radius()));
    _ball->stop();
    _ball->stickToPlatform(_platform);
}

void GameArea::doHitToPlatformQuery() {
    for (auto it = _hitToPlatformQuery.begin(); it != _hitToPlatformQuery.end();) {
        auto bonus = *it;
        if (bonus->numberOfExecutions() > 0) {
            bonus->effect(this);
            it++;
        }
        else {
            it = _hitToPlatformQuery.erase(it);
            delete bonus;
        }
    }
}