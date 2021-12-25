#include "Position.h"


/**
 * Position implementation
 */

using namespace abalone::Model::Position;

/**
 * @brief Position::Position Constructor of a Position by using a y_ and x_ values.
 * @param x x_ values of the Position.
 * @param y y_ values of the Position.
 */
Position::Position(int x, EnumNumber y) : y_{y},x_{x}
{

    if(x > 10 || x < -1)
    {
        // throw std::invalid_argument("Position Rejected : position out of the board.");
    }

}

/**
 * @brief Position::Position Constructor of a Position by using a old Position and a move.
 * @param p old Position.
 * @param move move to need to be done the old Position to have a new one.
 */
Position::Position(Position&p, int * move) : Position((p.getX()+move[0]),(static_cast<EnumNumber>(p.getY()+move[1])))
{}

/**
 * @brief Position Constructor by default of a Position
 */
Position::Position(): y_{A},x_{0}
{}

/**
* @brief Detructor of a Position
*/
Position::~Position()
{}

/**
 * @brief Position::operator = Operator to copy the value of a Position to a other.
 * @param p Position that we need to copy.
 */
void Position::operator =(Position p)
{
    this->x_=p.getX();
    this->y_=p.getY();
}

/**
 * @brief Position::operator == comparator between 2 position.
 * @param p Position that we need to compare with.
 * @return true, if x and y are the same in both Position.
 */
bool Position::operator ==(Position & p)
{
    return (this->x_==p.x_ && this->y_==p.y_);
}

/**
 * @brief Position::operator - difference betwwen 2 position to know the move done when start at a Position and end at another.
 * @param p Reference of Position.
 * @return Array of int, the X move and Y move to go from a Position to go to the other one.
 */
int * Position::operator -(Position &p){
    int * tab = new int [2];
    tab[0]=this->getX()-p.getX();
    tab[1]=this->getY()-p.getY();
    return tab;
}
