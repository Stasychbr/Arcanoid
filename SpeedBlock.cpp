#include "SpeedBlock.h"
#include <QPainter>

SpeedBlock::SpeedBlock(QGraphicsItem* parent, int height, int width):Block(parent, height, width) {
    _hasBonus = false;
    _scoreForHit = _specScoreForHit;
}

int SpeedBlock::hit(Ball* ball) {
    ball->speedUp();
    return Block::hit(ball);
}

void SpeedBlock::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    int blue = 255 / _maxHp * _hp;
    int green = _hp > _maxHp / 2 ? 125 : 0;
    painter->setBrush(QColor(0, green, blue));
    painter->drawRect(boundingRect());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
