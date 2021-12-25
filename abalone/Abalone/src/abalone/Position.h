#ifndef _POSITION_H
#define _POSITION_H

#include <stdexcept>

namespace abalone::Model::Position {

/**
 * @brief The EnumNumber enum Enumeration of a values of a Position
 */
enum EnumNumber {A=0, B, C, D, E, F, G, H, I};

/**
 * @brief The Position class represents a Position on the board.
 */
class Position
{

private :
    EnumNumber y_;
    int x_;

public :

    Position(int,EnumNumber);
    Position(Position&, int*);
    Position();
    ~Position();

    /**
     * @brief getX Getter of X value of the Position.
     * @return int x value of Position.
     */
    inline int getX(){
        return this->x_;
    }

    /**
     * @brief getY Getter of Y value of the Position.
     * @return EnumNumber y value of Position.
     */
    inline EnumNumber getY(){
        return this->y_;
    }

    void operator =(Position p);

    bool operator ==(Position & p);

    int * operator -(Position &p);
};

}
#endif //_POSITION_H
