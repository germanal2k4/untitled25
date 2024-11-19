#include <QCoreApplication>
#include <QMessageBox>
#include "Game.h"
#include "Rook.h"
#include "Horse.h"
#include "Bishop.h"
#include "Queen.h"
#include "Pawn.h"
#include "King.h"

Game::Game(QWidget* parent) : QGraphicsView(parent), selectedPiece(nullptr), selectedSquare(nullptr) {
    scene = new QGraphicsScene(this);
    setScene(scene);
    this->current = "white";
    setFixedSize(1000, 1000);
    scene->setSceneRect(0, 0, 1000, 1000);

    QGraphicsRectItem* grayBackground = new QGraphicsRectItem(650, 0, 350, 1000);  // Прямоугольник справа
    grayBackground->setBrush(QBrush(Qt::lightGray));  // Устанавливаем светло-серый цвет
    grayBackground->setZValue(-1);  // Размещаем фон позади фигур
    scene->addItem(grayBackground);

    QGraphicsRectItem* grayBackgroundBottom = new QGraphicsRectItem(0, 650, 640, 50);
    grayBackgroundBottom->setBrush(QBrush(Qt::lightGray));
    grayBackgroundBottom->setZValue(-1);
    scene->addItem(grayBackgroundBottom);

    // Создаем текст для отображения текущего игрока
    currentPlayerText = new QGraphicsTextItem("Ход белых");
    currentPlayerText->setDefaultTextColor(Qt::black);
    currentPlayerText->setFont(QFont("Arial", 18, QFont::Bold));  // Увеличиваем размер и жирность текста
    currentPlayerText->setPos(200, 655);  // Располагаем текст по центру серого фона под доской
    scene->addItem(currentPlayerText);

    initBoard();
}

// Инициализация клеток
void Game::initBoard() {
    int squareSize = 80;  // Размер клетки
    for (int row = 0; row < 8; ++row) {
        QList<ChessSquare*> rowSquares;
        for (int col = 0; col < 8; ++col) {
            // Создаём клетку и передаём указатель на сцену
            ChessSquare* square = new ChessSquare(row, col, squareSize, this, scene);
            QMetaObject::invokeMethod(scene, [=]() {
                scene->addItem(square);
            });  // Добавляем клетку на сцену
            square->setPos(col * squareSize, row * squareSize);  // Устанавливаем позицию клетки
            rowSquares.append(square);  // Добавляем клетку в строку
        }
        squares.append(rowSquares);  // Добавляем строку клеток в массив клеток
    }
    initWhite();
    initBlack();
}

// Инициализация фигур
void Game::initWhite() {
    // Белые фигуры
    addFigureToScene(new Rook("white", this), squares[0][0]);
    addFigureToScene(new Horse("white", this), squares[0][1]);
    addFigureToScene(new Bishop("white", this), squares[0][2]);
    addFigureToScene(new Queen("white", this), squares[0][4]);
    addFigureToScene(new King("white", this), squares[0][3]);
    addFigureToScene(new Bishop("white", this), squares[0][5]);
    addFigureToScene(new Horse("white", this), squares[0][6]);
    addFigureToScene(new Rook("white", this), squares[0][7]);
    whiteKingPosition = QPair<int, int>(0, 3);
    // Белые пешки
    for (int col = 0; col < 8; ++col) {
        addFigureToScene(new Pawn("white", this), squares[1][col]);
    }
}

// Метод для добавления фигуры на сцену и на клетку
void Game::addFigureToScene(Figure* figure, ChessSquare* square) {
    // Добавляем фигуру на сцену
    QMetaObject::invokeMethod(scene, [=]() {
        scene->addItem(figure);
    });

    // Затем устанавливаем фигуру на клетку
    square->setFigure(figure);
    QCoreApplication::processEvents();
    // Отладка: выводим, что фигура была добавлена
}

void Game::handlePieceClick(Figure* piece) {
    if (!piece) return;

    // Проверяем, является ли клик игрока на фигуре их текущего цвета
    if (piece->getColor() != current && !selectedPiece) {
        return;
    }

    if (selectedPiece) {
        // Сбрасываем подсветку всех клеток
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                squares[i][j]->resetColor();
            }
        }

        // Проверяем, кликаем ли мы по фигуре противника
        if (piece->getColor() != selectedPiece->getColor()) {

            qDebug() << "Противник выбран, удаляем фигуру...";  // Добавляем отладочное сообщение

            // Удаляем фигуру противника
            removeFigureFromScene(piece);  // <-- Проверяем, вызывается ли этот метод
            auto targetSquare = piece->getSquare();
            targetSquare->setFigure(selectedPiece);


            // Смена текущего игрока
            current = (current == "white") ? "black" : "white";

            // Обновляем текст для отображения текущего игрока
            currentPlayerText->setPlainText(current == "white" ? "Ход белых" : "Ход черных");

            // Сбрасываем выделение
            selectedPiece = nullptr;
            selectedSquare = nullptr;
            return;
        }
    }

    selectedPiece = piece;
    selectedSquare = piece->getSquare();
    selectedSquare->highlight(Qt::yellow);

    auto possibleMoves = selectedPiece->getPossibleMoves(selectedSquare->getPosition());
    for (auto move : possibleMoves) {
        squares[move.first][move.second]->highlight(Qt::red);
    }
}


void Game::removeFigureFromScene(Figure* figure) {
    if (!figure) return;

    // Координаты для размещения "убитых" фигур на сером поле
    static int removedFigureX = 700;
    static int removedFigureY = 20;

    // Перемещаем фигуру на серое поле справа от доски
    figure->setPos(removedFigureX, removedFigureY);

    // Обновляем координаты для следующей удаленной фигуры (стековое расположение)
    removedFigureY += 80;
    if (removedFigureY >= 1000) {  // Если достигли нижней границы, начинаем новый столбец
        removedFigureY = 20;
        removedFigureX += 80;
    }

    // Убираем фигуру с текущей клетки
    ChessSquare* square = figure->getSquare();
    if (square) {
        square->removeFigure();
    }

    centerOn(removedFigureX, removedFigureY);
}



QList<QPair<Figure*, ChessSquare*>> Game::getValidMovesToBlockCheck(const QString& color) {
    QList<QPair<Figure*, ChessSquare*>> validMoves;  // Список допустимых ходов

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Figure* piece = squares[row][col]->getFigure();

            // Проверяем, принадлежит ли фигура текущему игроку
            if (piece && piece->getColor() == color) {
                // Получаем возможные ходы для этой фигуры
                auto moves = piece->getPossibleMoves(squares[row][col]->getPosition());

                for (auto move : moves) {
                    ChessSquare* targetSquare = getSquare(move.first, move.second);

                    // Если целевая клетка существует
                    if (targetSquare) {
                        Figure* capturedPiece = targetSquare->getFigure();  // Сохраняем возможную съеденную фигуру

                        // Временно перемещаем фигуру для проверки
                        squares[row][col]->removeFigure();
                        targetSquare->setFigure(piece);

                        // Проверяем, снимается ли шах
                        if (!isKingInCheck(color)) {
                            validMoves.append(qMakePair(piece, targetSquare));
                        }

                        // Восстанавливаем исходное положение
                        targetSquare->setFigure(capturedPiece);
                        squares[row][col]->setFigure(piece);
                    }
                }
            }
        }
    }

    return validMoves;
}


// Обработка клика по клетке
void Game::handleSquareClick(ChessSquare* square) {
    if (!square || !selectedPiece) return;
    if(square->getHighlight() != QBrush(Qt::red)){
        return;
    }

    if (dynamic_cast<King*>(selectedPiece)) {
        if (selectedPiece->getColor() == "white") {
            whiteKingPosition = square->getPosition();
        } else if (selectedPiece->getColor() == "black") {
            blackKingPosition = square->getPosition();
        }
    }

    if (isKingInCheck(current)) {
        // Получаем допустимые ходы для снятия шаха
        QList<QPair<Figure*, ChessSquare*>> validMoves = getValidMovesToBlockCheck(current);

        // Проверяем, можно ли выбранной фигурой снять шах
        bool canMove = false;
        for (auto& move : validMoves) {
            if (move.first == selectedPiece && move.second == square) {
                canMove = true;
                break;
            }
        }

        if (!canMove) {
            QMessageBox::warning(this, "Невозможный ход", "Вы можете ходить только королем или фигурами, которые могут снять шах.");
            return;
        }
    }
    
    ChessSquare* originalSquare = selectedSquare;
    Figure* capturedPiece = square->getFigure();

    if (isKingInCheck(current)) {
        square->setFigure(capturedPiece);
        originalSquare->setFigure(selectedPiece);

        QMessageBox::warning(this, "Невозможный ход", "Ход оставит короля под шахом!");
        return;
    }

    selectedSquare->removeFigure();
    square->setFigure(selectedPiece);
    if((dynamic_cast<Pawn*>(selectedPiece))){
        auto pawn = dynamic_cast<Pawn*>(selectedPiece);
        pawn->changeFlag();
    }
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            squares[i][j]->resetColor();
        }
    }
    current = current == "white" ? "black" : "white";
    currentPlayerText->setPlainText(current == "white" ? "Ход белых" : "Ход черных");
    selectedPiece = nullptr;
    selectedSquare = nullptr;

    if (isKingInCheck(current)) {
        if (isCheckmate(current)) {

            QMessageBox::information(this, "Мат", "Игра окончена, поставлен мат!");
        } else {

            QMessageBox::information(this, "Шах", "Король под шахом!");
        }
    }
}

void Game::initBlack() {
    addFigureToScene(new Rook("black", this), squares[7][0]);
    addFigureToScene(new Horse("black", this), squares[7][1]);
    addFigureToScene(new Bishop("black", this), squares[7][2]);
    addFigureToScene(new Queen("black", this), squares[7][3]);
    addFigureToScene(new King("black", this), squares[7][4]);
    addFigureToScene(new Bishop("black", this), squares[7][5]);
    addFigureToScene(new Horse("black", this), squares[7][6]);
    addFigureToScene(new Rook("black", this), squares[7][7]);
    blackKingPosition = QPair<int, int>(7, 4);
    for (int col = 0; col < 8; ++col) {
        addFigureToScene(new Pawn("black", this), squares[6][col]);
    }
}

ChessSquare *Game::getSquare(int x, int y) {
    if(x >= 0 && x <= 7 && y >= 0 && y <= 7){
        return squares[x][y];
    }
    return nullptr;
}

bool Game::isKingInCheck(const QString &color) {
    QPair<int, int> kingPosition = (color == "white") ? whiteKingPosition : blackKingPosition;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Figure* opponentPiece = squares[row][col]->getFigure();
            if (opponentPiece && opponentPiece->getColor() != color) {
                auto moves = opponentPiece->getPossibleMoves(squares[row][col]->getPosition());
                for (auto move : moves) {
                    if (move == kingPosition) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Game::isCheckmate(const QString &color) {
    if (!isKingInCheck(color)) return false;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Figure* piece = squares[row][col]->getFigure();
            if (piece && piece->getColor() == color) {
                auto moves = piece->getPossibleMoves(squares[row][col]->getPosition());
                for (auto move : moves) {
                    ChessSquare* targetSquare = getSquare(move.first, move.second);
                    Figure* originalFigure = targetSquare->getFigure();

                    // Временно перемещаем фигуру для проверки
                    targetSquare->setFigure(piece);
                    squares[row][col]->removeFigure();
                    bool stillInCheck = isKingInCheck(color);

                    // Восстанавливаем исходное положение фигур
                    targetSquare->setFigure(originalFigure);
                    squares[row][col]->setFigure(piece);

                    // Если шах снят, значит это не мат
                    if (!stillInCheck) return false;
                }
            }
        }
    }
    return true;
}


