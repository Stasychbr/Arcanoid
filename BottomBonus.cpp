#include "BottomBonus.h"

BottomBonus::BottomBonus(QGraphicsItem* parent, QPointF& position): Bonus(parent, position) {
    _color = _specColor;
}

void BottomBonus::effect(GameArea* area) {
    area->spawnBottomBlock();
}
