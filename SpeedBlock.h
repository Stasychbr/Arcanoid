#pragma once
#include "Block.h"
class SpeedBlock : public Block {
public:
    SpeedBlock(QGraphicsItem* parent, int height, int width);
    void hit(Ball* ball) override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};

