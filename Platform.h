#pragma once

#include <QGraphicsObject>

class Platform : public QGraphicsItem {

private:
    static const int _startHorSize = 80;
    static const int _vertSize = 15;
    static const int _maxHorSize = 2 * _startHorSize;
    static const int _cutSize = _startHorSize / 2;
    static const int _enlargeSize = _startHorSize / 2;
    const double _speed = 4.0;

    int _horSize = 0;
    double _posX = 0;

public:
    Platform(QGraphicsItem* parent, QPointF& startPos);
    ~Platform();

    int width();
    int height();

    void moveRight();
    void moveLeft();

    void enlarge();
    void shorten();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};
