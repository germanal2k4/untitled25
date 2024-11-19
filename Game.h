#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "ChessSquare.h"
#include "Figure.h"

class Game : public QGraphicsView {
Q_OBJECT
public:
    explicit Game(QWidget* parent = nullptr);

    // Инициализация клеток и фигур
    void initBoard();
    void initWhite();
    void initBlack();
    ChessSquare* getSquare(int x, int y);
    // Добавление фигуры на сцену и на клетку
    void addFigureToScene(Figure* figure, ChessSquare* square);
    bool isKingInCheck(const QString& color);
    bool isCheckmate(const QString& color);

    void handlePieceClick(Figure* piece);
    void handleSquareClick(ChessSquare* square);
    void removeFigureFromScene(Figure* figure);
private:
    QPair<int, int> whiteKingPosition;
    QPair<int, int> blackKingPosition;
    QGraphicsTextItem* currentPlayerText;
    QGraphicsScene* scene;  // Сцена для отображения доски и фигур
    QList<QList<ChessSquare*>> squares;  // 2D массив клеток
    QString current;
    Figure* selectedPiece;  // Выбранная фигура
    ChessSquare* selectedSquare;  // Клетка с выбранной фигурой
    QList<QPair<Figure *, ChessSquare *>> getValidMovesToBlockCheck(const QString &color);
};

#endif // GAME_H
