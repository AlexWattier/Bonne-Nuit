#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Game.hpp"
//#include "View.hpp"

namespace goodNigth::Controlleur {

/**
 * @brief The Controller class Controller of the game control the game data and the game display.
 */
class Controller {
public:

    Controller(abalone::Model::Model &);

    ~Controller();

    void start();

private:

    goodNigth::Model::Game * game_;
   // goodNigth::View::View * view_;

};
}


#endif // CONTROLLER_HPP
