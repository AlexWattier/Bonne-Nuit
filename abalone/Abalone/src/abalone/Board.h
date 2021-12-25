#ifndef _BOARD_H
#define _BOARD_H
#include "Position.h"
#include "Case.h"

namespace abalone::Model::Board {

int const movement [6][2] = {{0,1},{0,-1},{1,0},{-1,0},{1,-1},{-1,1}}; // Ce sont les 6 movements qu'un boule peux potentiellement faire. (X,Y)

/**
 * @brief The Board class Board on where the player are going to play against each other.
 */
class Board {
private:
    Case board_[9][9];

    /**
     * @brief Getter of a address of the case at the given Position.
     * @param p Position where we need to get the address of the case.
     * @return Return adresse of Case wich is contain in the board_.
     */
    inline Case * getCaseToMove(abalone::Model::Position::Position & p)
    {
        return &this->board_[p.getX()][p.getY()];
    }

public:

    Board();

    ~Board();

    /**
     * @brief getCase Getter of a case on a given Position
     * @param p Position where we need to get the case.
     * @return Return a copy of Case wich is contain in the board_.
     */
    inline Case getCase(abalone::Model::Position::Position & p)
    {
        return this->board_[p.getX()][p.getY()];
    }

    /**
     * @brief isInBoard Boolean method to know if a given position is on the board.
     * @param p Given position to watch.
     * @return true if the state of the Case at the position p is BLACK,WHITE or EMPTY and false otherwise.
     */
    inline bool isInBoard(abalone::Model::Position::Position &p)
    {
        return !(this->getCase(p).getState()==OUT);
    }

    /**
     * @brief isInside Boolean method to know if a given position is in the array of the board.
     * @param p Given position to watch.
     * @return true if p.x and p.y are lower than 9 and false otherwise.
     */
    inline bool isInside(abalone::Model::Position::Position &p)
    {
        return (p.getX()<9 && p.getY()<9 && p.getX()>=0 && p.getY()>=0);
    }

    StateCase move(abalone::Model::Position::Position&,abalone::Model::Position::Position&,int * );

    void move(abalone::Model::Position::Position *, int,int *);



};
}

#endif //_BOARD_H
