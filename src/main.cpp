#include "GameAnalysis.h"
#include "GameEngineCore.h"

#include <exception>
#include <iostream>

using namespace TicTacToe;

using Game = GameEngineCore;

enum class Option {
  NewGame,
  RunSimToGetGameStats,
  Exit,
};

namespace {
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
  std::cout << std::endl;
  std::cout << "Enter menu option: ";
}

Option GetMainMenuOption() {
  while (true) {
    char input;
    std::cin >> input;
    if (input == 'x')
      return Option::Exit;
    if (input == 'r')
      return Option::RunSimToGetGameStats;
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

void ShowBoard(const Game &game) {
  std::cout << "Board:" << std::endl
            << game.GetBoard().ToString() << std::flush;
}

void ShowEndGame(Game &game) {
  ShowBoard(game);
  if (game.IsDraw()) {
    ShowDraw();
  } else {
    ShowPlayerVictory(GetPlayerName(game.GetWinner()));
  }
}

std::string PlayStrategyToString(PlayStrategy strategy) {
  switch (strategy) {
  case PlayStrategy::AllPlays:
    return "All Plays";
  case PlayStrategy::OnlyPerfectPlays:
    return "Max Win Plays";
  }
}

void ShowGameStats(const GameStats &stats, PlayStrategy strategy) {
  auto totalGames =
      stats.PlayerOneWinCount + stats.PlayerTwoWinCount + stats.DrawCount;
  auto percentPlayerOneWins =
      totalGames > 0
          ? 100 * static_cast<double>(stats.PlayerOneWinCount) / totalGames
          : 0;
  auto percentPlayerTwoWins =
      totalGames > 0
          ? 100 * static_cast<double>(stats.PlayerTwoWinCount) / totalGames
          : 0;
  auto percentDraws =
      totalGames > 0 ? 100 * static_cast<double>(stats.DrawCount) / totalGames
                     : 0;

  std::cout.precision(2);
  std::cout << "Games Stats (" << PlayStrategyToString(strategy) << "): { "
            << "TotalGames: " << totalGames
            << ", PlayerOneWins: " << stats.PlayerOneWinCount << "("
            << std::fixed << percentPlayerOneWins << "%)"
            << ", PlayerTwoWins: " << stats.PlayerTwoWinCount << "("
            << std::fixed << percentPlayerTwoWins << "%)"
            << ", Draws: " << stats.DrawCount << "(" << std::fixed
            << percentDraws << "%)"
            << ", Turns: " << stats.TurnCount << " }" << std::endl;
}

void ShowPlayStats(Game game, PlayStrategy strategy) {
  auto playStats = GetPlayStatsForOpenPositions(game, strategy);
  std::cout << "Play stats for current player ("
            << PlayStrategyToString(strategy) << "): " << std::endl;
  std::cout.precision(2);
  for (auto &stats : playStats) {
    std::cout << "\tPos(" << stats.Pos << "): "
              << "Win = " << std::fixed << 100 * stats.WinProbability << "%, "
              << "Loss = " << std::fixed << 100 * stats.LossProbability << "%, "
              << "Draw = " << std::fixed << 100 * stats.DrawProbalitity << "%"
              << std::endl;
  }
  std::cout << std::endl;
}

void RunSimToGetGameStats() {
  Game game;
  ShowGameStats(GetGameStats(game, PlayStrategy::AllPlays),
                PlayStrategy::AllPlays);
  ShowGameStats(GetGameStats(game, PlayStrategy::OnlyPerfectPlays),
                PlayStrategy::OnlyPerfectPlays);
}

void PlayTwoPlayerGame() {
  try {
    Game game;

    while (!game.IsGameOver()) {
      ShowBoard(game);
      ShowPlayStats(game, PlayStrategy::OnlyPerfectPlays);
      ShowPlayStats(game, PlayStrategy::AllPlays);
      game.PlayTurn(
          GetPlayerInputForTurn(GetPlayerName(game.GetCurrentPlayer())));
    }

    ShowEndGame(game);

  } catch (std::exception &ex) {
    ShowException(ex);
  }
}

} // namespace

int main() {

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

    case Option::RunSimToGetGameStats:
      RunSimToGetGameStats();
      break;
    }
  }
  ShowExit();

  return 0;
}
