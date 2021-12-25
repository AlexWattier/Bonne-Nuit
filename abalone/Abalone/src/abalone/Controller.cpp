/**
 * Project Abalone
 */

#include "Controller.h"

using namespace abalone::Controlleur;

/**
 * @brief Controller::Controller Constructor of a Controller.
 * @param md Instance of Model that contains all the data of the game.
 * @param view Instance of a View that we will use to display the game.
 */
Controller::Controller(abalone::Model::Model & md, abalone::view::InterfaceView & view): game_{&md},view_{&view}
{}

/**
 * @brief Controller::~Controller Destructor of Controller.
 */
Controller::~Controller()
{}

/**
 * @brief Controller::start Start the game, we stay in this method until the end of the game.
 */
void Controller::start() {
    bool didMove = false;
    int counting;
    this->view_->displayGameStart();
    while(!this->game_->endGame())
    {
        counting=0;
        didMove = false;
        this->view_->displayBoard((this->game_->getBoardRules().getBoard()));
        this->view_->displayTurn((this->game_->isBlackTurn()));
        while(!didMove)
        {
            if(counting > 5)
            {
                this->view_->displayBoard(this->game_->getBoardRules().getBoard());
                counting=0;
            }
            try {
                std::string moveValues=this->view_->askMove();
                didMove = this->game_->moveChooser(moveValues);
                this->view_->displayScore(this->game_->getCountBlackBall_(),this->game_->getcountWhiteBall_());
            } catch (const std::exception& e) {
                this->view_->displayError(e);
                counting++;
            }
        }

    }
    this->view_->displayWinner(this->game_->getCountBlackBall_(),this->game_->getcountWhiteBall_());
}

/**
 * @brief Controller::move Start the gui game, we stay in this method until the end of the game.
 */
void Controller::move(std::string moveValues){
    bool didMove = false;
    try {
        didMove = this->game_->moveChooser(moveValues);
    } catch (const std::exception& e) {
        this->view_->displayError(e);
    }
    if(didMove)
    {
        this->game_->endTurn();
        //this->view_->displayTurn((this->game_->isBlackTurn()));
    }
    if(this->game_->endGame())
    {
        this->view_->displayWinner(this->game_->getCountBlackBall_(),this->game_->getcountWhiteBall_());
    }
}
