#include "Platform.h"
#include <QPainter>

Platform::Platform(QGraphicsItem* parent, QPointF& startPos) {
    setParentItem(parent);
    setPos(startPos);
    _horSize = _startHorSize;
}

Platform::~Platform() {

}

int Platform::width() {
    return _horSize;
}

int Platform::height() {
    return _vertSize;
}

void Platform::moveRight() {
    setX(x() + _speed);
}

void Platform::moveLeft() {
    setX(x() - _speed);
}

void Platform::enlarge() {
    if (_horSize < _maxHorSize) {
        _horSize += _enlargeSize;
    }
}

void Platform::shorten() {
    _horSize -= _cutSize;
}

bool Platform::tooShort() {
    return _horSize < _cutSize;
}

QRectF Platform::boundingRect() const {
    return QRectF(-_horSize / 2, -_vertSize / 2, _horSize, _vertSize);
}

void Platform::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(Qt::red);
    painter->drawRect(boundingRect());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
