#pragma once

#include <QGraphicsItem>
#include "Ball.h"

class Block : public QGraphicsItem {
protected:
    static const int _maxHp = 4;
    int _width;
    int _height;
    int _hp;
public:
    //int _posX; //debug
    //int _posY; // debug
    Block(QGraphicsItem* parent, int height, int width);
    virtual ~Block();

    int height();
    int width();
    int hp();
    
    virtual void hit(Ball* ball);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};
