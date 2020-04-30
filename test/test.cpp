#include "../src/GameEngineCore.h"

#include <iostream>
#include <stdexcept>

using namespace TicTacToe;

using Game = GameEngineCore;
using Player = Game::Player;

void ShowGameBoard(const Game &game) {
  std::cout << "Board:" << std::endl
            << game.GetBoard().ToString() << std::flush;
}

void TestNewGame() {
  Game game;
  ShowGameBoard(game);
}

void TestPlayOneFirstPlay() {
  Game game;

  // Board:
  // @ 2 3
  // 4 5 6
  // 7 8 9
  game.PlayTurn(1);

  ShowGameBoard(game);
}

void TestPlayTwoFirstPlay() {
  Game game;

  // Board:
  // @ # 3
  // 4 5 6
  // 7 8 9
  game.PlayTurn(1);
  game.PlayTurn(2);

  ShowGameBoard(game);
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

  ShowGameBoard(game);

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

  ShowGameBoard(game);

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

  ShowGameBoard(game);

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
