#include "ChessSquare.h"
#include "Figure.h"
#include "Game.h"
#include <QGraphicsSceneMouseEvent>



void ChessSquare::setFigure(Figure* newFigure) {
    figure = newFigure;
    figure->setSquare(this);
    if (figure) {
        // Устанавливаем позицию фигуры
        figure->setPos(x() + rect().width() / 2 - figure->boundingRect().width() / 2,
                       y() + rect().height() / 2 - figure->boundingRect().height() / 2);

    }
}

Figure* ChessSquare::getFigure() {
    return figure;
}

void ChessSquare::removeFigure() {
    figure = nullptr;
}

void ChessSquare::highlight(Qt::GlobalColor color) {
    setBrush(QBrush(color));
}

void ChessSquare::resetColor() {
    if ((row + col) % 2 == 0) {
        setBrush(QBrush(Qt::white));
    } else {
        setBrush(QBrush(Qt::gray));
    }
}

QPair<int, int> ChessSquare::getPosition() {
    return QPair<int, int>(row, col);
}


ChessSquare::ChessSquare(int row, int col, int size, Game* game, QGraphicsScene* scene)
        : row(row), col(col), figure(nullptr), game(game), scene(scene) {
    setRect(0, 0, size, size);
    resetColor();
}

void ChessSquare::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(figure){
        game->handlePieceClick(figure);
    } else {
        game->handleSquareClick(this);
    }
}

QBrush ChessSquare::getHighlight() {
    return brush();
}
