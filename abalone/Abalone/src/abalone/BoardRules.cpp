#include "BoardRules.h"
// PUBLIC METHODS

/**
 * BoardRules implementation
 */

using namespace abalone::Model::BoardRules;

/**
 * @brief BoardRules::BoardRules Contructor of BoardRules.
 */
BoardRules :: BoardRules(){
    this->board_ = abalone::Model::Board::Board();
}

/**
 * @brief BoardRules::~BoardRules Destructor of BoardRules.
 */
BoardRules ::~BoardRules(){}

/**
 * @brief BoardRules::move Test if the move is valid and if it is than it do it for real.
 * @param oldPosition The old case where the StateCase need to move.
 * @param newPosition The new case where the StateCase is going to be changed.
 * @param blackTurn bool to know if it's the turn of the white team or black team.
 */
abalone::Model::Board::StateCase BoardRules::move(abalone::Model::Position::Position & oldPosition, abalone::Model::Position::Position & newPosition, bool blackTurn){

    moveArgumentsVerification(oldPosition,newPosition,blackTurn);

    int * pmove = findMove(oldPosition,newPosition);

    abalone::Model::Board::StateCase falledBall = abalone::Model::Board::EMPTY;

    if(canPush(oldPosition,pmove))
        falledBall = this->board_.move(oldPosition,newPosition,pmove);


    return falledBall;
}

/**
 * @brief BoardRules::move Test if the move is valid and if it is than it do it for real.
 * @param oldStartPositon The old case of the start of a group where the StateCase need to move.
 * @param oldEndPosition The old case of the end of a group where the StateCase need to move.
 * @param newPosition The new case of oldStartPosition.
 * @param blackTurn bool to know if it's the turn of the white team or black team.
 */
void BoardRules::move(abalone::Model::Position::Position& oldStartPositon,abalone::Model::Position::Position& oldEndPosition,abalone::Model::Position::Position& newPosition, bool blackTurn)
{
    moveArgumentsVerification(oldStartPositon,newPosition,blackTurn);

    int * pmove = findMove(oldStartPositon,newPosition);

    abalone::Model::Position::Position tabPosition [3];

    int nbMove = ballSelection(oldStartPositon, oldEndPosition, tabPosition);

    for(int index=0;index < nbMove; index++)
    {
        if(!isYourBall(tabPosition[index],blackTurn))
            throw std::invalid_argument("Incorrect Selection : One of the selected balls is not yours.");
    }
    if(willPush(tabPosition,nbMove,pmove))
        throw std::invalid_argument("Move Refused : You're not able to push when you use a move by straffing multiple balls.");

    this->board_.move(tabPosition,nbMove,pmove);
}


// ------------------------------------------------------
// PRIVATE METHODS

/**
 * @brief BoardRules::findMove Find the "Movement" used. It throw a invalid_argument if there is no "Movement" used because than it's a Invalid move.
 * @param oldPosition Position where we start.
 * @param newPostion Position where we end.
 * @return a Pointeur of the table of the move (x,y).
 */
int * BoardRules::findMove(abalone::Model::Position::Position &oldPosition, abalone::Model::Position::Position &newPostion){
    int indexmovement = findIndexMove(oldPosition, newPostion);
    if(indexmovement<0)
        throw std::invalid_argument("Move Refused : Unknown Move");
    int * pmove = (int *)abalone::Model::Board::movement[indexmovement];
    return pmove;
}

/**
 * @brief Board::findIndexMove Find the index of a const move in the movement int const table.
 * @param oldPosition Position where we start.
 * @param newPosition Position where we end.
 * @return the index of the move done in the movement table.
 */
int BoardRules::findIndexMove(abalone::Model::Position::Position & oldPosition, abalone::Model::Position::Position & newPosition){
    int index;
    int * moveWanted = newPosition-oldPosition;
    for(index = 0; index < 6;index++)
    {
        if(verifMove(moveWanted,index))
        {
            delete(moveWanted);
            return index;
        }

    }
    delete(moveWanted);
    return -1;
}

/**
 * @brief BoardRules::verifMove Verify if the move wanted by the user is equals to the move in movement at the given index.
 * @param moveWanted move that the users want.
 * @param index index of a move in const table "movement".
 * @return true if the value in movement at the index is equals to the movewanted false otherwise.
 */
bool BoardRules::verifMove(int * moveWanted,int index)
{
    int * pmove = (int *) abalone::Model::Board::movement[index];
    if(moveWanted[0]==pmove[0] && moveWanted[1]==pmove[1])
        return true;
    return false;
}

/**
 * @brief BoardRules::verifMiddlePosition Verify if the position of the middle ball of a Selection in just near ball from the start of the selection.
 * @param middlePositionValuesFromStart move needed to verify if from the start the ball, is the select ball just near it.
 * @param index index of a move in const table "movement".
 * @return true if the value in movement at the index is equals to the movewanted false otherwise.
 */
bool BoardRules::verifMiddlePosition(double * middlePositionValuesFromStart,int index)
{
    int * pmove = (int *) abalone::Model::Board::movement[index];
    if(static_cast<int>(middlePositionValuesFromStart[0])==pmove[0] && static_cast<int>(middlePositionValuesFromStart[1])==pmove[1])
        return true;
    return false;
}

/**
 * @brief BoardRules::moveRules Verify multiple thing about the oldPosition and the new one. Like if the oldPosition is really on the board and not out and if it's in than is the ball
 * a this position from his team ? and for the end test if the newPosition is the array named board_. For all 3 if it's false than throw a Exceptions.
 * @param oldPosition Position that we start on.
 * @param newPosition Position that we need to finish on.
 * @param blackTurn bool to know if it's the turn of the white team or black team.
 */
void BoardRules::moveArgumentsVerification(abalone::Model::Position::Position & oldPosition, abalone::Model::Position::Position& newPosition, bool blackTurn){
    if(!this->board_.isInBoard(oldPosition))
        throw std::invalid_argument("Incorrect value of initial position : Position not on the Board");
    if(!isYourBall(oldPosition,blackTurn))
        throw std::invalid_argument("Incorrect value of initial position : Not your ball.");
    if(!this->board_.isInBoard(newPosition))
        throw std::invalid_argument("Incorrect value of the new position : Position not on the Board");
}

/**
 * @brief BoardRules::isYourBall Check if at a given position that the StateCase if your team color and not.
 * @param p Position that we need to check the State.
 * @param blackTurn bool to know if it's the turn of the white team or black team.
 * @return True if we're on a Black StateCase and it's black turn, if we're on a White StateCase and it's not black turn and false otherwise.
 */
bool BoardRules::isYourBall(abalone::Model::Position::Position& p,bool blackTurn){
    if((blackTurn && this->board_.getCase(p).getState()==abalone::Model::Board::BLACK)
            || (!blackTurn && this->board_.getCase(p).getState()==abalone::Model::Board::WHITE))
        return true;
    if(this->board_.getCase(p).getState()==abalone::Model::Board::EMPTY)
        throw std::invalid_argument("Incorrect value of initial position : There's no ball");
    return false;
}




/**
 * @brief BoardRules::canPush Check if we are can push the balls in front of us. Our team need to be more than the other. And there can't be our team behind the opponents team.
 * @param position Position where we start the simulation of pushing.
 * @param pmove "movement" used to do our move.
 * @return true if we can push and false if we can't.
 */
bool BoardRules::canPush(abalone::Model::Position::Position & position, int * pmove){

    abalone::Model::Position::Position p = abalone::Model::Position::Position(position,pmove);
    abalone::Model::Board::StateCase myteamColor = board_.getCase(position).getState();
    unsigned myteam = 1;
    unsigned otherteam = 0;

    while((board_.getCase(p).getState()==abalone::Model::Board::WHITE || board_.getCase(p).getState()==abalone::Model::Board::BLACK) && myteam >= otherteam)
    {
        if(board_.getCase(p).getState()==myteamColor)
        {
            if(otherteam==0)
                myteam++;
            else
            {
                throw std::invalid_argument("Move Refused : Can't push opponent ball when there's one of you own ball just behind them.");
            }
        }
        else
            otherteam++;
        p = abalone::Model::Position::Position(p,pmove);
    }

    if(myteam >= 4)
    {
        throw std::invalid_argument("Move Refused : Can't move more than 3 balls of your own balls \"by pushing\"."
                                    " You try to move " + std::to_string(myteam) + "\" by pushing\".");
    }

    if(myteam > otherteam)
    {
        return true;
    }
    else
    {
        throw std::invalid_argument("Move Refused : Can't push because you've less or same number of balls than your opponent : "
                                   "Your (" + std::to_string(myteam) + "), Opponement (" + std::to_string(otherteam)+").");
    }

}

/**
 * @brief BoardRules::ballSelection check if there's 2 or 3 ball in the lign selection when we do a multiple straff.
 * @param oldStartPositon Start of the oldPosition.
 * @param oldEndPosition End of the oldPosition.
 * @param tabPosition Table that we full in with all the position that we'll move after.
 * @return int the number of Position that we need to move.
 */
int BoardRules::ballSelection(abalone::Model::Position::Position & oldStartPositon,abalone::Model::Position::Position & oldEndPosition,abalone::Model::Position::Position * tabPosition){
    bool goodSelection = false;
    int * middlePosValues = oldEndPosition-oldStartPositon;
    double middleValues []= {static_cast<double>(middlePosValues[0]),static_cast<double>(middlePosValues[1])};
    delete(middlePosValues);
    middleValues[0]=ceil(middleValues[0]/2);
    middleValues[1]=ceil(middleValues[1]/2);
    if((middleValues[0]==0 && middleValues[1]==0))
    {
        goodSelection=true;
    } else {
        for(int index = 0; index < 6;index++)
        {
            if(verifMiddlePosition(middleValues,index))
            {
                goodSelection=true;
                index=6;
            }
        }
    }

    if(!goodSelection)
    {
        throw std::invalid_argument("Move Refused : Can't Select more than 3 balls.");
    }
    int pointerIntMiddleValues [] = {static_cast<int>(middleValues[0]),static_cast<int>(middleValues[1])};
    abalone::Model::Position::Position middleOldPosition=abalone::Model::Position::Position(oldStartPositon,pointerIntMiddleValues);
    unsigned nbMove;

    if(!(middleOldPosition==oldEndPosition))
    {
        tabPosition [0]= oldStartPositon;
        tabPosition [1]= middleOldPosition;
        tabPosition [2]= oldEndPosition;
        nbMove = 3;
    }
    else
    {
        tabPosition [0]= oldStartPositon;
        tabPosition [1]= oldEndPosition;
        nbMove = 2;
    }
    return nbMove;
}

/**
 * @brief BoardRules::willPush Check if the multiple move are going to push a other balls because here we need to go in a empty case.
 * @param tabPosition all Ball Start Position that we need to check.
 * @param nbMove Number of Ball that we need to check.
 * @param pmove Pointer to the "movement" used.
 * @return true if at least one ball will push and false if any push.
 */
bool BoardRules::willPush(abalone::Model::Position::Position * tabPosition,int nbMove,int * pmove){
    abalone::Model::Position::Position p;
    for(int index = 0; index < nbMove; index++)
    {
        p = abalone::Model::Position::Position (tabPosition[index],pmove);
        if(board_.getCase(p).getState() != abalone::Model::Board::EMPTY && board_.getCase(p).getState() != abalone::Model::Board::OUT)
        {
            return true;
        }
    }
    return false;
}

















