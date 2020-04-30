#pragma once

#include "GameBoard.h"

namespace TicTacToe {

class GameEngineCore {
public:
  enum class Player { One, Two };

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

  Player GetCurrentPlayer() const;
  bool IsGameOver() const;
  bool IsDraw() const;
  Player GetWinner() const;
  GameBoard GetBoard() const;

protected:
  enum class State {
    PlayerOnesTurn,
    PlayerTwosTurn,
    PlayerOneWon,
    PlayerTwoWon,
    Draw
  };
  virtual void UpdateState(State newState);

private:
  PlayerToken GetCurrentPlayerToken() const;
  bool IsWinningPlay(PlayerToken token, int pos) const;

  State m_state{};
  GameBoard m_board{};
};
} // namespace TicTacToe
