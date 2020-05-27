#pragma once
#include "Bonus.h"
class ChangeTrajectoryBonus : public Bonus {
private:
    QColor _specColor = QColor(0, 255, 0, 127);
public:
    ChangeTrajectoryBonus(QGraphicsItem* parent, QPointF& position);
    void effect(GameArea* area) override;
};

