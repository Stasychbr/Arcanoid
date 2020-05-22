#pragma once

#include <QGraphicsItem>

class Block : public QGraphicsItem {
private:
    int _width;
    int _height;
public:
    Block(QGraphicsItem* parent, int height, int width);
    ~Block();

    void setWidth(int width);
    void setHeight(int height);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};
