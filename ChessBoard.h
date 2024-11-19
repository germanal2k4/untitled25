#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QGraphicsView>
#include <QGraphicsScene>

class ChessBoard : public QGraphicsView {
Q_OBJECT
public:
    explicit ChessBoard(QWidget* parent = nullptr);
    QGraphicsScene* getScene();  // Возвращаем сцену, чтобы игра могла добавлять на неё элементы

private:
    QGraphicsScene* scene;
};

#endif // CHESSBOARD_H
