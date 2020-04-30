#include "GameBoard.h"

#include <exception>
#include <sstream>

using namespace TicTacToe;

namespace {

char CellToChar(GameBoard::Cell c) {
  switch (c) {
  case GameBoard::Cell::Empty:
    return '_';

  case GameBoard::Cell::PlayerOneToken:
    return '@';

  case GameBoard::Cell::PlayTwoToken:
    return '#';
  }
}

int PosToRow(int pos) { return (pos - 1) / 3; }

int PosToCol(int pos) { return (pos - 1) % 3; }

int RowColToPos(int row, int col) { return row * 3 + col + 1; }

} // namespace

namespace TicTacToe {

void GameBoard::PlaceToken(PlayerToken token, int pos) {
  auto row = PosToRow(pos);
  auto col = PosToCol(pos);

  if (m_board[row][col] != Cell::Empty) {
    throw std::runtime_error("Position is not empty");
  }

  m_board[row][col] =
      token == PlayerToken::One ? Cell::PlayerOneToken : Cell::PlayTwoToken;
  m_playCount++;
}

bool GameBoard::IsPositionOpen(int pos) const {
  auto row = PosToRow(pos);
  auto col = PosToCol(pos);
  return m_board[row][col] == Cell::Empty;
}

bool GameBoard::IsBoardFull() const { return m_playCount == 9; }

int GameBoard::GetTokenCountInRow(PlayerToken token, int pos) const {
  auto row = PosToRow(pos);
  auto cell =
      token == PlayerToken::One ? Cell::PlayerOneToken : Cell::PlayTwoToken;
  int count = 0;
  if (cell == m_board[row][0])
    count++;
  if (cell == m_board[row][1])
    count++;
  if (cell == m_board[row][2])
    count++;
  return count;
}

int GameBoard::GetTokenCountInCol(PlayerToken token, int pos) const {
  auto col = PosToCol(pos);
  auto cell =
      token == PlayerToken::One ? Cell::PlayerOneToken : Cell::PlayTwoToken;
  int count = 0;
  if (cell == m_board[0][col])
    count++;
  if (cell == m_board[1][col])
    count++;
  if (cell == m_board[2][col])
    count++;
  return count;
}

int GameBoard::GetTokenCountInDiag(PlayerToken token,
                                   bool topLeftBottomRightDiag) const {
  auto cell =
      token == PlayerToken::One ? Cell::PlayerOneToken : Cell::PlayTwoToken;
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

std::string GameBoard::CellToString(int row, int col) const {
  auto cell = m_board[row][col];
  auto cellStr = cell == Cell::Empty ? std::to_string(RowColToPos(row, col))
                                     : std::string(1, CellToChar(cell));
  return "[" + cellStr + "]";
}

std::string GameBoard::ToString() const {
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
