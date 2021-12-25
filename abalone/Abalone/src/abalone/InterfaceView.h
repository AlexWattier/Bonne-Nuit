#ifndef _INTERFACEVIEW_H
#define _INTERFACEVIEW_H
#include "Board.h"

namespace abalone::view {

/**
 * @brief The InterfaceView Absract class that need to be herited by a view if you want a view to be use by the controller.
 */
class InterfaceView {
public:
    /**
     * @brief InterfaceView Constructor of InterfaceView
     */
    InterfaceView()
    {}

    /**
     * @brief ~InterfaceView Destructor of InterfaceView
     */
    virtual ~InterfaceView()
    {}

    /**
     * @brief displayGameStart Display a little message for the presentation of the game "at start".
     */
    virtual void displayGameStart() = 0;

    /**
     * @brief displayTurn display at wich turn it is.
     */
    virtual void displayTurn(bool) = 0;

    /**
     * @brief displayBoard Display the Board "by copy".
     */
    virtual void displayBoard(abalone::Model::Board::Board) = 0;

    /**
     * @brief displayWinner the Winner of the game.
     */
    virtual void displayWinner(int,int) = 0;

    /**
     * @brief displayScore Display the Score during the game.
     */
    virtual void displayScore(int,int) = 0;

    /**
     * @brief askMove ask at the user wich move he want to do and do a lecture of it.
     * @return String wich contains the move that the users want to do.
     */
    virtual std::string askMove() = 0;

    /**
     * @brief displayError display the what of the given exception.
     */
    virtual void displayError(const std::exception &) = 0;
};
}



#endif //_INTERFACEVIEW_H
