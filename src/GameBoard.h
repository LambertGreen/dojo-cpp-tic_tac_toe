#pragma once

#include <array>
#include <string>

namespace TicTacToe {

enum class PlayerToken { One, Two };

class GameBoard {
public:
  enum class Cell { Empty, PlayerOneToken, PlayTwoToken };

  // The position values for each cell are numbered from 1 to 9
  // starting with 1 in the top-left, incrementing by 1 going from
  // left to right.
  //
  // Position numbers:
  //   1 2 3
  //   4 5 6
  //   7 8 9
  //
  void PlaceToken(PlayerToken token, int pos);
  bool IsPositionOpen(int pos) const;
  bool IsBoardFull() const;

  int GetTokenCountInRow(PlayerToken token, int pos) const;
  int GetTokenCountInCol(PlayerToken token, int pos) const;
  int GetTokenCountInDiag(PlayerToken token, bool topLeftBottomRightDiag) const;
  std::string ToString() const;

private:
  std::string CellToString(int row, int col) const;

  std::array<std::array<Cell, 3>, 3> m_board{};
  int m_playCount{};
};

} // namespace TicTacToe
