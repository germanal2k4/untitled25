//
// Created by German Albershteyn on 16.10.2024.
//

#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"


Queen::Queen(QString color, Game *game, QGraphicsItem *parent) : Figure(color, game, parent) {
    if (color == "white") {
        setPixmap(QPixmap(":/Images/queen1.png"));
    } else {
        setPixmap(QPixmap(":/Images/queen.png"));
    }
}

QList<QPair<int, int>> Queen::getPossibleMoves(const QPair<int, int> &pos) {
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

    y = pos.second + 1;
    x = pos.first;
    while (y <= 7){
        if(game->getSquare(x, y)->getFigure() == nullptr){
            ans.push_back({x,y});
            y++;
        } else { if(game->getSquare(x, y)->getFigure()->getColor() != color){
                ans.push_back({x,y});
            }
            break;
        }
    }
    y = pos.second - 1;
    while (y >= 0){
        if(game->getSquare(x, y)->getFigure() == nullptr){
            ans.push_back({x,y});
            y--;
        } else{
            if(game->getSquare(x, y)->getFigure()->getColor() != color){
                ans.push_back({x,y});
            }
            break;
        }
    }

    y = pos.second;
    x = pos.first + 1;
    while (x <= 7){
        if(game->getSquare(x, y)->getFigure() == nullptr){
            ans.push_back({x,y});
            x++;
        } else{
            if(game->getSquare(x, y)->getFigure()->getColor() != color){
                ans.push_back({x,y});
            }
            break;
        }
    }
    x = pos.first - 1 ;
    while (x >= 0){
        if(game->getSquare(x, y)->getFigure() == nullptr){
            ans.push_back({x,y});
            x--;
        } else {
            if(game->getSquare(x, y)->getFigure()->getColor() != color){
                ans.push_back({x,y});
            }
            break;
        }
    }
    return ans;
}
