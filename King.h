#ifndef KING_H
#define KING_H

#include "Figure.h"
#include "Game.h"
#include "ChessSquare.h"

class King : public Figure {
public:
    King(QString color, Game* game, QGraphicsItem* parent = nullptr);

    // Реализуем метод для получения возможных ходов короля
    QList<QPair<int, int>> getPossibleMoves(const QPair<int, int>& pos) override;
};

#endif // KING_H
