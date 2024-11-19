#ifndef ROOK_H
#define ROOK_H

#include "Figure.h"
#include "ChessBoard.h"
#include "ChessSquare.h"
#include "Game.h"

class Rook : public Figure {
public:
    Rook(QString color, Game* game, QGraphicsItem* parent = nullptr);

    // Реализуем метод для получения возможных ходов ладьи
    QList<QPair<int, int>> getPossibleMoves(const QPair<int, int>& pos) override;
};

#endif // ROOK_H
