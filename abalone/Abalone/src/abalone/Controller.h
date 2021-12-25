#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "Model.h"
#include "InterfaceView.h"

namespace abalone::Controlleur {

/**
 * @brief The Controller class Controller of the game control the game data and the game display.
 */
class Controller {
public:

    Controller(abalone::Model::Model &, abalone::view::InterfaceView &);

    ~Controller();

    void start();
    void move(std::string);

private:

    abalone::Model::Model * game_;

    abalone::view::InterfaceView * view_;

};
}


#endif //_CONTROLLER_H
