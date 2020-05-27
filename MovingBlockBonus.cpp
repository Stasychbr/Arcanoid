#include "MovingBlockBonus.h"

MovingBlockBonus::MovingBlockBonus(QGraphicsItem* parent, QPointF& position):Bonus(parent, position) {
    _color = _specColor;
}

void MovingBlockBonus::effect(GameArea* area) {
    //area->spawnMovingBlock();
}
