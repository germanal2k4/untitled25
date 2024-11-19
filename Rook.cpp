#include "Rook.h"

Rook::Rook(QString color, Game* game, QGraphicsItem* parent)
        : Figure(color, game, parent) {
    if (color == "white") {
        setPixmap(QPixmap(":/Images/rook1.png"));
    } else {
        setPixmap(QPixmap(":/Images/rook.png"));
    }
}

// Реализуем метод для получения всех возможных ходов ладьи
QList<QPair<int, int>> Rook::getPossibleMoves(const QPair<int, int>& pos) {
    QList<QPair<int, int>> ans;

    int y = pos.second + 1;
    int x = pos.first;
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
