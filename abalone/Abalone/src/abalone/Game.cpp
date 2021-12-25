/**
 * Project Abalone
 */

#include "Game.h"

using namespace abalone::Model;

/**
 * Game implementation
 */
/**
 * @brief Game::Game Constructor of Game
 */
Game::Game(){

}

/**
 * @brief Game::~Game Destructor of Game
 */
Game::~Game(){

}

/**
 * @brief Game::moveChooser will analyse the input and chose a specify move to do.
 * @param position input with all the position in it.
 * @return boolean so if a move is done we know it and false if there is no move done.
 */
bool Game::moveChooser(std::string & position) {
    bool didMove = true;
    this->inputControl(position);
    int * tab = this->stringTranslation(position);
    switch(position.size())
    {
    case 4:
    {
        int tabPositionValues [] = {tab[0],tab[1],tab[2],tab[3]};
        delete(tab);
        abalone::Model::Position::Position oldPosition = abalone::Model::Position::Position(tabPositionValues[0],static_cast<abalone::Model::Position::EnumNumber>(tabPositionValues[1]));
        abalone::Model::Position::Position newPosition = abalone::Model::Position::Position(tabPositionValues[2],static_cast<abalone::Model::Position::EnumNumber>(tabPositionValues[3]));
        didMove = this->move(oldPosition,newPosition);
        break;
    }
    case 6:
    {
        int tabPositionValues [] = {tab[0],tab[1],tab[2],tab[3],tab[4],tab[5]};
        delete(tab);
        abalone::Model::Position::Position oldStartPosition = abalone::Model::Position::Position(tabPositionValues[0],static_cast<abalone::Model::Position::EnumNumber>(tabPositionValues[1]));
        abalone::Model::Position::Position oldEndPosition = abalone::Model::Position::Position(tabPositionValues[2],static_cast<abalone::Model::Position::EnumNumber>(tabPositionValues[3]));
        abalone::Model::Position::Position newPosition = abalone::Model::Position::Position(tabPositionValues[4],static_cast<abalone::Model::Position::EnumNumber>(tabPositionValues[5]));
        didMove = this->move(oldStartPosition,oldEndPosition,newPosition);
        break;
    }
    default:
    {
        delete(tab);
        throw std::invalid_argument("Input not in good Format.");
    }
    }
    return didMove;
}

/**
 * @brief Game::stringTranslation create a array wich is the string but seperated in int.
 * @param position user input.
 * @return Pointer to a array of every value for all the needed Position.
 */
int * Game::stringTranslation(std::string position){
    int * tab = new int [position.size()];
    for(int index=0;index<static_cast<int>(position.size());index++)
    {
        if(index%2==0)
        {
            tab[index] = static_cast<int>(position.at(index)-'1');
        }
        else {
            if(position.at(1)<'A')
                tab[index] = static_cast<abalone::Model::Position::EnumNumber>(toupper(position.at(index))-'A');
            else
                tab[index] = static_cast<abalone::Model::Position::EnumNumber>(position.at(index)-'A');
        }
    }
    return tab;
}

/**
 * @brief Game::endGame Boolean method wich verify if the game is finished or not.
 * @return True if the game is finish (if one of countBlackBallOut_ or countWhiteBallOut_ are equal 6.
 */
bool Game::endGame() {
    if(this->countBlackBallOut_ == 6 || this->countWhiteBallOut_==6)
        return true;
    return false;
}

/**
 * @brief Game::move move in one row where we can push.
 * @param oldPosition Position where we start.
 * @param newPosition Position where we should end.
 * @return true if the move is done to the end ans should throw an exception in every other cases.
 */
bool Game::move (abalone::Model::Position::Position & oldPosition,abalone::Model::Position::Position & newPosition){
    abalone::Model::Board::StateCase statecase = this->boardRules_.move(oldPosition,newPosition,this->isBlackTurn());
    this->updateFallenBalls(statecase);
    return true;
}

/**
 * @brief Game::move move a selection of balls, 3 max and move them in diagonals.
 * @param oldStartPosition Position where we start the selection.
 * @param oldEndPosition Position where we end the selection.
 * @param newPosition the New Position of the start of the selection to know the movement that we will do for everyone of them.
 * @return true if the move is done to the end ans should throw an exception in every other cases.
 */
bool Game::move (abalone::Model::Position::Position & oldStartPosition,abalone::Model::Position::Position & oldEndPosition,abalone::Model::Position::Position & newPosition){
    this->boardRules_.move(oldStartPosition,oldEndPosition,newPosition,this->isBlackTurn());
    return true;
}

/**
 * @brief Game::updateFallenBalls Update the Score when there's a ball that has fallen
 * @param stateCase type of the ball that has fall or EMPTY if there's no ball that had fallen.
 */
void Game::updateFallenBalls(abalone::Model::Board::StateCase stateCase){
    if(stateCase==abalone::Model::Board::BLACK){
        this->addCountWhiteBall_();
    }
    if(stateCase==abalone::Model::Board::WHITE){
        this->addCountBlackBallOut_();
    }
}

/**
 * @brief Game::inputControl Controlle if the input is correct or not. And if it's in the good orders.
 * @param position string wich is the input of the users.
 */
void Game::inputControl(std::string & position)
{
    if(4==static_cast<int>(position.size()))
    {
        if(toupper(position[0])-'A' >= 0 && toupper(position[2])-'A' >= 0)
        {
            this->charInverser(position);
        }
        return;
    }
    else if(6==static_cast<int>(position.size()))
    {
        if(toupper(position[0])-'A' >= 0 && toupper(position[2])-'A' >= 0 && toupper(position[4])-'A' >= 0 )
        {
            this->charInverser(position);
        }
        return;
    }
    throw std::invalid_argument("Input invalid");
}

/**
 * @brief Game::charInverser inverse in a String 0 with 1, 2 with 3, ...
 * @param position String input by users.
 */
void Game::charInverser(std::string & position)
{
    char temp;
    for(int index=0;index<static_cast<int>(position.size());index=index+2)
    {
        temp=position[index];
        position[index]=position[index+1];
        position[index+1]=temp;
    }
}
