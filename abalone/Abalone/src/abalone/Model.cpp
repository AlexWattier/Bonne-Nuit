#include "Model.h"

using namespace abalone::Model;

/**
 * @brief Model::Model Constructor of Model.
 */
Model::Model() {
    countBlackBallOut_=0;
    this->countWhiteBallOut_=0;
    this->blackTurn_=true;
    this->boardRules_=abalone::Model::BoardRules::BoardRules();
}

/**
 * @brief Model::~Model Destructor of Model
 */
Model::~Model(){

}


