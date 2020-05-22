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

void Ball::launch() {
    if (_currentSpeed == 0) {
        _angle = M_PI / 2;
        _currentSpeed = _speed;
    }
}

void Ball::changeDirection(CollideSide side, double platformPlace) {
    if (side == CollideSide::UP) {
        _angle *= -1;
    }
    else if (side == CollideSide::PLATFORM) {
        if (_angle >= 0) {
            return;
        }
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
}

void Ball::move() {
    moveBy(_currentSpeed * cos(_angle), -_currentSpeed * sin(_angle));
}

void Ball::stop() {
    _currentSpeed = 0;
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
