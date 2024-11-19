#ifndef FIGURE_H
#define FIGURE_H

#include <QGraphicsPixmapItem>
#include <QList>
#include <QPair>
#include <QString>

class ChessSquare;  // Forward declaration для клеток
class Game;         // Forward declaration для игры

class Figure : public QGraphicsPixmapItem {
public:
    Figure(QString color, Game* game, QGraphicsItem* parent = nullptr);

    // Чисто виртуальный метод для движения фигур
    virtual QList<QPair<int, int>> getPossibleMoves(const QPair<int, int>& pos) = 0;
    QString getColor();
    void setSquare(ChessSquare* square);
    ChessSquare* getSquare();


protected:

    QString color;
    ChessSquare* currentSquare;
    Game* game;
};

#endif // FIGURE_H
