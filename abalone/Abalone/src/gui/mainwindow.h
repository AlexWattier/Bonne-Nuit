#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QLabel>
#include <QMessageBox>
#include <iostream>
#include <cmath>
#include <QtAlgorithms>

#include "BlackBall.h"
#include "point.hpp"
#include "../abalone/Controller.h"
#include "../abalone/InterfaceView.h"
#include "../abalone/Case.h"
#include "../abalone/Board.h"
#include "../abalone/Model.h"


namespace gui::mainwindow {

class MainWindow : public QMainWindow,public abalone::view::InterfaceView{
    Q_OBJECT

private:
    abalone::Model::Model * game_;

    QGraphicsView * view_ = nullptr;

    int const size_ = 9;

    std::string commande_= "";

    QGraphicsScene * scene ;

    void displayInsideBoard( abalone::Model::Model * game);

    abalone::Controlleur::Controller *controller_;

    void displayAllBall(abalone::Model::Board::Board board);

    void refreshView();

    bool verifCoord6();

    int convertCoord(char charCoo);

public:

    MainWindow(abalone::Model::Model & game,QWidget *parent=nullptr  );

    ~MainWindow();

    void setController(abalone::Controlleur::Controller *controller);

    void displayGameStart() override;

    void displayTurn(bool) override;

    void displayBoard(abalone::Model::Board::Board) override;

    void displayWinner(int,int) override;

    void displayScore(int,int) override;

    std::string askMove() override;

    void displayError(const std::exception &) override;

    void receivedTouchClick(std::string commande);
};
}
#endif // MAINWINDOW_H
