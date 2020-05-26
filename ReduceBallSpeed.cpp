#include "ReduceBallSpeed.h"

ReduceBallSpeed::ReduceBallSpeed(QGraphicsItem* parent, QPointF& position):Bonus(parent, position) {
    _color = _specColor;
}

void ReduceBallSpeed::effect(GameArea* area) {
    area->ball()->reduceSpeed();
}
