#include "mainwindow.h"
#include "../abalone/Controller.h"
#include "../abalone/Game.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    abalone::Model::Game game = abalone::Model::Game();
    gui::mainwindow::MainWindow view = gui::mainwindow::MainWindow(game);
    abalone::Controlleur::Controller controller = abalone::Controlleur::Controller(game,view);
    view.setController(&controller);
    view.show();
    return a.exec();
}
