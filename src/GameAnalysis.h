#pragma once

#include "GameEngineCore.h"

#include <vector>

namespace TicTacToe {

using Game = GameEngineCore;
using Player = Game::Player;

struct GameStats {
  long TurnCount{};
  long PlayerOneWinCount{};
  long PlayerTwoWinCount{};
  long DrawCount{};
};

struct PlayStats {
  int Pos{};
  double WinProbability;
  double LossProbability;
  double DrawProbalitity;
};

enum class PlayStrategy {
  AllPlays,
  OnlyPerfectPlays,
};

enum class GameResult { IsDraw, PlayerOneWon, PlayerTwoWon };

GameStats GetGameStats(Game game, PlayStrategy playStrategy);
std::vector<PlayStats> GetPlayStatsForOpenPositions(Game game,
                                                    PlayStrategy playStrategy);
} // namespace TicTacToe
