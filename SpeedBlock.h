#pragma once
#include "Block.h"
class SpeedBlock : public Block {
private:
    static const int _specScoreForHit = 2;
public:
    SpeedBlock(QGraphicsItem* parent, int height, int width);
    int hit(Ball* ball) override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};

