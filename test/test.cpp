#include "../src/game.h"

#include <iostream>
#include <stdexcept>

using namespace TicTacToe;
using Player = Game::Player;

void TestNewGame() {
  Game game;
  game.PrintBoard();
  game.PrintStats();
}

void TestPlayOneFirstPlay() {
  Game game;

  // Board:
  // @ 2 3
  // 4 5 6
  // 7 8 9
  game.PlayTurn(1);

  game.PrintBoard();
  game.PrintStats();
}

void TestPlayTwoFirstPlay() {
  Game game;

  // Board:
  // @ # 3
  // 4 5 6
  // 7 8 9
  game.PlayTurn(1);
  game.PlayTurn(2);

  game.PrintBoard();
  game.PrintStats();
}

void TestPlayerOneWinsInRow() {
  Game game;

  // Board:
  // @ 2 3
  // # 5 6
  // 7 8 9
  game.PlayTurn(1);
  game.PlayTurn(4);

  // Board:
  // @ @ 3
  // # # 6
  // 7 8 9
  game.PlayTurn(2);
  game.PlayTurn(5);

  // Board:
  // @ @ @
  // # # 6
  // 7 8 9
  game.PlayTurn(3);

  game.PrintBoard();
  game.PrintStats();

  if (game.GetWinner() != Player::One) {
    throw std::runtime_error("PlayerOne is expected to have won!");
  }
}

void TestPlayerTwoWinsInCol() {
  Game game;

  // Board:
  // @ 2 #
  // 4 5 6
  // 7 8 9
  game.PlayTurn(1);
  game.PlayTurn(3);

  // Board:
  // @ @ #
  // 4 5 #
  // 7 8 9
  game.PlayTurn(2);
  game.PlayTurn(6);

  // Board:
  // @ @ #
  // @ 5 #
  // 7 8 #
  game.PlayTurn(4);
  game.PlayTurn(9);

  game.PrintBoard();
  game.PrintStats();

  if (game.GetWinner() != Player::Two) {
    throw std::runtime_error("PlayerTwo is expected to have won!");
  }
}

void TestDraw() {
  Game game;

  // Board:
  // @ 2 #
  // 4 5 6
  // 7 8 9
  game.PlayTurn(1);
  game.PlayTurn(3);

  // Board:
  // @ 2 #
  // # 5 @
  // 7 8 9
  game.PlayTurn(6);
  game.PlayTurn(4);

  // Board:
  // @ 2 #
  // # 5 @
  // 7 @ #
  game.PlayTurn(8);
  game.PlayTurn(9);

  // Board:
  // @ @ #
  // # # @
  // 7 @ #
  game.PlayTurn(2);
  game.PlayTurn(5);

  // Board:
  // @ @ #
  // # # @
  // @ @ #
  game.PlayTurn(7);

  game.PrintBoard();
  game.PrintStats();

  if (!game.IsDraw()) {
    throw std::runtime_error("Expected a draw!");
  }
}

int main() {
  TestNewGame();
  TestPlayOneFirstPlay();
  TestPlayTwoFirstPlay();
  TestPlayerOneWinsInRow();
  TestPlayerTwoWinsInCol();
  TestDraw();

  return 0;
}
