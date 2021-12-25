#include "Board.h"

/**
 * Board implementation
 */

using namespace abalone::Model::Board;

/**
 * @brief Board::Board Constructor of a Board.
 */
Board::Board()
{
    for(unsigned x = 0; x<9;x++)
    {
        for(unsigned y=0;y<9;y++)
        {
            if((x==4) ||
                    (x==3 && y>0) ||
                    (x==5 && y<8) ||
                    (x==6 && (y==0 || y==1 || y==5 || y==6)) ||
                    (x==2 && (y==2 || y==3 || y ==7|| y==8)))
            {
                this->board_[x][y]=Case(abalone::Model::Position::Position(x,static_cast<abalone::Model::Position::EnumNumber>(y)),EMPTY);
            }
            else
            {
                if((x==1 && y>2) ||
                        (x==0 && y>3) ||
                        (x==2 && y>3 && y<7))
                {
                    this->board_[x][y]= Case(abalone::Model::Position::Position(x,static_cast<abalone::Model::Position::EnumNumber>(y)),WHITE);
                }
                else
                {
                    if((x==7 && y<6)||
                            (x==8 && y<5) ||
                            (x==6 && y>1 && y<5))
                    {
                        this->board_[x][y]=Case(abalone::Model::Position::Position(x,static_cast<abalone::Model::Position::EnumNumber>(y)),BLACK);
                    }
                    else
                    {
                        this->board_[x][y]=Case(abalone::Model::Position::Position(x,static_cast<abalone::Model::Position::EnumNumber>(y)),OUT);
                    }
                }
            }
        }
    }
}

/**
 * @brief Board::~Board Destructors of Board.
 */
Board::~Board(){}


/**
 * @brief Board::move change the StateCase of the Case at given Position by moving one StateCase to a other.
 * @param oldPosition The old case where the StateCase need to move.
 * @param newPosition The new case where the StateCase is going to be changed.
 * @param pmove move done to be from oldPosition to newPosition.
 * @return return Black or White if a ball fall and empty otherwise.
 */
StateCase Board::move(abalone::Model::Position::Position& oldPosition,abalone::Model::Position::Position& newPosition, int * pmove){
    StateCase falledBall;
    if(!this->isInside(newPosition)|| this->getCase(newPosition).getState()==OUT)
    {
        falledBall = this->getCaseToMove(oldPosition)->getState();
        this->getCaseToMove(oldPosition)->setState(EMPTY);
        return falledBall;
    }
    else
    {
        if(this->getCaseToMove(newPosition)->getState()==EMPTY)
        {
            StateCase state = this->getCase(oldPosition).getState();
            this->getCaseToMove(newPosition)->setState(state);
            this->getCaseToMove(oldPosition)->setState(EMPTY);
            return EMPTY;
        }
        else
        {
            abalone::Model::Position::Position newPositionOfNextBall = abalone::Model::Position::Position(newPosition,pmove);
            falledBall = move(newPosition, newPositionOfNextBall,pmove);

            this->getCaseToMove(newPosition)->setState(this->getCase(oldPosition).getState());
            this->getCaseToMove(oldPosition)->setState(EMPTY);

            return falledBall;
        }
    }
}

/**
 * @brief Board::move move of multiple StateCase of a case to a other.
 * @param tabPosition all the old case where we need to move their state to a new one.
 * @param nbMove numbre of old case that we need to move.
 * @param pmove move done from the oldposition to the new one.
 */
void Board::move(abalone::Model::Position::Position * tabPosition,int nbMove,int *pmove)
{
    abalone::Model::Position::Position newPosition;
    for(int index = 0; index < nbMove; index++)
    {
        newPosition=abalone::Model::Position::Position(tabPosition[index],pmove);
        move(tabPosition[index],newPosition, pmove);
    }
}











