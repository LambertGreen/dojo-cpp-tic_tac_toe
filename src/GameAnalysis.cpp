#include "GameAnalysis.h"

#include <cmath>
#include <iomanip>
#include <iostream>

using namespace TicTacToe;
using Player = Game::Player;

namespace {

void SimPlay(Game &game, GameStats &stats) {
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

GameStats GetGameStats(Game game) {
  GameStats stats;
  SimPlay(game, stats);
  return stats;
}

std::vector<PlayStats> GetPlayStatsForOpenPositions(Game game) {
  std::vector<PlayStats> playStats;
  for (int pos = 1; pos <= 9; pos++) {
    if (game.GetBoard().IsPositionOpen(pos)) {
      Game gameCopy = game;
      gameCopy.PlayTurn(pos);
      auto gameStats = GetGameStats(gameCopy);
      auto currentPlayer = game.GetCurrentPlayer();
      PlayStats stats;
      stats.Pos = pos;
      stats.WinLossDiff =
          currentPlayer == Player::One
              ? gameStats.PlayerOneWinCount - gameStats.PlayerTwoWinCount
              : gameStats.PlayerTwoWinCount - gameStats.PlayerOneWinCount;
      stats.DrawCount = gameStats.DrawCount;
      playStats.push_back(stats);
    }
  }
  return playStats;
}

} // namespace TicTacToe
