#pragma once

#include <QGraphicsObject>
#include "Platform.h"
#include "Ball.h"
#include "Grid.h"

class GameArea : public QGraphicsObject {

    Q_OBJECT

private:
    const int _blocksMargin = 4 * Ball::radius();
    const double _blocksHeightCoef = 0.4; // coef * area.height()

    Platform* _platform = nullptr;
    Ball* _ball = nullptr;
    Grid* _blocksGrid = nullptr;
    QRectF _area;

    static const int _timerPeriod = 16; //msec
    int _timerID = 0;

    void timerEvent(QTimerEvent* e) override;
    void managePlatform();
    void manageBall();
    void handleBallPlatformCollision();
    void startNewLife();
public:
    GameArea(QRectF& area);
    ~GameArea();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};
