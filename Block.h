#pragma once

#include <QGraphicsItem>
#include "Ball.h"

class Block : public QGraphicsItem {
protected:
    static const int _maxHp = 4;
    static const int _bonusChance = 2; // 1/n
    int _width;
    int _height;
    int _hp;
    bool _hasBonus;
public:
    //int _posX; //debug
    //int _posY; // debug
    Block(QGraphicsItem* parent, int height, int width);
    virtual ~Block();

    int height();
    int width();
    int hp();
    bool hasBonus();
    
    virtual void hit(Ball* ball);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};
