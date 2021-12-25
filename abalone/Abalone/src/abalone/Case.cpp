#include "Case.h"

/**
 * Case implementation
 */
using namespace abalone::Model::Board;

/**
 * @brief Case::Case Constructor of Case by using a Reference of Position and a State.
 * @param position Position of the case.
 * @param state StateCase of the case.
 */
Case::Case(abalone::Model::Position::Position && position,const StateCase state) : position_(std::move(position)), state_(state)
{}

/**
 * @brief Case::Case Constructor of Case by using a x and y value and a State.
 * @param x X values of the Positions of the case.
 * @param y Y values of the Positions of the case.
 * @param state StateCase of the case.
 */
Case::Case(const int x,const abalone::Model::Position::EnumNumber y,const StateCase state = StateCase::OUT) : Case(abalone::Model::Position::Position(x,y),state)
{}

/**
 * @brief Case Contructor by default of a Case.
 */
Case::Case() : position_{},state_{OUT}
{};

/**
* @brief ~Case Destructor of Case.
*/
Case::~Case(){}

/**
 * @brief Case::operator == Change operator to compare 2 StateCase.
 * @param state StateCase to compare with.
 * @return True if each the 2 Statecase are the same.
 */
bool Case::operator==(StateCase &state)
{
    return this->state_ == state;
}
