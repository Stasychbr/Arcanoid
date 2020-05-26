#include "StickToPlatform.h"

StickToPlatform::StickToPlatform(QGraphicsItem* parent, QPointF& position): Bonus(parent, position) {
    _numberOfExecs = _specNumberOfExecs;
    _color = _specColor;
    _type = _specType;
}

void StickToPlatform::effect(GameArea* area) {
    area->ball()->stop();
    area->ball()->stickToPlatform(area->platform());
    _numberOfExecs--;
}
