#include "MovingBlock.h"
#include <QPainter>

MovingBlock::MovingBlock(QGraphicsItem* parent, int height, int width, QPointF& startPosition, QPointF& endPosition):Block(parent, height, width) {
    _hp = _specHp;
    _anim = new QPropertyAnimation((QGraphicsObject*)this, "pos");
    _anim->setStartValue(startPosition);
    _anim->setEndValue(startPosition);
    _anim->setDuration(_animDuration);
    _anim->setKeyValueAt(0.5, endPosition);
    _anim->setLoopCount(-1);
    _anim->start();
}

MovingBlock::~MovingBlock() {
    delete _anim;
}

void MovingBlock::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(QColor(255, 255, 0, 127 + 127 / _specHp * _hp));
    painter->drawRect(Block::boundingRect());
}
