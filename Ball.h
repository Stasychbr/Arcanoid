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
    static const int _startSpeed = 4;
    static const int _maxSpeed = 2 * _startSpeed;
    static const int _minSpeed = _startSpeed / 2;
    const double _platformCoef = 0.4;
    
    QColor _color = Qt::yellow;
    double _speed = 0;
    double _angle = 0; // from -pi to pi

    bool falseSignal(CollideSide side);
    void normaliseAngle();
public:
    Ball(QGraphicsItem* parent, QPointF& startPosition);
    Ball(Ball* parentBall);
    ~Ball();

    static int radius();

    void stickToPlatform(Platform* platform);
    void launch(QGraphicsItem* gameArea);
    bool changeDirection(CollideSide side, double platformPlace = 0);
    void move();
    void stop();
    void speedUp();
    void reduceSpeed();
    void changeTrajectory(double deltaAngle);
    void ballCollision(Ball* anotherBall);
    void makeMainBall();

    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};
