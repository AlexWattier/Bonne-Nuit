#ifndef _MODEL_H
#define _MODEL_H

#include "BoardRules.h"

namespace abalone::Model {

/**
 * @brief The Model class Mother class of everyType of Game that should be Herited.
 */
class Model {

protected:

    unsigned countBlackBallOut_; // Need 6 for a White Winners.
    unsigned countWhiteBallOut_; // Need 6 for a Black Winners.
    bool blackTurn_;
    abalone::Model::BoardRules::BoardRules boardRules_;

    /**
     * @brief addCountBlackBallOut_ add one to countBlackBallOut_.
     */
    inline void addCountBlackBallOut_()
    {
        this->countBlackBallOut_++;
    }

    /**
     * @brief addCountWhiteBall_ add one to countWhiteBallOut_
     */
    inline void addCountWhiteBall_()
    {
        this->countWhiteBallOut_++;
    }

public:

    Model();

    virtual ~Model();

    /**
     * @brief getCountBlackBall_ Getter of countBlackBallOut_
     * @return a unsigned value.
     */
    inline unsigned getCountBlackBall_()
    {
        return this->countBlackBallOut_;
    }

    /**
     * @brief getcountWhiteBall_ Getter of countWhiteBallOut_
     * @return a unsigned value.
     */
    inline unsigned getcountWhiteBall_()
    {
        return this->countWhiteBallOut_;
    }

    /**
     * @brief getTurn Getter of blackTurn_
     * @return true if black need to play or false if it is at white player to play.
     */
    inline bool isBlackTurn()
    {
        return this->blackTurn_;
    }

    /**
     * @brief getBoardRules Getter of BoardRules.
     * @return a copy of BoardRules.
     */
    inline abalone::Model::BoardRules::BoardRules getBoardRules()
    {
        return this->boardRules_;
    }

    /**
     * @brief endTurn change the value of blackTurn_.
     */
    inline void endTurn()
    {
        this->blackTurn_=!this->blackTurn_;
    }

    virtual bool endGame() = 0;

    virtual bool moveChooser(std::string &) = 0;
};

}

#endif //_MODEL_H
