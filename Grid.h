#pragma once

#include <QGraphicsItem>
#include <vector>
#include "Block.h"

class Grid : public QGraphicsItem {
    static const int _horSize = 5;
    static const int _vertSize = 8;

    QRectF _area;

    std::vector <std::vector<Block*>> _blocks;
public:
    Grid(QGraphicsItem* parent, QRectF& area);
    ~Grid();
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};
