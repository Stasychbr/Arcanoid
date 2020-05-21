#pragma once

#include <QtWidgets/QMainWindow>
#include <QGraphicsView>
#include <QTimer>
#include "ui_Arcanoid.h"
#include "GameArea.h"

class Arcanoid : public QMainWindow
{
    Q_OBJECT

public:
    Arcanoid(QWidget *parent = Q_NULLPTR);
    ~Arcanoid();

private:
    static const int _vertSize = 600;
    static const int _horSize = 600;

    QGraphicsView* _view = nullptr;
    QGraphicsScene* _scene = nullptr;
    QTimer* _timer = nullptr;

    GameArea* _gameArea = nullptr;

    Ui::ArcanoidClass ui;
};
