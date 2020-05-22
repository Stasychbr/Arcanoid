#pragma once

#include <QGraphicsItem>

class Ball : public QGraphicsItem {
private:
    static const int _radius = 10;
    static const int _speed = 4.0;
    const double _platformCoef = 0.4;
    
    double _currentSpeed = 0;
    double _angle = 0; // from -pi to pi
public:
    enum class CollideSide {
        UP,
        LEFT,
        RIGHT,
        PLATFORM,
    };

    Ball(QGraphicsItem* parent, QPointF& startPosition);
    ~Ball();

    static int radius();

    void launch();
    void changeDirection(CollideSide side, double platformPlace = 0);
    void move();
    void stop();

    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};
