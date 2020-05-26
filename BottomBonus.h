#pragma once
#include "Bonus.h"
class BottomBonus : public Bonus {
private:
    QColor _specColor = QColor(255, 50, 255, 125);
public:
    BottomBonus(QGraphicsItem* parent, QPointF& position);
    void effect(GameArea* area) override;
};

