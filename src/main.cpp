#include "GameEngineCore.h"

#include <exception>
#include <iostream>

using namespace TicTacToe;

using Game = GameEngineCore;

void ShowAppHeader() {
  std::cout << "--------------------------------" << std::endl;
  std::cout << "Welcome to the Tic-tac-toe game!" << std::endl;
  std::cout << "--------------------------------" << std::endl;
}

void ShowMainMenu() {
  std::cout << std::endl;
  std::cout << "-------" << std::endl;
  std::cout << " Menu  " << std::endl;
  std::cout << "-------" << std::endl;
  std::cout << " [n] - New Game" << std::endl;
  std::cout << " [r] - Run simulations" << std::endl;
  std::cout << " [x] - Exit" << std::endl;
}

enum class Option {
  NewGame,
  RunSimulation,
  Exit,
};

Option GetMainMenuOption() {
  while (true) {
    char input;
    std::cin >> input;
    if (input == 'x')
      return Option::Exit;
    if (input == 'r')
      return Option::RunSimulation;
    if (input == 'n')
      return Option::NewGame;
    std::cout << "Not a valid option!" << std::endl;
  }
}

std::string GetPlayerName(Game::Player p) {
  switch (p) {
  case Game::Player::One:
    return "Player one";
  case Game::Player::Two:
    return "Player two";
  };
}

int GetPlayerInputForTurn(std::string playerName) {
  std::cout << playerName << " play your turn: ";
  int index;
  std::cin >> index;
  return index;
}

void ShowPlayerVictory(std::string playerName) {
  std::cout << std::endl;
  std::cout << "---------------------------------------------------"
            << std::endl;
  std::cout << "Game over: " << playerName << " has won!!!" << std::endl;
  std::cout << "---------------------------------------------------"
            << std::endl;
}

void ShowDraw() {
  std::cout << std::endl;
  std::cout << "---------------------------------------------------"
            << std::endl;
  std::cout << "Game over: It's a draw!" << std::endl;
  std::cout << "---------------------------------------------------"
            << std::endl;
}

void ShowExit() {
  std::cout << std::endl;
  std::cout << "Goodbye!" << std::endl;
  std::cout << std::endl;
}

void ShowException(const std::exception &ex) {
  std::cout << "Exception occurred: " << ex.what();
}

void ShowEndGame(Game &game) {
  game.PrintBoard();
  if (game.IsDraw()) {
    ShowDraw();
  } else {
    ShowPlayerVictory(GetPlayerName(game.GetWinner()));
  }
  game.PrintStats();
}

void PlayTwoPlayerGame() {
  try {
    Game game;

    while (!game.IsGameOver()) {
      game.PrintBoard();
      game.PlayTurn(
          GetPlayerInputForTurn(GetPlayerName(game.GetCurrentPlayer())));
    }

    ShowEndGame(game);

  } catch (std::exception &ex) {
    ShowException(ex);
  }
}

void SimPlay(Game game, bool showOutput) {
  if (game.IsGameOver()) {
    if (showOutput) {
      ShowEndGame(game);
    }
    return;
  }

  for (int pos = 1; pos <= 9; pos++) {
    if (game.IsPositionOpen(pos)) {
      auto gameCopy = game;
      gameCopy.PlayTurn(pos);
      SimPlay(gameCopy, showOutput);
    }
  }
}

void RunSimulation() {
  Game game;
  bool showOutput = false;
  SimPlay(game, showOutput);
  game.PrintStats();
}

int main(int argc, char *argv[]) {

  ShowAppHeader();

  bool exit = false;
  while (!exit) {

    ShowMainMenu();
    switch (GetMainMenuOption()) {
    case Option::Exit:
      exit = true;
      break;

    case Option::NewGame:
      PlayTwoPlayerGame();
      break;

    case Option::RunSimulation:
      RunSimulation();
      break;
    }
  }
  ShowExit();

  return 0;
}
