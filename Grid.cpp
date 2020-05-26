#include "Grid.h"
#include <random>
#include <QRandomGenerator>

Grid::Grid(QGraphicsItem* parent, QRectF& area) {
    setParentItem(parent);
    _area = QRectF(0, 0, area.width(), area.height());
    int blockHeight = area.height() / _vertSize;
    int blockWidth = area.width() / _horSize;
    for (int i = 0; i < _vertSize; i++) {
        _blocks.push_back(std::vector<Block*> {});
        for (int j = 0; j < _horSize; j++) {
            _blocks[i].push_back(generateBlock(blockHeight, blockWidth));
            _blocks[i][j]->setPos(j * blockWidth + 0.5 * blockWidth, i * blockHeight + 0.5 * blockHeight);
            //_blocks[i][j]->_posX = j; //debug
            //_blocks[i][j]->_posY = i; //debug 
        }
    }
}

Block* Grid::generateBlock(int blockHeight, int blockWidth) {
    std::geometric_distribution<int> blocksDistr(0.4);
    switch (blocksDistr(*QRandomGenerator::global())) {
    case 1:
        return (Block*)new SpeedBlock(this, blockHeight, blockWidth);
    case 2:
        return (Block*)new UnbreakableBlock(this, blockHeight, blockWidth);
    default:
        return new Block(this, blockHeight, blockWidth);
    }
}

Grid::~Grid() {
    for (auto row : _blocks) {
        for (auto block : row) {
            delete block;
        }
    }
}

Block* Grid::ballCollision(QGraphicsItem* ball) {
    for (auto& row: _blocks) {
        for (auto& block : row) {
            if (block->hp() > 0 && block->collidesWithItem(ball)) {
                return block;
            }
        }
    }
    return nullptr;
}

QRectF Grid::boundingRect() const {
    return _area;
}

void Grid::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
}
