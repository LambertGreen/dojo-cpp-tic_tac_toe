#include "GameBoard.h"

#include <exception>
#include <sstream>

using namespace TicTacToe;

namespace {

char ToChar(GameBoard::Cell c) {
  switch (c) {
  case GameBoard::Cell::Empty:
    return '_';

  case GameBoard::Cell::PlayerOneToken:
    return '@';

  case GameBoard::Cell::PlayTwoToken:
    return '#';
  }
}

int RowColToPosition(int row, int col) { return row * 3 + col + 1; }
} // namespace

namespace TicTacToe {

void GameBoard::PlaceToken(PlayerToken p, int row, int col) {
  if (m_board[row][col] != Cell::Empty) {
    throw std::runtime_error("Position is not empty");
  }

  m_board[row][col] =
      p == PlayerToken::One ? Cell::PlayerOneToken : Cell::PlayTwoToken;
  m_playCount++;
}

bool GameBoard::IsPositionOpen(int row, int col) {
  return m_board[row][col] == Cell::Empty;
}

bool GameBoard::IsBoardFull() { return m_playCount == 9; }

int GameBoard::GetTokenCountInRow(PlayerToken p, int row) {
  auto cell = p == PlayerToken::One ? Cell::PlayerOneToken : Cell::PlayTwoToken;
  int count = 0;
  if (cell == m_board[row][0])
    count++;
  if (cell == m_board[row][1])
    count++;
  if (cell == m_board[row][2])
    count++;
  return count;
}

int GameBoard::GetTokenCountInCol(PlayerToken p, int col) {
  auto cell = p == PlayerToken::One ? Cell::PlayerOneToken : Cell::PlayTwoToken;
  int count = 0;
  if (cell == m_board[0][col])
    count++;
  if (cell == m_board[1][col])
    count++;
  if (cell == m_board[2][col])
    count++;
  return count;
}

int GameBoard::GetTokenCountInDiag(PlayerToken p, bool topLeftBottomRightDiag) {
  auto cell = p == PlayerToken::One ? Cell::PlayerOneToken : Cell::PlayTwoToken;
  int count = 0;
  if (topLeftBottomRightDiag) {

    if (cell == m_board[0][0])
      count++;
    if (cell == m_board[1][1])
      count++;
    if (cell == m_board[2][2])
      count++;
  } else {
    if (cell == m_board[0][2])
      count++;
    if (cell == m_board[1][1])
      count++;
    if (cell == m_board[2][0])
      count++;
  }
  return count;
}

std::string GameBoard::CellToString(int row, int col) {
  auto cell = m_board[row][col];
  auto cellStr = cell == Cell::Empty
                     ? std::to_string(RowColToPosition(row, col))
                     : std::string(1, ToChar(cell));
  return "[" + cellStr + "]";
}

std::string GameBoard::ToString() {
  std::stringstream ss;
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      ss << CellToString(row, col);
    }
    ss << std::endl;
  }
  return ss.str();
}

} // namespace TicTacToe
