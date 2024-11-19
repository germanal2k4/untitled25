#ifndef BISHOP_H
#define BISHOP_H

#include "Figure.h"
#include "Game.h"
#include "ChessSquare.h"

class Bishop : public Figure {
public:
    Bishop(QString color, Game* game, QGraphicsItem* parent = nullptr);

    // Реализуем метод для получения возможных ходов слона
    QList<QPair<int, int>> getPossibleMoves(const QPair<int, int>& pos) override;
};

#endif // BISHOP_H
