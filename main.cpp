#include <QApplication>
#include "Game.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto game = new Game();
    game->show();

    return QApplication::exec();
}
