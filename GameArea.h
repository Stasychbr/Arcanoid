#pragma once

#include <QGraphicsObject>
#include <QGraphicsItem>
#include <list>
#include "Platform.h"
#include "Ball.h"
#include "Grid.h"
#include "Block.h"

class Bonus;

class GameArea : public QGraphicsObject {

    Q_OBJECT

private:
    const int _blocksMargin = 4 * Ball::radius();
    const double _blocksHeightCoef = 0.4; // coef * area.height()
    int _score = 0;

    QRectF _area;
    Platform* _platform = nullptr;
    Ball* _ball = nullptr;
    Ball* _bonusBall = nullptr;
    Grid* _blocksGrid = nullptr;
    std::list<Bonus*> _bonuses;
    std::list<Bonus*> _hitToPlatformQuery;
    std::list<Block*> _bonusBlocks;

    static const int _timerPeriod = 16; //msec
    int _timerID = 0;

    void timerEvent(QTimerEvent* e) override;
    void managePlatform();
    void manageBall(Ball* ball);
    void manageFallOut();
    void manageCollisions(Ball* ball);
    void manageBallsCollisions();
    void manageBonuses();
    void startNewLife();
    void doHitToPlatformQuery();
    Block* checkBonusBlocksCollisions(Ball* ball);

    void gameOver();
    void victory();

    void deleteBonuses();
    void deleteBonusBlocks();
public:
    GameArea(QRectF& area);
    ~GameArea();

    Platform* platform();
    Ball* ball();

    void spawnBonus(Block* block);
    void spawnBottomBlock();
    //void spawnMovingBlock();
    void spawnSecondBall();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};
