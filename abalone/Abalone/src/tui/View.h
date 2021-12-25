#ifndef VIEW_H
#define VIEW_H

#include "../abalone/Board.h"
#include "../abalone/InterfaceView.h"
#include <iostream>
#include "../abalone/Case.h"

namespace tui::View {
/**
 * @brief The View class that is gonna display everything what is going on in the game. Majority of method are from InterfaceView.
 */
class View: public abalone::view::InterfaceView {
private:
    int const size_ = 9;

    void displayInsideBoard(abalone::Model::Board::Board& , int);

public:
    View();

    void displayGameStart() override;

    void displayTurn(bool) override;

    void displayBoard(abalone::Model::Board::Board) override;

    void displayWinner(int,int) override;

    void displayScore(int,int) override;

    std::string askMove() override;

    void displayError(const std::exception &) override;
};
}



#endif // VIEW_H
