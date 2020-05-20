#include "Arcanoid.h"

Arcanoid::Arcanoid(QWidget *parent):QMainWindow(parent) {
    ui.setupUi(this);
    ui.mainToolBar->close();
    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    _view = new QGraphicsView;
    _view->setFixedSize({ _horSize, _vertSize });
    setFixedSize({ _horSize, _vertSize });
    setCentralWidget(_view);
    _view->setFrameStyle(0);


    _scene = new QGraphicsScene();
    _view->setRenderHint(QPainter::Antialiasing);
    _scene->setSceneRect(0, 0, _horSize, _vertSize);
}

Arcanoid::~Arcanoid() {
    delete _scene;
}
