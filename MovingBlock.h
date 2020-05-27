#pragma once
#include "Block.h"
#include <QPropertyAnimation>
class MovingBlock : public Block {
private:
    QPropertyAnimation* _anim = nullptr;
    static const int _specHp = 3;
    static const int _animDuration = 2000;
public:
    MovingBlock(QGraphicsItem* parent, int height, int width, QPointF& startPosition, QPointF& endPosition);
    ~MovingBlock();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};

