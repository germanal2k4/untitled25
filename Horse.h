#ifndef HORSE_H
#define HORSE_H

#include "Figure.h"
#include "Game.h"
#include "ChessSquare.h"

class Horse : public Figure {
public:
    Horse(QString color, Game* game, QGraphicsItem* parent = nullptr);

    QList<QPair<int, int>> getPossibleMoves(const QPair<int, int>& pos) override;
};

#endif // Horse_H