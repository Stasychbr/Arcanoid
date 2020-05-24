#pragma once

#include <QGraphicsItem>

class Block : public QGraphicsItem {
private:
    static const int _maxHp = 4;

    int _width;
    int _height;
    int _hp;

public:
    //int _posX; //debug
    //int _posY; // debug
    Block(QGraphicsItem* parent, int height, int width);
    ~Block();

    int height();
    int width();
    int hp();

    void setWidth(int width);
    void setHeight(int height);
    
    void hit();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};
