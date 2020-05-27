#include "SecondBallBonus.h"

SecondBallBonus::SecondBallBonus(QGraphicsItem* parent, QPointF& position) :Bonus(parent, position) {
    _color = _specColor;
}

void SecondBallBonus::effect(GameArea* area) {
    area->spawnSecondBall();
}
