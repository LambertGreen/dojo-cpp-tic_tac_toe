#include "GameEngineCore.h"

namespace TicTacToe {

using Game = GameEngineCore;
struct PlayStats {
  long TurnCount{};
  long GameCount{};
  long PlayerOneWinCount{};
  long PlayerTwoWinCount{};
  long DrawCount{};
};
using PlayStatsByPosition = std::array<std::unique_ptr<PlayStats>, 9>;

PlayStats GetPlayStats(Game game);
void PrintPlayStats(const PlayStats &stats);

} // namespace TicTacToe
