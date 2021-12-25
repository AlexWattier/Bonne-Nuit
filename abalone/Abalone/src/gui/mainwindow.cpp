#include "mainwindow.h"
#include "hexacell.h"


using namespace gui::mainwindow;

/**
 * @brief Controller::Controller Constructor of a Controller.
 * @param game Instance of Model that contains all the data of the game.
 */
MainWindow::MainWindow(abalone::Model::Model & game,QWidget *parent): QMainWindow(parent)
{

    this->scene = new QGraphicsScene();
    this->game_ = &game;
    MainWindow::displayInsideBoard( this->game_);
}


/**
 * @brief View::displayInsideBoard Display the inside of the Board.
 * @param game Instance of Model that contains all the data of the game.
 */
void MainWindow::displayInsideBoard(abalone::Model::Model * game)
{
    abalone::Model::Board::Board board = game->getBoardRules().getBoard();
    displayBoard(board);
    displayTurn((this->game_->isBlackTurn()));
    displayScore(this->game_->getCountBlackBall_(),this->game_->getcountWhiteBall_());
    displayAllBall(board);
    this->scene->setBackgroundBrush(Qt::darkGreen);
    QGraphicsView * view = new QGraphicsView(this->scene);

    this->view_ = view;
    this->view_->setRenderHint(QPainter::Antialiasing);
    this->view_->setRenderHint(QPainter::TextAntialiasing);
    this->view_->setCacheMode(QGraphicsView::CacheBackground);
    this->view_->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    this->view_->setDragMode(QGraphicsView::ScrollHandDrag);
    this->view_->update();
    resize(1000, 800);
    this->setCentralWidget( this->view_);
}

/**
 * @brief MainWindow::setController receive the controller of the main.
 * @param  controller controller from the main.
 */
void MainWindow::setController(abalone::Controlleur::Controller *controller)
{
    this->controller_ = controller;
}

/**
 * @brief MainWindow::receivedTouchClick receive the coordinates of the box click.
 */
void MainWindow::receivedTouchClick(std::string commande)
{
    this->commande_= this->commande_ + commande;
    if( this->commande_.length()>=4)
    {
        if(verifCoord6())
        {
            if(this->commande_.length()==6)
            {
                askMove();
                refreshView();
            }
        }else{
            askMove();
            refreshView();
        }
    }
}

/**
 * @brief MainWindow::verifCoord6 check if coordinates are deviated
 */
bool MainWindow::verifCoord6()
{
    std::string stringDx = this->commande_;
    char charDx1 = stringDx.at(0);
    char charDy1 = stringDx.at(1);
    char charDx2 = stringDx.at(2);
    char charDy2 = stringDx.at(3);
    int intDx1 =  convertCoord(charDx1);
    int intDy1 =charDy1-48;
    int intDx2 = convertCoord(charDx2);
    int intDy2 =charDy2 -48;
    int ecartDx = intDx1 - intDx2;
    int ecartDy = intDy1 - intDy2;
    if(ecartDx == 2||ecartDx == -2 || ecartDy== 2||ecartDy == -2){
        return true;
    }
    return false;
}

/**
 * @brief MainWindow::verifCoord6 check if coordinates are deviated
 * @param charCoo char coordinates in the commande
 */
int MainWindow::convertCoord(char charCoo)
{
    int intCoo = 0;
    switch (charCoo) {
    case 'A':intCoo = 0;break;
    case 'B':intCoo = 1;break;
    case 'C':intCoo = 2;break;
    case 'D':intCoo = 3;break;
    case 'E':intCoo = 4;break;
    case 'F':intCoo = 5;break;
    case 'G':intCoo = 6;break;
    case 'H':intCoo = 7;break;
    case 'I':intCoo = 8;break;
    }
    return intCoo;
}



/**
 * @brief MainWindow::refreshView refresh the ball in the View.
 */
void MainWindow::refreshView()
{
    this->commande_= "";
    int nbChildren = this->scene->items().size();
    int nbBall = nbChildren - 61;
    for (auto i = 0; i < nbBall; i++) {
        delete this->scene->items().at(0);
    }
    displayTurn((this->game_->isBlackTurn()));
    displayScore(this->game_->getCountBlackBall_(),this->game_->getcountWhiteBall_());
    displayAllBall(this->game_->getBoardRules().getBoard());

}


/**
 * @brief View::displayBoard Display the Board "by copy".
 * @param  board board from constructor.
 */
void MainWindow::displayBoard(abalone::Model::Board::Board board)
{
    abalone::Model::Position::Position position;
    MainWindow *pthis= this;
    double longLargeur= -8;
    double longHauteur=4;
    for (int i = 0; i < 9; i++) {
        for (int j = 0;j<9 ; j++) {
            position = abalone::Model::Position::Position(i, static_cast<abalone::Model::Position::EnumNumber>(j));
            if(board.isInside(position)){
                if(board.isInBoard(position)){
                    this->scene->addItem(new gui::hexacell::HexaCell( j, i,longLargeur,longHauteur,pthis));
                }
            }
        }
        longLargeur =longLargeur+0.5;
        longHauteur = longHauteur -1;
    }
}
/**
 * @brief  MainWindow::displayAllBall Display all ball in the board.
 * @param  board board from constructor.
*/
void MainWindow::displayAllBall(abalone::Model::Board::Board board)
{
    abalone::Model::Position::Position position;
    double longLargeur= -8;
    double longHauteur=4;
    for (int i = 0; i < 9; i++) {
        for (int j = 0;j<9 ; j++) {
            position = abalone::Model::Position::Position(i, static_cast<abalone::Model::Position::EnumNumber>(j));
            if(board.isInside(position)){
                if(board.isInBoard(position)){
                    abalone::Model::Board::StateCase state = board.getCase(position).getState();
                    if (state == abalone::Model::Board::BLACK)this->scene->addItem(new gui::ball::BlackBall( j, i,longLargeur,longHauteur,state));
                    if (state == abalone::Model::Board::WHITE)this->scene->addItem(new gui::ball::BlackBall( j, i,longLargeur,longHauteur,state));
                }
            }
        }
        longLargeur =longLargeur+0.5;
        longHauteur = longHauteur -1;
    }

}

/**
 * @brief View::displayGameStart Display a little message for the presentation of the game "at start".
 */
void MainWindow::displayGameStart()
{
    QMessageBox displayGameStartBox;
    displayGameStartBox.setIcon(QMessageBox::Information);
    displayGameStartBox.setText("Turn : Black ");
    displayGameStartBox.exec();
}

/**
 * @brief View::displayTurn display at wich turn it is.
 * @param turnBlack bool of who is at the turn. Black turn = true, White turn = false.
 */
void MainWindow::displayTurn(bool turnBlack)
{
    QString turn = "";
    QGraphicsTextItem * textTurn = new QGraphicsTextItem();
    QFont  font = QFont();
    font.setPointSize(20);
    textTurn->setFont(font);
    if(turnBlack){
        turn = "Turn : Black ";
        textTurn->setPlainText(turn);
        textTurn->boundingRect();
    }else{
        turn = "Turn : White ";
        textTurn->setPlainText(turn);
        textTurn->boundingRect();
    }
    textTurn->setPos(-5.5*40, 40*-8);

    this->scene->addItem(textTurn);
}

/**
 * @brief View::displayWinner displayWinner the Winner of the game.
 * @param CountBlackBall Counter of all black ball that had fallen.
 * @param CountWhiteBall Counter of all white ball that had fallen.
 */
void MainWindow::displayWinner(int scorePlayerOne,int scorePlayerTwo )
{
    QMessageBox displayWinnerBox;
    QString message = "";
    QString score = "";
    if(scorePlayerOne>scorePlayerTwo){
        score = QString::number(scorePlayerOne);
        message = "le joueur noir a gagner avec : " + score + " point ";
    }else{
        score = QString::number(scorePlayerTwo);
        message =message + "le joueur blanc a gagner avec: " + score + " point ";
    }
    displayWinnerBox.setText(message);
    refreshView();
    displayWinnerBox.exec();
    this->close();
}

/**
 * @brief View::displayScore Display the Score during the game.
 * @param CountBlackBall Counter of all black ball that had fallen.
 * @param CountWhiteBall Counter of all white ball that had fallen.
 */
void MainWindow::displayScore(int scorePlayerOne,int scorePlayerTwo)
{
    QString score = QString::number(scorePlayerOne);
    QString scoreOne = "joueur noir : " + score + "  ";
    QString score2 = QString::number(scorePlayerTwo);
    QString scoreTwo = "joueur blanc : " + score2 + "  ";
    QGraphicsTextItem * textTurnOne = new QGraphicsTextItem();
    QGraphicsTextItem * textTurnTwo = new QGraphicsTextItem();
    QFont  font = QFont();
    font.setPointSize(20);
    textTurnOne->setFont(font);
    textTurnOne->setPlainText(scoreOne);
    textTurnOne->boundingRect();
    textTurnOne->setPos(-10*40, 40*9);
    this->scene->addItem(textTurnOne);
    QFont  font2 = QFont();
    font2.setPointSize(20);
    textTurnTwo->setFont(font2);
    textTurnTwo->setPlainText(scoreTwo);
    textTurnTwo->boundingRect();
    textTurnTwo->setPos(-1*40, 40*9);
    this->scene->addItem(textTurnTwo);
}

/**
 * @brief ask at the user wich move he want to do and do a lecture of it.
 * @return String wich contains the move that the users want to do.
*/
std::string MainWindow::askMove()
{
    this->controller_->move(this->commande_);
    return this->commande_;
}

/**
 * @brief View::displayError display the what of the given exception.
 * @param e exception gived by the controller.
 */
void MainWindow::displayError(const std::exception & except)
{
    QMessageBox displayErrorBox;
    displayErrorBox.setIcon(QMessageBox::Warning);
    displayErrorBox.setText(except.what());
    displayErrorBox.exec();
}

/**
 * @brief MainWindow::~MainWindow Destructor of MainWindow
 */
MainWindow::~MainWindow()
{

}

