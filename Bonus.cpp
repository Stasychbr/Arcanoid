#include "Bonus.h"
#include <QPainter>

Bonus::Bonus(QGraphicsItem* parent, QPointF& position) {
    setPos(position);
    setParentItem(parent);
}

int Bonus::size() {
    return _size;
}

void Bonus::move() {
    setY(y() + _speed);
}

QRectF Bonus::boundingRect() const {
    return QRectF(-_size / 2, -_size / 2, _size, _size);
}

void Bonus::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(_color);
    painter->drawRect(boundingRect());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
