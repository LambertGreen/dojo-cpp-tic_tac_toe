#include "board.h"

#include <array>

namespace TicTacToe {

class Game {
public:
  enum class Player { One, Two };
  void NewGame();
  Player GetCurrentPlayer();
  // Index is a unique number per cell
  // 0 1 2
  // 3 4 5
  // 6 7 8
  //
  void PlayTurn(int index);
  void PlayTurn(int row, int col);
  bool IsGameOver();
  bool IsDraw();
  Player GetWinner();

  void PrintBoard();

private:
  enum class State {
    PlayerOnesTurn,
    PlayerTwosTurn,
    PlayerOneWon,
    PlayerTwoWon,
    Draw
  };

  void ThrowIfGameAlreadyOver();
  PlayerToken GetCurrentPlayerToken();

  State m_state{};
  Board m_board{};
};
} // namespace TicTacToe
