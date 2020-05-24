#pragma once

#include <QGraphicsItem>

class Block : public QGraphicsItem {
private:
    int _width;
    int _height;

public:
    int _posX; //debug
    int _posY; // debug
    Block(QGraphicsItem* parent, int height, int width);
    ~Block();

    int height();
    int width();

    void setWidth(int width);
    void setHeight(int height);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};
