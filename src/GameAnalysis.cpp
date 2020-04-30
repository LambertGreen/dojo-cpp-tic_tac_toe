#include "GameAnalysis.h"

#include <iomanip>
#include <iostream>

using namespace TicTacToe;
using Player = Game::Player;

namespace {

void SimPlay(Game &game, PlayStats &stats) {
  if (game.IsGameOver()) {
    stats.GameCount++;
    if (game.IsDraw()) {
      stats.DrawCount++;
    } else if (game.GetWinner() == Player::One) {
      stats.PlayerOneWinCount++;
    } else {
      stats.PlayerTwoWinCount++;
    }
    return;
  }

  for (int pos = 1; pos <= 9; pos++) {
    if (game.GetBoard().IsPositionOpen(pos)) {
      auto gameCopy = game;
      gameCopy.PlayTurn(pos);
      stats.TurnCount++;

      SimPlay(gameCopy, stats);
    }
  }
}

} // namespace

namespace TicTacToe {

PlayStats GetPlayStats(Game game) {
  PlayStats stats;
  SimPlay(game, stats);
  return stats;
}

void PrintPlayStats(const PlayStats &stats) {
  auto totalGames = stats.GameCount;
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
  std::cout << "Games Stats: { "
            << "TotalGames: " << totalGames
            << ", PlayerOneWins: " << stats.PlayerOneWinCount << "("
            << std::fixed << percentPlayerOneWins << "%)"
            << ", PlayerTwoWins: " << stats.PlayerTwoWinCount << "("
            << std::fixed << percentPlayerTwoWins << "%)"
            << ", Draws: " << stats.DrawCount << "(" << std::fixed
            << percentDraws << "%)"
            << ", Turns: " << stats.TurnCount << " }" << std::endl;
}

} // namespace TicTacToe
