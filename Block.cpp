#include "Block.h"
#include <QPainter>

Block::Block(QGraphicsItem* parent, int height, int width) {
    setParentItem(parent);
    _height = height;
    _width = width;
}

Block::~Block() {

}

int Block::height() {
    return _height;
}

int Block::width() {
    return _width;
}

void Block::setWidth(int width) {
    _width = width;
}

void Block::setHeight(int height) {
   _height = height;
}

QRectF Block::boundingRect() const {
    return QRectF(-_width / 2, -_height / 2, _width, _height);
}

void Block::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(Qt::green);
    painter->drawRect(boundingRect());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
