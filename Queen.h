#ifndef QUEEN_H
#define QUEEN_H

#include "Figure.h"
#include "Game.h"
#include "ChessSquare.h"

class Queen : public Figure {
public:
    Queen(QString color, Game* game, QGraphicsItem* parent = nullptr);

    // Реализуем метод для получения возможных ходов ферзя
    QList<QPair<int, int>> getPossibleMoves(const QPair<int, int>& pos) override;
};

#endif // QUEEN_H
