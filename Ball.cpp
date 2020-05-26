#include "Ball.h"
#include <QPainter>
#include <cmath>

#define M_PI 3.14159265358979323846


Ball::Ball(QGraphicsItem* parent, QPointF& startPosition) {
    setParentItem(parent);
    setPos(startPosition);
}

Ball::~Ball() {
}

int Ball::radius() {
    return _radius;
}

void Ball::stickToPlatform(Platform* platform) {
    setParentItem(platform);
    setPos(QPointF(0, -platform->height() / 2 - radius()));
}

void Ball::launch(QGraphicsItem* gameArea) {
    if (_speed == 0) {
        QPointF newPos = mapToItem(gameArea, pos());
        setParentItem(gameArea);
        setPos(newPos);
        _angle = M_PI / 2;
        _speed = _startSpeed;
    }
}

bool Ball::falseSignal(CollideSide side) {
    if (side == CollideSide::UP && _angle < 0) {
        return true;
    }
    else if ((side == CollideSide::DOWN || side == CollideSide::PLATFORM) && _angle > 0) {
        return true;
    }
    else if (side == CollideSide::RIGHT && (_angle < -M_PI / 2 || _angle > M_PI / 2)) {
        return true;
    }
    else if (side == CollideSide::LEFT && _angle < M_PI / 2 && _angle > -M_PI / 2) {
        return true;
    }
    else {
        return false;
    }
}

bool Ball::changeDirection(CollideSide side, double platformPlace) {
    if (falseSignal(side)) {
        return false;
    }
    if (side == CollideSide::UP || side == CollideSide::DOWN) {
        _angle *= -1;
    }
    else if (side == CollideSide::PLATFORM) {
        _angle *= -1;
        _angle -= _platformCoef * platformPlace;
    }
    else {
        _angle = M_PI - _angle;
    }
    if (_angle > M_PI) {
        _angle -= 2 * M_PI;
    }
    if (_angle < -M_PI) {
        _angle += 2 * M_PI;
    }
    return true;
}

void Ball::move() {
    moveBy(_speed * cos(_angle), -_speed * sin(_angle));
}

void Ball::stop() {
    _speed = 0;
}

void Ball::speedUp() {
    if (_speed < _maxSpeed) {
        _speed++;
    }
}

void Ball::reduceSpeed() {
    if (_speed > _minSpeed) {
        _speed--;
    }
}

QPainterPath Ball::shape() const {
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

QRectF Ball::boundingRect() const {
    return QRectF(-_radius, -_radius, 2 * _radius, 2 * _radius);
}

void Ball::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(boundingRect());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
