#include "Block.h"
#include <QPainter>
#include <random>
#include <QRandomGenerator>

Block::Block(QGraphicsItem* parent, int height, int width) {
    setParentItem(parent);
    _height = height;
    _width = width;
    _hp = QRandomGenerator::global()->bounded(1, _maxHp + 1);
}

Block::~Block() {

}

int Block::height() {
    return _height;
}

int Block::width() {
    return _width;
}

int Block::hp() {
    return _hp;
}

void Block::setWidth(int width) {
    _width = width;
}

void Block::setHeight(int height) {
   _height = height;
}

void Block::hit() {
    _hp--;
    update();
    if (_hp == 0) {
        hide();
    }
}

QRectF Block::boundingRect() const {
    return QRectF(-_width / 2, -_height / 2, _width, _height);
}

void Block::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    int green = 255  / _maxHp * _hp;
    int red = _hp > _maxHp / 2 ? 0 : 255;
    painter->setBrush(QColor(red, green, 0));
    painter->drawRect(boundingRect());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
