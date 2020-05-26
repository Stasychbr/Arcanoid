#include "BottomBlock.h"
#include <QPainter>

BottomBlock::BottomBlock(QGraphicsItem* parent, int height, int width, QPointF& position):Block(parent, height, width) {
    setPos(position);
    _hp = 1;
    _hasBonus = false;
}

void BottomBlock::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(QColor(155, 0, 25, 127));
    painter->drawRect(boundingRect());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
