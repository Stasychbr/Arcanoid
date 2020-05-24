#include "GameArea.h"
#include <QKeyEvent>
#include <windows.h>

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

QRectF GameArea::boundingRect() const {
    return _area;
}

void GameArea::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
}

void GameArea::timerEvent(QTimerEvent* e) {
    managePlatform();
    manageBall();
    manageCollisions();
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
        double dx = _ball->x() - blockCoords.x();//_ball->x() - collidingBlock->x();
        double dy = _ball->y() - blockCoords.y();//_ball->y() - collidingBlock->y();
        if (dy > -collidingBlock->height() / 2 && dy < collidingBlock->height() / 2) {
            if (dx < 0/*-collidingBlock->width() / 2*/) {
                _ball->changeDirection(Ball::CollideSide::RIGHT);
            }
            else {
                _ball->changeDirection(Ball::CollideSide::LEFT);
            }
        }
        else if (dx > -collidingBlock->width() / 2 && dx < collidingBlock->width() / 2) {
            if (dy < 0) {
                _ball->changeDirection(Ball::CollideSide::DOWN);
            }
            else {
                _ball->changeDirection(Ball::CollideSide::UP);
            }
        }
    }
}

void GameArea::startNewLife() {
    _platform->setPos(QPointF(_area.width() / 2, _area.height() - 3 * _platform->height() / 2));
    _ball->setPos(QPointF(_platform->x(), _platform->y() - _platform->height() / 2 - _ball->radius()));
    _ball->stop();
    _ball->stickToPlatform(_platform);
}