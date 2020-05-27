#include "ChangeTrajectoryBonus.h"
#include <QRandomGenerator>
#include <random>

#define M_PI 3.14159265358979323846

ChangeTrajectoryBonus::ChangeTrajectoryBonus(QGraphicsItem* parent, QPointF& position): Bonus(parent, position) {
    _color = _specColor;
}

void ChangeTrajectoryBonus::effect(GameArea* area) {
    std::uniform_real_distribution<double> distr(-M_PI / 2, M_PI / 2);
    area->ball()->changeTrajectory(distr(*QRandomGenerator::global()));
}
