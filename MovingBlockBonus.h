#pragma once
#include "Bonus.h"
class MovingBlockBonus : public Bonus {
private:
    QColor _specColor = QColor(0, 0, 255, 125);
public:
    MovingBlockBonus(QGraphicsItem* parent, QPointF& position);
    void effect(GameArea* area) override;
};

