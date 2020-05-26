#include "GameArea.h"
#include <QKeyEvent>
#include <windows.h>
#include <random>
#include <QRandomGenerator>
#include "EnlargePlatformBonus.h"
#include "ReduceBallSpeed.h"

GameArea::GameArea(QRectF& area) {
    _area = area;
    _platform = new Platform(this, QPointF(_area.width() / 2, _area.height() - 3 * _platform->height() / 2));
    _ball = new Ball(_platform, QPointF(0, -_platform->height() / 2 - _ball->radius()));
    _blocksGrid = new Grid(this, QRectF(_blocksMargin, _blocksMargin, area.width() - 2 * _blocksMargin, _blocksHeightCoef * area.height()));
    _blocksGrid->setPos(_blocksMargin, _blocksMargin);
    _timerID = startTimer(_timerPeriod);
}

GameArea::~GameArea() {
    killTimer(_timerID);
    delete _blocksGrid;
    delete _ball;
    delete _platform;
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
    manageBall();
    manageCollisions();
    manageBonuses();
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

void GameArea::manageBall() {
    _ball->move();
    if (GetAsyncKeyState(VK_SPACE)) {
        _ball->launch(this);
    }
    if (_ball->x() + _ball->radius() >= _area.width()) {
        _ball->changeDirection(Ball::CollideSide::RIGHT);
    }
    if (_ball->x() - _ball->radius() <= 0) {
        _ball->changeDirection(Ball::CollideSide::LEFT);
    }
    if (_ball->y() - _ball->radius() <= 0) {
        _ball->changeDirection(Ball::CollideSide::UP);
    }
    if (_ball->y() >= _area.height()) {
        startNewLife();
    }
}

void GameArea::manageCollisions() {
    if (_platform->collidesWithItem(_ball)) {
        double platformPlace = 2 * (_ball->x() - _platform->x()) / _platform->width();
        _ball->changeDirection(Ball::CollideSide::PLATFORM, platformPlace);
    }
    Block* collidingBlock = _blocksGrid->ballCollision(_ball);
    if (collidingBlock) {
        QPointF blockCoords = mapFromItem(_blocksGrid, collidingBlock->pos());
        double dx = _ball->x() - blockCoords.x();
        double dy = _ball->y() - blockCoords.y();
        bool check = false;
        if (dx > -collidingBlock->width() / 2 && dx < collidingBlock->width() / 2) {
            if (dy < 0) {
                check = _ball->changeDirection(Ball::CollideSide::DOWN);
            }
            else {
                check = _ball->changeDirection(Ball::CollideSide::UP);
            }
        }
        else if (dy > -collidingBlock->height() / 2 && dy < collidingBlock->height() / 2) {
            if (dx < 0) {
                check = _ball->changeDirection(Ball::CollideSide::RIGHT);
            }
            else {
                check = _ball->changeDirection(Ball::CollideSide::LEFT);
            }
        }
        if (check) {
            collidingBlock->hit(_ball);
            if (collidingBlock->hasBonus()) {
                spawnBonus(collidingBlock);
            }
        }
    }
}

void GameArea::spawnBonus(Block* block) {
    std::geometric_distribution<int> blocksDistr(0.4);
    switch (blocksDistr(*QRandomGenerator::global())) {
    case 1:
        _bonuses.push_back((Bonus*)new ReduceBallSpeed(this, mapFromItem(_blocksGrid, _blocksGrid->findBonusPlace(block))));
        break;
    default:
        _bonuses.push_back((Bonus*)new EnlargePlatformBonus(this, mapFromItem(_blocksGrid, _blocksGrid->findBonusPlace(block))));
    }
}

void GameArea::manageBonuses() {
    for (auto it = _bonuses.begin(); it != _bonuses.end();) {
        auto bonus = *it;
        bonus->move();
        if (bonus->collidesWithItem(_platform)) {
            bonus->effect(this);
            it = _bonuses.erase(it);
            delete bonus;
        }
        else if (bonus->y() > _area.height() + bonus->size()) {
            it = _bonuses.erase(it);
            delete bonus;
        }
        else {
            ++it;
        }
    }
}

void GameArea::startNewLife() {
    _platform->setPos(QPointF(_area.width() / 2, _area.height() - 3 * _platform->height() / 2));
    _ball->setPos(QPointF(_platform->x(), _platform->y() - _platform->height() / 2 - _ball->radius()));
    _ball->stop();
    _ball->stickToPlatform(_platform);
}
