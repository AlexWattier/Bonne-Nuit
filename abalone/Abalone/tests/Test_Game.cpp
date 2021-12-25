#include <catch2/catch.hpp>
#include "Game.h"

using namespace abalone::Model;

TEST_CASE("Game", "[Game][moveChooser]")
{

    SECTION("Constructor Game."){
        Game game = Game();
        REQUIRE(game.getCountBlackBall_()==0);
        REQUIRE(game.getcountWhiteBall_()==0);
        REQUIRE(game.isBlackTurn()==true);
    }

    SECTION("Move with or without Aba-pro")
    {
        SECTION("Non Aba-pro"){
            Game game = Game();
            std::string input_NonAbaPro= "C8C7";
            REQUIRE(true == game.moveChooser(input_NonAbaPro));
        }
        SECTION("Aba-pro"){
            Game game = Game();
            std::string input_AbaPro= "8C7C";
            REQUIRE(true == game.moveChooser(input_AbaPro));
        }
    }

    SECTION("moveChooser")
    {
        SECTION("moveChooser Linear")
        {
            Game game = Game();
            std::string input = "C7C6";
            bool moved = game.moveChooser(input);
            abalone::Model::Position::Position initial = abalone::Model::Position::Position(6,abalone::Model::Position::C);
            abalone::Model::Position::Position newPos = abalone::Model::Position::Position(5,abalone::Model::Position::C);
            REQUIRE(moved==true);
            REQUIRE(game.getBoardRules().getBoard().getCase(initial).getState()==abalone::Model::Board::EMPTY);
            REQUIRE(game.getBoardRules().getBoard().getCase(newPos).getState()==abalone::Model::Board::BLACK);
        }

        SECTION("moveChooser Diagonal")
        {
            Game game = Game();
            std::string input = "C7E7C6";
            bool moved = game.moveChooser(input);
            REQUIRE(moved==true);
            abalone::Model::Position::Position initial = abalone::Model::Position::Position(6,abalone::Model::Position::C);
            abalone::Model::Position::Position newPos = abalone::Model::Position::Position(5,abalone::Model::Position::C);
            REQUIRE(game.getBoardRules().getBoard().getCase(initial).getState()==abalone::Model::Board::EMPTY);
            REQUIRE(game.getBoardRules().getBoard().getCase(newPos).getState()==abalone::Model::Board::BLACK);
            initial = abalone::Model::Position::Position(6,abalone::Model::Position::D);
            newPos = abalone::Model::Position::Position(5,abalone::Model::Position::D);
            REQUIRE(game.getBoardRules().getBoard().getCase(initial).getState()==abalone::Model::Board::EMPTY);
            REQUIRE(game.getBoardRules().getBoard().getCase(newPos).getState()==abalone::Model::Board::BLACK);
            initial = abalone::Model::Position::Position(6,abalone::Model::Position::E);
            newPos = abalone::Model::Position::Position(5,abalone::Model::Position::E);
            REQUIRE(game.getBoardRules().getBoard().getCase(initial).getState()==abalone::Model::Board::EMPTY);
            REQUIRE(game.getBoardRules().getBoard().getCase(newPos).getState()==abalone::Model::Board::BLACK);
        }
    }

}

TEST_CASE("BoardRules", "[BoardRules][move]"){
    SECTION("Error Move"){
        SECTION("Initial Position not in Board."){
            abalone::Model::BoardRules::BoardRules boardR = abalone::Model::BoardRules::BoardRules();
            abalone::Model::Position::Position initialPosition = abalone::Model::Position::Position(0,abalone::Model::Position::A);
            abalone::Model::Position::Position newPosition = abalone::Model::Position::Position();
            REQUIRE_THROWS_MATCHES(boardR.move(initialPosition,newPosition,true),
                                   std::invalid_argument,
                                   Catch::Message("Incorrect value of initial position : Position not on the Board"));
        }

        SECTION("Not Your Ball"){
            abalone::Model::BoardRules::BoardRules boardR = abalone::Model::BoardRules::BoardRules();
            abalone::Model::Position::Position initialPosition = abalone::Model::Position::Position(9,abalone::Model::Position::C);
            abalone::Model::Position::Position newPosition = abalone::Model::Position::Position();
            REQUIRE_THROWS_MATCHES(boardR.move(initialPosition,newPosition,true),
                                   std::invalid_argument,
                                   Catch::Message("Incorrect value of initial position : Not your ball."));
        }

        SECTION("New Position not in Board"){
            abalone::Model::BoardRules::BoardRules boardR = abalone::Model::BoardRules::BoardRules();
            abalone::Model::Position::Position initialPosition = abalone::Model::Position::Position(6,abalone::Model::Position::C);
            abalone::Model::Position::Position newPosition = abalone::Model::Position::Position(0,abalone::Model::Position::A);
            REQUIRE_THROWS_MATCHES(boardR.move(initialPosition,newPosition,true),
                                   std::invalid_argument,
                                   Catch::Message("Incorrect value of the new position : Position not on the Board"));
        }

        SECTION("Not a Move"){
            abalone::Model::BoardRules::BoardRules boardR = abalone::Model::BoardRules::BoardRules();
            abalone::Model::Position::Position initialPosition = abalone::Model::Position::Position(6,abalone::Model::Position::C);
            abalone::Model::Position::Position newPosition = abalone::Model::Position::Position(4,abalone::Model::Position::C);
            REQUIRE_THROWS_MATCHES(boardR.move(initialPosition,newPosition,true),
                                   std::invalid_argument,
                                   Catch::Message("Move Refused : Unknown Move"));
        }
        SECTION("Can't Push : To much own Balls"){
            abalone::Model::BoardRules::BoardRules boardR = abalone::Model::BoardRules::BoardRules();
            abalone::Model::Position::Position initialPosition = abalone::Model::Position::Position(1,abalone::Model::Position::D);
            abalone::Model::Position::Position newPosition = abalone::Model::Position::Position(1,abalone::Model::Position::E);
            REQUIRE_THROWS_AS(boardR.move(initialPosition,newPosition,true),
                                   std::invalid_argument);
        }
    }
}

TEST_CASE("Board", "[Board][move]"){
    SECTION("Move"){
        SECTION("Lineare Move"){
            SECTION("Correct Move"){
                abalone::Model::Board::Board board = abalone::Model::Board::Board();
                abalone::Model::Position::Position initialPosition = abalone::Model::Position::Position(2,abalone::Model::Position::E);
                abalone::Model::Position::Position newPosition = abalone::Model::Position::Position(3,abalone::Model::Position::E);
                board.move(initialPosition,newPosition,nullptr);
                REQUIRE(board.getCase(initialPosition).getState()==abalone::Model::Board::EMPTY);
                REQUIRE(board.getCase(newPosition).getState()==abalone::Model::Board::WHITE);
            }

            SECTION("Pushing"){
                SECTION("Pushing and Falling ball"){
                    abalone::Model::Board::Board board = abalone::Model::Board::Board();
                    abalone::Model::Position::Position initialPosition = abalone::Model::Position::Position(0,abalone::Model::Position::G);
                    abalone::Model::Position::Position newPosition = abalone::Model::Position::Position(0,abalone::Model::Position::F);
                    int pmove [] = {0,-1};
                    abalone::Model::Board::StateCase fallen = board.move(initialPosition,newPosition,pmove);
                    REQUIRE(fallen==abalone::Model::Board::WHITE);
                }

                SECTION("Pushing without falling"){
                    abalone::Model::Board::Board board = abalone::Model::Board::Board();
                    abalone::Model::Position::Position initialPosition = abalone::Model::Position::Position(0,abalone::Model::Position::E);
                    abalone::Model::Position::Position newPosition = abalone::Model::Position::Position(1,abalone::Model::Position::E);
                    int pmove [] = {1,0};
                    REQUIRE(board.move(initialPosition,newPosition,pmove)==abalone::Model::Board::EMPTY);
                    REQUIRE(board.getCase(initialPosition).getState()==abalone::Model::Board::EMPTY);
                    REQUIRE(board.getCase(newPosition).getState()==abalone::Model::Board::WHITE);
                    abalone::Model::Position::Position p = abalone::Model::Position::Position(newPosition,pmove);
                    REQUIRE(board.getCase(p).getState()==abalone::Model::Board::WHITE);
                    p = abalone::Model::Position::Position(p,pmove);
                    REQUIRE(board.getCase(p).getState()==abalone::Model::Board::WHITE);
                }
            }
        }

        SECTION("Diagonals Move"){
            SECTION("3 balls"){
                abalone::Model::Board::Board board = abalone::Model::Board::Board();
                abalone::Model::Position::Position tab [] = {abalone::Model::Position::Position(2,abalone::Model::Position::E),
                                                             abalone::Model::Position::Position(2,abalone::Model::Position::F),
                                                             abalone::Model::Position::Position(2,abalone::Model::Position::G)};
                int pmove [] = {1,0};
                board.move(tab,3,pmove);

                REQUIRE(board.getCase(tab[0]).getState()==abalone::Model::Board::EMPTY);
                REQUIRE(board.getCase(tab[1]).getState()==abalone::Model::Board::EMPTY);
                REQUIRE(board.getCase(tab[2]).getState()==abalone::Model::Board::EMPTY);

                abalone::Model::Position::Position p = abalone::Model::Position::Position(tab[0],pmove);
                REQUIRE(board.getCase(p).getState()==abalone::Model::Board::WHITE);

                p = abalone::Model::Position::Position(tab[1],pmove);
                REQUIRE(board.getCase(p).getState()==abalone::Model::Board::WHITE);

                p = abalone::Model::Position::Position(tab[2],pmove);
                REQUIRE(board.getCase(p).getState()==abalone::Model::Board::WHITE);
            }

            SECTION("2 balls"){
                abalone::Model::Board::Board board = abalone::Model::Board::Board();
                abalone::Model::Position::Position tab [] = {abalone::Model::Position::Position(2,abalone::Model::Position::E),
                                                             abalone::Model::Position::Position(2,abalone::Model::Position::F)};
                int pmove [] = {1,0};
                board.move(tab,2,pmove);

                REQUIRE(board.getCase(tab[0]).getState()==abalone::Model::Board::EMPTY);
                REQUIRE(board.getCase(tab[1]).getState()==abalone::Model::Board::EMPTY);

                abalone::Model::Position::Position p = abalone::Model::Position::Position(2,abalone::Model::Position::G);
                REQUIRE(board.getCase(p).getState()==abalone::Model::Board::WHITE);

                p = abalone::Model::Position::Position(tab[0],pmove);
                REQUIRE(board.getCase(p).getState()==abalone::Model::Board::WHITE);

                p = abalone::Model::Position::Position(tab[1],pmove);
                REQUIRE(board.getCase(p).getState()==abalone::Model::Board::WHITE);

                p = abalone::Model::Position::Position(3,abalone::Model::Position::G);
                REQUIRE(board.getCase(p).getState()==abalone::Model::Board::EMPTY);
            }
        }



    }
}

