#pragma once

#include <QGraphicsItem>
#include <vector>
#include "Block.h"
#include "SpeedBlock.h"

class Grid : public QGraphicsItem {
    static const int _horSize = 5;
    static const int _vertSize = 8;

    static const int _blockTypes = 2;
    static const int _speedBlockChance = 10; // 1/n

    QRectF _area;

    std::vector <std::vector<Block*>> _blocks;

    Block* generateBlock(int blockHeight, int blockWidth);
public:
    Grid(QGraphicsItem* parent, QRectF& area);
    ~Grid();

    Block* ballCollision(QGraphicsItem* ball);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};
