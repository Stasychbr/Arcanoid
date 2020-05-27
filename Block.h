#pragma once

#include <QGraphicsItem>
#include "Ball.h"
#include <QGraphicsObject>

class Block : public QGraphicsObject {
protected:
    static const int _maxHp = 4;
    static const int _bonusChance = 3; // 1/n
    int _width = 0;
    int _height = 0;
    int _hp = 0;
    int _scoreForHit = 1;
    bool _hasBonus = false;
public:
    Block(QGraphicsItem* parent, int height, int width);
    virtual ~Block();

    int height();
    int width();
    int hp();
    bool hasBonus();
    
    virtual int hit(Ball* ball);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};
