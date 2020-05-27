#include "Arcanoid.h"
#include <QMessageBox>

Arcanoid::Arcanoid(QWidget *parent):QMainWindow(parent) {
    ui.setupUi(this);
    ui.mainToolBar->close();
    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    _view = new QGraphicsView;
    _view->setFixedSize({ _horSize, _vertSize });
    setFixedSize({ _horSize, _vertSize });
    setCentralWidget(_view);
    _view->setFrameStyle(0);


    QRectF area(0, 0, _horSize, _vertSize);
    _scene = new QGraphicsScene();
    _view->setRenderHint(QPainter::Antialiasing);
    _scene->setSceneRect(area);

    _gameArea = new GameArea(area);
    _scene->addItem(_gameArea);
    _view->setScene(_scene);
}

Arcanoid::~Arcanoid() {
    delete _gameArea;
    delete _scene;
}

