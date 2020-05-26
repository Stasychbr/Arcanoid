#pragma once
#include "Block.h"

class BottomBlock : public Block {
public:
    BottomBlock(QGraphicsItem* parent, int height, int width, QPointF& position);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};

