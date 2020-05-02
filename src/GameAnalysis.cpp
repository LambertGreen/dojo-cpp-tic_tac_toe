#include "GameAnalysis.h"

#include <cmath>
#include <iomanip>
#include <iostream>

using namespace TicTacToe;
using Player = Game::Player;

namespace {

void SimPlay(Game &game, GameStats &stats) {
  if (game.IsGameOver()) {
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

GameResult SimMaxWinPlay(Game &game, GameStats &stats) {
  if (game.IsGameOver()) {
    if (game.IsDraw()) {
      stats.DrawCount++;
      return GameResult::IsDraw;
    } else if (game.GetWinner() == Player::One) {
      stats.PlayerOneWinCount++;
      return GameResult::PlayerOneWon;
    } else {
      stats.PlayerTwoWinCount++;
      return GameResult::PlayerTwoWon;
    }
  }

  // Set initial value to a loss for the current player
  GameResult result = game.GetCurrentPlayer() == Player::One
                          ? GameResult::PlayerTwoWon
                          : GameResult::PlayerOneWon;
  std::vector<GameStats> p1wins_stats;
  std::vector<GameStats> p2wins_stats;
  std::vector<GameStats> draw_stats;
  // Check if possible plays for a better result
  for (int pos = 1; pos <= 9; pos++) {
    if (game.GetBoard().IsPositionOpen(pos)) {
      auto gameCopy = game;
      gameCopy.PlayTurn(pos);

      GameStats gameStats;
      auto gameResult = SimMaxWinPlay(gameCopy, gameStats);
      switch (gameResult) {
      case GameResult::PlayerOneWon:
        p1wins_stats.push_back(gameStats);
        break;
      case GameResult::PlayerTwoWon:
        p2wins_stats.push_back(gameStats);
        break;
      case GameResult::IsDraw:
        draw_stats.push_back(gameStats);
        break;
      }
    }
  }

  if (game.GetCurrentPlayer() == Player::One) {
    if (p1wins_stats.size() > 0) {
      result = GameResult::PlayerOneWon;
      for (auto gameStats : p1wins_stats) {
        stats.TurnCount += gameStats.TurnCount + 1;
        stats.PlayerOneWinCount += gameStats.PlayerOneWinCount + 1;
      }
    } else if (draw_stats.size() > 0) {
      result = GameResult::IsDraw;
      for (auto gameStats : draw_stats) {
        stats.TurnCount += gameStats.TurnCount + 1;
        stats.DrawCount += gameStats.DrawCount + 1;
      }
    } else if (p2wins_stats.size() > 0) {
      result = GameResult::PlayerTwoWon;
      for (auto gameStats : p2wins_stats) {
        stats.TurnCount += gameStats.TurnCount + 1;
        stats.PlayerTwoWinCount += gameStats.PlayerTwoWinCount + 1;
      }
    }
  } else if (game.GetCurrentPlayer() == Player::Two) {
    if (p2wins_stats.size() > 0) {
      result = GameResult::PlayerTwoWon;
      for (auto gameStats : p2wins_stats) {
        stats.TurnCount += gameStats.TurnCount + 1;
        stats.PlayerTwoWinCount += gameStats.PlayerTwoWinCount + 1;
      }
    } else if (draw_stats.size() > 0) {
      result = GameResult::IsDraw;
      for (auto gameStats : draw_stats) {
        stats.TurnCount += gameStats.TurnCount + 1;
        stats.DrawCount += gameStats.DrawCount + 1;
      }
    } else if (p1wins_stats.size() > 0) {
      result = GameResult::PlayerOneWon;
      for (auto gameStats : p1wins_stats) {
        stats.TurnCount += gameStats.TurnCount + 1;
        stats.PlayerOneWinCount += gameStats.PlayerOneWinCount + 1;
      }
    }
  }

  return result;
}
} // namespace

namespace TicTacToe {

GameStats GetGameStats(Game game, PlayStrategy strategy) {
  GameStats stats;
  switch (strategy) {
  case PlayStrategy::AllPlays:
    SimPlay(game, stats);
    return stats;

  case PlayStrategy::OnlyPerfectPlays:
    GameStats stats;
    SimMaxWinPlay(game, stats);
    return stats;
  }
}

std::vector<PlayStats> GetPlayStatsForOpenPositions(Game game,
                                                    PlayStrategy strategy) {
  std::vector<PlayStats> playStats;
  for (int pos = 1; pos <= 9; pos++) {
    if (game.GetBoard().IsPositionOpen(pos)) {
      Game gameCopy = game;
      gameCopy.PlayTurn(pos);
      auto gameStats = GetGameStats(gameCopy, strategy);
      auto currentPlayer = game.GetCurrentPlayer();
      long totalGamesCount = gameStats.PlayerOneWinCount +
                             gameStats.PlayerTwoWinCount + gameStats.DrawCount;
      PlayStats stats;
      stats.Pos = pos;
      stats.WinProbability =
          currentPlayer == Player::One
              ? static_cast<double>(gameStats.PlayerOneWinCount) /
                    totalGamesCount
              : static_cast<double>(gameStats.PlayerTwoWinCount) /
                    totalGamesCount;
      stats.LossProbability =
          currentPlayer == Player::One
              ? static_cast<double>(gameStats.PlayerTwoWinCount) /
                    totalGamesCount
              : static_cast<double>(gameStats.PlayerOneWinCount) /
                    totalGamesCount;
      stats.DrawProbalitity =
          static_cast<double>(gameStats.DrawCount) / totalGamesCount;
      playStats.push_back(stats);
    }
  }
  return playStats;
}

} // namespace TicTacToe
