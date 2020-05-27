#pragma once
#include "Bonus.h"
class SecondBallBonus : public Bonus {
private:
    QColor _specColor = QColor(0, 0, 255, 125);
public:
    SecondBallBonus(QGraphicsItem* parent, QPointF& position);
    void effect(GameArea* area) override;
};

