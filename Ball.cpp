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

void Ball::changeDirection(CollideSide side) {
    if (side == CollideSide::UP) {
        _angle *= -1;
    }
    else {
        _angle = M_PI - _angle;
    }
}

void Ball::move() {
    double cx = x();
    double cy = y();
    double dx = cx + _currentSpeed * cos(_angle);
    double dy = cy - _currentSpeed * sin(_angle);
    setX(dx);
    setY(dy);
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
