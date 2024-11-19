//
// Created by German Albershteyn on 15.10.2024.
//

#include "Pawn.h"

#include <utility>


Pawn::Pawn(QString color, Game *game, QGraphicsItem *parent) : Figure(color, game, parent) {
    if (color == "white") {
        setPixmap(QPixmap(":/Images/pawn1.png"));
    } else {
        setPixmap(QPixmap(":/Images/pawn.png"));
    }
    this->flag = false;
}

QList<QPair<int, int>> Pawn::getPossibleMoves(const QPair<int, int> &pos) {
    QList<QPair<int, int>> ans;
    int tmp = color == "white" ? 1 :  -1;
    if(!flag){
        int temp = color == "white" ? 2 : -2;
        if (!game->getSquare(pos.first + temp, pos.second)->getFigure()) {
            ans.push_back({pos.first + temp, pos.second});
        }
    }
    if (!game->getSquare(pos.first + tmp, pos.second)->getFigure()) {
        ans.push_back({pos.first + tmp, pos.second});
    }

    if (0 <= pos.first + tmp && pos.first + tmp <= 7 && pos.second - 1 >= 0
    && game->getSquare(pos.first + tmp, pos.second - 1)->getFigure()
    && game->getSquare(pos.first + tmp, pos.second - 1)->getFigure()->getColor() != color) {
        ans.push_back({pos.first + tmp, pos.second - 1});
    }
    if (0 <= pos.first + tmp && pos.first + tmp <= 7 && pos.second + 1 <= 7 &&
            game->getSquare(pos.first + tmp, pos.second + 1)->getFigure()
    && game->getSquare(pos.first + tmp, pos.second + 1)->getFigure()->getColor() != color) {
        ans.push_back({pos.first + tmp, pos.second + 1});
    }
    return ans;
}

void Pawn::changeFlag() {
    flag = true;
}
