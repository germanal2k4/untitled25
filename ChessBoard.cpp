#include "ChessBoard.h"

ChessBoard::ChessBoard(QWidget* parent) : QGraphicsView(parent), scene(new QGraphicsScene(this)) {
    setScene(scene);
}

QGraphicsScene* ChessBoard::getScene() {
    return scene;  // Возвращаем сцену для добавления элементов
}
