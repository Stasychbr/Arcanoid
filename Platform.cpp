#include "Platform.h"
#include <QPainter>

Platform::Platform(QGraphicsItem* parent, QPointF& startPos) {
    setParentItem(parent);
    setPos(startPos);
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
    setX(x() + dx);
}

void Platform::moveLeft() {
    setX(x() - dx);
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
