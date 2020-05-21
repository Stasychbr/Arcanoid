#pragma once

#include <QGraphicsObject>

class Platform : public QGraphicsObject {
    Q_OBJECT

private:
    static const int _horSize = 80;
    static const int _vertSize = 15;
    const double dx = 2.0;

    double _posX = 0;

public:
    Platform(QGraphicsItem* parent, QPointF& startPos);
    ~Platform();

    int width();
    int height();

    void moveRight();
    void moveLeft();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};
