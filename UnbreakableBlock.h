#pragma once
#include "Block.h"
class UnbreakableBlock : public Block {
public:
    UnbreakableBlock(QGraphicsItem* parent, int height, int width);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};

