#pragma once

#include <QGraphicsItem>
#include "Platform.h"

class Ball : public QGraphicsItem {
public:
    enum class CollideSide {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        PLATFORM,
    };
private:
    static const int _radius = 10;
    static const int _speed = 4.0;
    static const int _maxSpeed = 2 * _speed;
    const double _platformCoef = 0.4;
    
    double _currentSpeed = 0;
    double _angle = 0; // from -pi to pi

    bool falseSignal(CollideSide side);
public:
    Ball(QGraphicsItem* parent, QPointF& startPosition);
    ~Ball();

    static int radius();

    void stickToPlatform(Platform* platform);
    void launch(QGraphicsItem* gameArea);
    bool changeDirection(CollideSide side, double platformPlace = 0);
    void move();
    void stop();
    void speedUp();

    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};
