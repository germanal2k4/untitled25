#include "Figure.h"
#include "ChessSquare.h"
#include "Game.h"

Figure::Figure(QString color, Game* game, QGraphicsItem* parent)
        : QGraphicsPixmapItem(parent), color(color), game(game), currentSquare(nullptr) {}

QString Figure::getColor() {
    return color;
}

void Figure::setSquare(ChessSquare* square) {
    qDebug() << square->getPosition();
    currentSquare = square;
}

ChessSquare* Figure::getSquare() {
    return currentSquare;
}



