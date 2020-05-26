#pragma once
#include "Bonus.h"

class ReduceBallSpeed : public Bonus {
private:
    QColor _specColor = QColor(0, 255, 255, 127);
public:
    ReduceBallSpeed(QGraphicsItem* parent, QPointF& position);
    void effect(GameArea* area) override;
};

