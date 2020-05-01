#pragma once

#include "GameEngineCore.h"

#include <vector>

namespace TicTacToe {

using Game = GameEngineCore;
using Player = Game::Player;

struct GameStats {
  long TurnCount{};
  long GameCount{};
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

GameStats GetGameStats(Game game);
std::vector<PlayStats> GetPlayStatsForOpenPositions(Game game);
} // namespace TicTacToe
