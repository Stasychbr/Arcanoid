#pragma once
#include <QGraphicsItem>
#include "GameArea.h"
class Bonus : public QGraphicsItem {
private:
    static const int _speed = 3.0;
    static const int _size = 10;
protected:
    QColor _color = Qt::black;
    Bonus(QGraphicsItem* parent, QPointF& position);
public:
    int size();
    
    virtual void effect(GameArea* area) = 0;
    void move();
    
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};

