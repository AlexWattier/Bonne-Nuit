#ifndef BOARDRULES_H
#define BOARDRULES_H
#include "Board.h"
#include <math.h>
#include <stdexcept>

namespace abalone::Model::BoardRules{
/**
 * @brief The BoardRules class is the class that we need to go trought when we come from game to Board and in
 * BoardRules we need to go trought a lot of bool method to verify if our move is valid.
 */
class BoardRules {

private:
    abalone::Model::Board::Board board_;

    void moveArgumentsVerification(abalone::Model::Position::Position &, abalone::Model::Position::Position&, bool);

    bool verifMove(int*,int);

    int findIndexMove(abalone::Model::Position::Position &, abalone::Model::Position::Position &);

    int * findMove(abalone::Model::Position::Position&, abalone::Model::Position::Position &);

    bool isYourBall(abalone::Model::Position::Position&,bool);

    bool canPush(abalone::Model::Position::Position&,int *);

    bool willPush(abalone::Model::Position::Position *,int ,int *);

    int ballSelection(abalone::Model::Position::Position &, abalone::Model::Position::Position &, abalone::Model::Position::Position *);

    bool verifMiddlePosition(double * moveWanted,int index);
public:

    BoardRules();

    ~BoardRules();

    /**
     * @brief getBoard getter of board_
     * @return Board the instance of Board that we currently playing with.
     */
    inline abalone::Model::Board::Board getBoard(){
        return board_;
    }

    abalone::Model::Board::StateCase move (abalone::Model::Position::Position &,abalone::Model::Position::Position &,bool);

    void move (abalone::Model::Position::Position &,abalone::Model::Position::Position &,abalone::Model::Position::Position &,bool);




};
}
#endif // BOARDRULES_H


