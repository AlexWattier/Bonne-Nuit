#ifndef BOARD_HPP
#define BOARD_HPP

#include "Position.hpp"
#include "Case.hpp"

namespace goodNigth::Model::Board {

int const movement [6][2] = {{0,1},{0,-1},{1,0},{-1,0},{1,-1},{-1,1}}; // Ce sont les 6 movements qu'un boule peux potentiellement faire. (X,Y)

/**
 * @brief The Board class Board on where the player are going to play against each other.
 */
class Board {
private:
    Case board_[9][9];


public:

    Board();

    ~Board();

};
}


#endif // BOARD_HPP
