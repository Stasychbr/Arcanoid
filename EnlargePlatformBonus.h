#pragma once
#include "Bonus.h"
class EnlargePlatformBonus : public Bonus {
private:
    QColor _specColor = QColor(255, 0, 0, 127);
public:
    EnlargePlatformBonus(QGraphicsItem* parent, QPointF& position);
    void effect(GameArea* area) override;
};

