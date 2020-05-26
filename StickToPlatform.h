#pragma once
#include "Bonus.h"
class StickToPlatform : public Bonus {
private:
    static const int _specNumberOfExecs = 3;
    QColor _specColor = QColor(255, 127, 0, 127);
    Bonus::BonusType _specType = Bonus::BonusType::AFTER_PLATFORM_HIT;
public:
    StickToPlatform(QGraphicsItem* parent, QPointF& position);
    void effect(GameArea* area) override;
};

