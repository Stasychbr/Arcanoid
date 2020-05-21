#pragma once

#include <QGraphicsObject>
#include "Platform.h"
#include "Ball.h"

class GameArea : public QGraphicsObject {

    Q_OBJECT

private:
    Platform* _platform = nullptr;
    Ball* _ball = nullptr;
    QRectF _area;

    static const int _timerPeriod = 20; //msec
    int _timerID = 0;

public:
    GameArea(QRectF& area);
    ~GameArea();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void timerEvent(QTimerEvent* e) override;
};
