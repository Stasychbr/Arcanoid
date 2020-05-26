#pragma once
#include <QGraphicsItem>
#include "GameArea.h"
class Bonus : public QGraphicsItem {
public:
    enum class BonusType {
        INSTANT,
        AFTER_PLATFORM_HIT,
    };
private:
    static const int _speed = 3.0;
    static const int _size = 10;
protected:
    BonusType _type = BonusType::INSTANT;
    QColor _color = Qt::black;
    Bonus(QGraphicsItem* parent, QPointF& position);
    int _numberOfExecs = 1;
public:
    int size();
    Bonus::BonusType type();
    int numberOfExecutions();
    
    virtual void effect(GameArea* area) = 0;
    void move();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};

