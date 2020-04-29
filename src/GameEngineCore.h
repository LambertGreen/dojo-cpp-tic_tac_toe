#include "GameBoard.h"

#include <array>

namespace TicTacToe {

class GameEngineCore {
public:
  enum class Player { One, Two };

  void NewGame();
  Player GetCurrentPlayer();
  // The position values for each cell are numbered from 1 to 9
  // starting with 1 in the top-left, incrementing by 1 going from
  // left to right.
  //
  // Position numbers:
  //   1 2 3
  //   4 5 6
  //   7 8 9
  //
  void PlayTurn(int position);
  bool IsPositionOpen(int position);
  bool IsGameOver();
  bool IsDraw();
  Player GetWinner();

  void PrintBoard();

  struct PlayStats {
    long PlayerOneWinCount;
    long PlayerTwoWinCount;
    long DrawCount;
    long TurnCount;
  };
  static PlayStats GetStats();
  static void ClearStats();
  static void PrintStats();

private:
  enum class State {
    PlayerOnesTurn,
    PlayerTwosTurn,
    PlayerOneWon,
    PlayerTwoWon,
    Draw
  };

  PlayerToken GetCurrentPlayerToken();
  void PlayTurn(int row, int col);
  bool IsWinningPlay(PlayerToken token, int row, int col);

  State m_state{};
  GameBoard m_board{};

  static PlayStats s_stats;
};
} // namespace TicTacToe
