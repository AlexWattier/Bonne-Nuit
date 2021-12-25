#ifndef _GAME_H
#define _GAME_H

#include "Model.h"

namespace abalone::Model{

/**
 * @brief The Game class is where We will verify everything that will be done in game. Every input Update scores, ...
 */
class Game: public Model {
private:

    bool move (abalone::Model::Position::Position &,abalone::Model::Position::Position &);

    bool move (abalone::Model::Position::Position &,abalone::Model::Position::Position &,abalone::Model::Position::Position &);

    void updateFallenBalls(abalone::Model::Board::StateCase);

    int * stringTranslation(std::string);

    void charInverser(std::string &);

    void inputControl(std::string &);

public:

    Game();

    ~Game();

    bool moveChooser(std::string &) override;

    bool endGame() override;


};
}

#endif //_GAME_H
