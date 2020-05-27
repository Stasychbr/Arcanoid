#include "UnbreakableBlock.h"
#include <limits>
#include <QPainter>

UnbreakableBlock::UnbreakableBlock(QGraphicsItem* parent, int height, int width): Block(parent, height, width) {
    _hp = INT_MAX;
    _hasBonus = false;
    _scoreForHit = 0;
}

void UnbreakableBlock::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(Qt::darkRed);
    painter->drawRect(boundingRect());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
