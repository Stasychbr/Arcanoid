#include "Block.h"
#include <QPainter>
#include <random>
#include <QRandomGenerator>
#include "Grid.h"

Block::Block(QGraphicsItem* parent, int height, int width) {
    std::uniform_int_distribution<int> bonusDistr(1, _bonusChance);
    setParentItem(parent);
    _height = height;
    _width = width;
    _hp = QRandomGenerator::global()->bounded(1, _maxHp + 1);
    _hasBonus = bonusDistr(*QRandomGenerator::global()) == 1;
}

Block::~Block() {

}

int Block::height() {
    return _height;
}

int Block::width() {
    return _width;
}

int Block::hp() {
    return _hp;
}

bool Block::hasBonus() {
    return _hasBonus;
}

int Block::hit(Ball* ball) {
    _hp--;
    update();
    if (_hp == 0) {
        Grid* grid = (Grid*)parentItem();
        grid->blockWasDestroyed();
        hide();
    }
    return _scoreForHit;
}

QRectF Block::boundingRect() const {
    return QRectF(-_width / 2, -_height / 2, _width, _height);
}

void Block::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    int green = 255  / _maxHp * _hp;
    int red = _hp > _maxHp / 2 ? 0 : 255;
    painter->setBrush(QColor(red, green, 0));
    painter->drawRect(boundingRect());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
