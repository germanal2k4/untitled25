//
// Created by German Albershteyn on 15.10.2024.
//

#include "Bishop.h"

#include <utility>




Bishop::Bishop(QString color, Game *game, QGraphicsItem *parent) : Figure(color, game, parent) {
    if (color == QString("white")) {

        setPixmap(QPixmap(":/Images/bishop1.png"));
    } else {
        setPixmap(QPixmap(":/Images/bishop.png"));
    }
}

QList<QPair<int, int>> Bishop::getPossibleMoves(const QPair<int, int> &pos) {

    int x = pos.first;
    int y = pos.second;
    QList<QPair<int, int>> ans;

    while(x < 7 && y < 7){
        x++;
        y++;
        if(game->getSquare(x, y)->getFigure() == nullptr){
            ans.push_back({x,y});
        } else {
            if(game->getSquare(x, y)->getFigure()->getColor() != color){
                ans.push_back({x,y});
            }
            break;
        }
    }
    x = pos.first;
    y = pos.second;
    while(x < 7 && y > 0){
        x++;
        y--;
        if(game->getSquare(x, y)->getFigure() == nullptr){
            ans.push_back({x,y});
        } else {
            if(game->getSquare(x, y)->getFigure()->getColor() != color){
                ans.push_back({x,y});
            }
            break;
        }
    }
    x = pos.first;
    y = pos.second;
    while(x > 0 && y > 0){
        x--;
        y--;
        if(game->getSquare(x, y)->getFigure() == nullptr){
            ans.push_back({x,y});
        } else {
            if(game->getSquare(x, y)->getFigure()->getColor() != color){
                ans.push_back({x,y});
            }
            break;
        }
    }
    x = pos.first;
    y = pos.second;
    while(x > 0 && y < 7){
        x--;
        y++;
        if(game->getSquare(x, y)->getFigure() == nullptr){
            ans.push_back({x,y});
        } else {
            if(game->getSquare(x, y)->getFigure()->getColor() != color){
                ans.push_back({x,y});
            }
            break;
        }
    }
    return ans;
}
