#ifndef _CASE_H
#define _CASE_H
#include "Position.h"

namespace abalone::Model::Board {

/**
 * @brief The StateCase enum Enume of all the State of a Case.
 */
enum StateCase {WHITE=1,BLACK,EMPTY,OUT};

/**
 * @brief The Case class Case that will be in the Board.
 */
class Case {
private:
    abalone::Model::Position::Position position_;
    StateCase state_;

public: 

    Case(abalone::Model::Position::Position&&,StateCase);

    Case(const int,const abalone::Model::Position::EnumNumber,const StateCase);

    Case();

    ~Case();

    /**
     * @brief getState Getter of state_ attributs of the Case.
     * @return a StateCase value.
     */
    inline StateCase getState(){
        return this->state_;
    }

    /**
     * @brief setState Setter of State.
     * @param newState New State of the case.
     */
    inline void setState(StateCase newState){
        this->state_ = newState;
    }

    bool operator==(StateCase &);
};
}

#endif //_CASE_H
