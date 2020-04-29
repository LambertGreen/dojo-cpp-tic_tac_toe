#include "../src/game.h"

#include <iostream>
#include <stdexcept>

using namespace TicTacToe;
using Player = Game::Player;

void TestNewGame() {
  Game game;
  game.PrintBoard();
}

void TestPlayOneFirstPlay() {
  Game game;
  game.PlayTurn(0, 0);
  game.PrintBoard();
}

void TestPlayTwoFirstPlay() {
  Game game;
  game.PlayTurn(0, 0);
  game.PlayTurn(0, 1);
  game.PrintBoard();
}

void TestPlayerOneWinsInRow() {
  Game game;
  game.PlayTurn(0, 0);
  game.PlayTurn(1, 0);
  game.PlayTurn(0, 1);
  game.PlayTurn(1, 1);
  game.PlayTurn(0, 2);
  game.PrintBoard();

  if (game.GetWinner() != Player::One) {
    throw std::runtime_error("PlayerOne is expected to have won!");
  }
}

void TestPlayerOneWinsInCol() {
  Game game;
  game.PlayTurn(0, 0);
  game.PlayTurn(0, 1);
  game.PlayTurn(1, 0);
  game.PlayTurn(1, 1);
  game.PlayTurn(2, 0);
  game.PrintBoard();

  if (game.GetWinner() != Player::One) {
    throw std::runtime_error("PlayerOne is expected to have won!");
  }
}

int main() {
  TestNewGame();
  TestPlayOneFirstPlay();
  TestPlayTwoFirstPlay();
  TestPlayerOneWinsInRow();
  TestPlayerOneWinsInCol();

  return 0;
}
