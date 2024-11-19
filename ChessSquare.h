#ifndef CHESSSQUARE_H
#define CHESSSQUARE_H

#include <QGraphicsRectItem>
#include <QBrush>

class Figure;  // Forward declaration для фигуры
class Game;    // Forward declaration для игры

class ChessSquare : public QGraphicsRectItem {
public:
    ChessSquare(int row, int col, int size, Game* game, QGraphicsScene* scene);

    void setFigure(Figure* figure);
    Figure* getFigure();
    void removeFigure();

    void highlight(Qt::GlobalColor color);
    void resetColor();
    QBrush getHighlight();
    QPair<int, int> getPosition();
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;



private:
    QGraphicsScene* scene;
    int row;
    int col;
    Figure* figure;
    Game* game;
};

#endif // CHESSSQUARE_H
