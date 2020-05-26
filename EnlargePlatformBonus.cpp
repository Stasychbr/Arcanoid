#include "EnlargePlatformBonus.h"

EnlargePlatformBonus::EnlargePlatformBonus(QGraphicsItem* parent, QPointF& position):Bonus(parent, position) {
    _color = _specColor;
}

void EnlargePlatformBonus::effect(GameArea* area) {
    area->platform()->enlarge();
    area->platform()->update();
}

