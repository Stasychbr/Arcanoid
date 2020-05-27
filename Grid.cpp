#include "Grid.h"
#include <random>
#include <QRandomGenerator>
#include "Bonus.h"

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
        }
    }
}

Block* Grid::generateBlock(int blockHeight, int blockWidth) {
    std::geometric_distribution<int> blocksDistr(0.4);
    switch (blocksDistr(*QRandomGenerator::global())) {
    case 1:
        _blocksToDestroy++;
        return (Block*)new SpeedBlock(this, blockHeight, blockWidth);
    case 3:
        return (Block*)new UnbreakableBlock(this, blockHeight, blockWidth);
    default:
        _blocksToDestroy++;
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

void Grid::blockWasDestroyed() {
    _blocksToDestroy--;
}

bool Grid::isAllDestroyed() {
    return _blocksToDestroy == 0;
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

QPointF Grid::findBonusPlace(Block* block) {
    int column = (block->x() - block->width() / 2) / block->width();
    int row = (block->y() - block->height() / 2) / block->height();
    int lowestRow = _vertSize;
    for (int i = _vertSize - 1; i >= row; i--) {
        if (_blocks[i][column]->isVisible()) {
            lowestRow = i;
            break;
        }
    }
    return QPointF(block->x(), ++lowestRow * block->height() + Bonus::size());
}

bool Grid::findFreeSpace(QPointF& start, QPointF& end) {
    int startPlace = 0, endPlace = 0;
    for (int i = 0; i < _vertSize; i++) {
        startPlace = 0;
        endPlace = 0;
        for (int j = 0; j < _horSize; j++) {
            if (!_blocks[i][j]->isVisible()) {
                startPlace = j;
                endPlace = startPlace;
                while (j < _horSize && !_blocks[i][j]->isVisible()) {
                    endPlace++;
                    j++;
                }
            }
            if (endPlace - startPlace >= 3) {
                start = _blocks[i][startPlace]->pos();
                end = _blocks[i][endPlace - 1]->pos();
                return true;
            }
        }
    }
    return false;
}

void Grid::blockSize(int& height, int& width) {
    height = _blocks[0][0]->height();
    width = _blocks[0][0]->width();
}

QRectF Grid::boundingRect() const {
    return _area;
}

void Grid::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
}
