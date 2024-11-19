#ifndef PAWN_H
#define PAWN_H

#include "Figure.h"
#include "Game.h"
#include "ChessSquare.h"

class Pawn : public Figure {
public:
    Pawn(QString color, Game* game, QGraphicsItem* parent = nullptr);

    // Реализуем метод для получения возможных ходов пешки
    QList<QPair<int, int>> getPossibleMoves(const QPair<int, int>& pos) override;
    void changeFlag();
private:
    bool flag;
};

#endif // PAWN_H
