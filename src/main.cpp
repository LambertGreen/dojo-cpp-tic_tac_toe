#include "game.h"

#include <exception>
#include <iostream>

using namespace TicTacToe;

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
  std::cout << " [x] - Exit" << std::endl;
}

enum class Option {
  NewGame,
  Exit,
};

Option GetMainMenuOption() {
  while (true) {
    char input;
    std::cin >> input;
    if (input == 'x')
      return Option::Exit;
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
  std::cout << "Game over: It's draw!" << std::endl;
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

int main(int argc, char *argv[]) {

  ShowAppHeader();

  while (true) {

    ShowMainMenu();
    Option option = GetMainMenuOption();
    if (option == Option::Exit)
      break;

    try {
      Game game;

      while (!game.IsGameOver()) {
        game.PrintBoard();
        game.PlayTurn(
            GetPlayerInputForTurn(GetPlayerName(game.GetCurrentPlayer())));
      }
      if (game.IsDraw()) {
        ShowDraw();
      } else {
        ShowPlayerVictory(GetPlayerName(game.GetWinner()));
      }
    } catch (std::exception &ex) {
      ShowException(ex);
    }
  }
  ShowExit();

  return 0;
}
