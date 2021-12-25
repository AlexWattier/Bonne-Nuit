/**
 * Project Abalone
 */

#include "View.h"

using namespace tui::View;

/**
 * View implementation
 */

/**
 * @brief View::View Contructor of View.
 */
View::View() {
}

/**
 * @brief View::displayGameStart Display a little message for the presentation of the game "at start".
 */
void View::displayGameStart() {
    std::cout << "Color's Rules : "<<std::endl;
    std::cout << "  - O = Black Player"<<std::endl;
    std::cout << "  - X = White Player"<<std::endl;
}

/**
 * @brief View::displayBoard Display the Board "by copy".
 */
void View::displayBoard(abalone::Model::Board::Board board) {
    std::cout << " Board : "<< std::endl;
    std::cout << "            _ _ _ _ _"<<std::endl;
    for (int i = 0; i < this->size_+2; i++) {
        switch (i) {
        case 0:
            std::cout << "        1--/";
            this->displayInsideBoard(board, i);
            std::cout << "\\";
            break;
        case 1:
            std::cout << "       2--/";
            this->displayInsideBoard(board, i);
            std::cout << "\\";
            break;
        case 2:
            std::cout << "      3--/";
            this->displayInsideBoard(board, i);
            std::cout << "\\";
            break;
        case 3:
            std::cout << "     4--/";
            this->displayInsideBoard(board, i);
            std::cout << "\\";
            break;
        case 4:
            std::cout << "    5--(";
            this->displayInsideBoard(board, i);
            std::cout << ")";
            break;
        case 5:
            std::cout << "     6--\\";
            this->displayInsideBoard(board, i);
            std::cout << "/\\";
            break;
        case 6:
            std::cout << "      7--\\" ;
            this->displayInsideBoard(board, i);
            std::cout << "/\\ I";
            break;
        case 7:
            std::cout << "       8--\\" ;
            this->displayInsideBoard(board, i);
            std::cout << "/\\ H";
            break;
        case 8:
            std::cout << "        9--\\" ;
            this->displayInsideBoard(board, i);
            std::cout << "/\\ G";
            break;
        case 9:
            std::cout << "             \\ \\ \\ \\ \\ F";
            break;
        case 10:
            std::cout << "              A B C D E";
            break;
        }
        std::cout<<""<<std::endl;
    }
}

/**
 * @brief View::displayInsideBoard Display the inside of the Board.
 * @param board board from displayBoard.
 * @param i row where we are.
 */
void View::displayInsideBoard(abalone::Model::Board::Board& board, int i){
    abalone::Model::Position::Position position;
    for (int j = 0; j < this->size_; j++) {
        position = abalone::Model::Position::Position(i, static_cast<abalone::Model::Position::EnumNumber>(j));
        if(board.isInside(position)){
            if(board.isInBoard(position)){
                if(board.getCase(position).getState()==abalone::Model::Board::StateCase::WHITE){
                    std::cout<<"X";
                }else if(board.getCase(position).getState()==abalone::Model::Board::StateCase::BLACK){
                    std::cout<<"O";
                }else if(board.getCase(position).getState()==abalone::Model::Board::StateCase::EMPTY){
                    std::cout<<".";
                }
            }
            if(board.isInBoard(position)){
                position = abalone::Model::Position::Position(i, static_cast<abalone::Model::Position::EnumNumber>(j+1));
                if(board.isInside(position)){
                    if(board.isInBoard(position)){
                        position = abalone::Model::Position::Position(i+1, static_cast<abalone::Model::Position::EnumNumber>(j));
                        if(!board.isInside(position)){
                            std::cout<<"_";
                        }else{
                            std::cout<<" ";
                        }
                    }
                }
            }
        }
    }
}

/**
 * @brief View::displayTurn display at wich turn it is.
 * @param turnBlack bool of who is at the turn. Black turn = true, White turn = false.
 */
void View::displayTurn(bool turnBlack){
    std::cout << "Turn : ";
    if(turnBlack){
        std::cout << "Black "<<std::endl;
    }else{
        std::cout << "White "<<std::endl;
    }
}

/**
 * @brief View::displayWinner displayWinner the Winner of the game.
 * @param CountBlackBall Counter of all black ball that had fallen.
 * @param CountWhiteBall Counter of all white ball that had fallen.
 */
void View::displayWinner(int CountBlackBall,int CountWhiteBall){
    std::cout << "WINNER Player ";
    if(CountBlackBall==6)
    {
        std::cout << "White";
    } else if(CountWhiteBall==6)
    {
        std::cout << "Black";
    } else {
        std::cout <<"Game should not be finished.";
    }
}

/**
 * @brief View::displayScore Display the Score during the game.
 * @param CountBlackBall Counter of all black ball that had fallen.
 * @param CountWhiteBall Counter of all white ball that had fallen.
 */
void View::displayScore(int CountBlackBall,int CountWhiteBall){
    std::cout << "Score : " <<std::endl;
    std::cout << "  "<< CountBlackBall << " Black ball have fallen " <<std::endl;
    std::cout << "  "<< CountWhiteBall << " White ball have fallen " <<std::endl;
    std::cout << std::endl;
}

/**
 * @brief ask at the user wich move he want to do and do a lecture of it.
 * @return String wich contains the move that the users want to do.
 */
std::string View::askMove(){
    std::string orderReceived;
    std::cout << "  Move Wanted : ";
    std::cin >> orderReceived;
    std::cout<< std::endl;
    return orderReceived;
}

/**
 * @brief View::displayError display the what of the given exception.
 * @param e exception gived by the controller.
 */
void View::displayError(const std::exception & e)
{
    std::cout<< e.what() << std::endl;
}
