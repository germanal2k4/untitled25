//
// Created by German Albershteyn on 16.10.2024.
//

#include "King.h"


King::King(QString color, Game *game, QGraphicsItem *parent) : Figure(color, game, parent) {
    if (color == "white") {
        setPixmap(QPixmap(":/Images/king1.png"));
    } else {
        setPixmap(QPixmap(":/Images/king.png"));
    }
}

QList<QPair<int, int>> King::getPossibleMoves(const QPair<int, int> &pos) {
    int x = pos.first;
    int y = pos.second;
    QList<QPair<int, int>> ans = {{x - 1, y}, {x, y - 1},
                                  {x + 1, y + 1}, {x - 1, y + 1},
                                  {x, y + 1}, {x - 1, y - 1},
                                  {x + 1, y}, {x + 1, y - 1}};
    QList<QPair<int, int>> res;
    for(auto z : ans){
        if(0 <= z.first && z.first <= 7 && 0 <= z.second && z.second <= 7){
            if(game->getSquare(z.first, z.second)->getFigure() == nullptr){
                res.push_back(z);
            } else if(game->getSquare(z.first, z.second)->getFigure()->getColor() != color){
                res.push_back(z);
            }
        }
    }
    return res;
}
