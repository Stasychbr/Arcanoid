#pragma once

#include <QGraphicsItem>
#include <vector>
#include "Block.h"
#include "SpeedBlock.h"
#include "UnbreakableBlock.h"

class Grid : public QGraphicsItem {
    static const int _horSize = 5;
    static const int _vertSize = 8;

    QRectF _area;

    std::vector <std::vector<Block*>> _blocks;

    Block* generateBlock(int blockHeight, int blockWidth);
public:
    Grid(QGraphicsItem* parent, QRectF& area);
    ~Grid();

    Block* ballCollision(QGraphicsItem* ball);
    QPointF findBonusPlace(Block* block);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};
