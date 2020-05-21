#pragma once

#include <QGraphicsItem>

class Ball : public QGraphicsItem {
private:
    static const int _radius = 10;
    static const int _speed = 2.0;
    
    double _currentSpeed = 0;
    double _angle = 0;
public:
    enum class CollideSide {
        UP,
        LEFT,
        RIGHT,
    };

    Ball(QGraphicsItem* parent, QPointF& startPosition);
    ~Ball();

    int radius();

    void launch();
    void changeDirection(CollideSide side);
    void move();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};
