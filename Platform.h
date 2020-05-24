#pragma once

#include <QGraphicsObject>

class Platform : public QGraphicsItem {

private:
    static const int _horSize = 80;
    static const int _vertSize = 15;
    const double _speed = 3.0;

    double _posX = 0;

public:
    Platform(QGraphicsItem* parent, QPointF& startPos);
    ~Platform();

    int width();
    int height();

    void moveRight();
    void moveLeft();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};
