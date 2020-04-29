#include "GameEngineCore.h"

#include <exception>
#include <iomanip>
#include <iostream>

using namespace TicTacToe;

namespace {
int PositionToRow(int pos) { return (pos - 1) / 3; }

int PositionToCol(int pos) { return (pos - 1) % 3; }
} // namespace

namespace TicTacToe {

GameEngineCore::Player GameEngineCore::GetCurrentPlayer() {
  switch (m_state) {
  case State::PlayerOnesTurn:
    return Player::One;

  case State::PlayerTwosTurn:
    return Player::Two;

  default:
    throw std::runtime_error("Game is over!");
  }
}

void GameEngineCore::PlayTurn(int position) {
  PlayTurn(PositionToRow(position), PositionToCol(position));
}

void GameEngineCore::PlayTurn(int row, int col) {
  // Throw if game is over
  switch (m_state) {
  case State::Draw:
  case State::PlayerOneWon:
  case State::PlayerTwoWon:
    throw std::runtime_error("Game is already over");
  default:
    break;
  }

  // Place player token on board
  auto playerToken = GetCurrentPlayerToken();
  m_board.PlaceToken(playerToken, row, col);

  // Check if player won
  if (m_board.GetTokenCountInRow(playerToken, row) == 3 ||
      m_board.GetTokenCountInCol(playerToken, col) == 3 ||
      m_board.GetTokenCountInDiag(playerToken,
                                  true /*topLeftBottomRightDiag*/) == 3 ||
      m_board.GetTokenCountInDiag(playerToken,
                                  false /*topLeftBottomRightDiag*/) == 3) {
    switch (GetCurrentPlayer()) {
    case Player::One:
      m_state = State::PlayerOneWon;
      s_stats.PlayerOneWinCount++;
      break;

    case Player::Two:
      m_state = State::PlayerTwoWon;
      s_stats.PlayerTwoWinCount++;
      break;
    }
    return;
  }

  // Check if game is a draw
  if (m_board.IsBoardFull()) {
    m_state = State::Draw;
    s_stats.DrawCount++;
    return;
  }

  // Switch turn to other player
  if (m_state == State::PlayerOnesTurn) {
    m_state = State::PlayerTwosTurn;
  } else if (m_state == State::PlayerTwosTurn) {
    m_state = State::PlayerOnesTurn;
  }
  s_stats.TurnCount++;
}

bool GameEngineCore::IsPositionOpen(int position) {
  return m_board.IsPositionOpen(PositionToRow(position),
                                PositionToCol(position));
}

bool GameEngineCore::IsGameOver() {
  switch (m_state) {
  case State::PlayerOnesTurn:
  case State::PlayerTwosTurn:
    return false;

  case State::PlayerOneWon:
  case State::PlayerTwoWon:
  case State::Draw:
    return true;
  }
}

bool GameEngineCore::IsDraw() { return m_state == State::Draw; }

GameEngineCore::Player GameEngineCore::GetWinner() {
  switch (m_state) {
  case State::PlayerOneWon:
    return Player::One;

  case State::PlayerTwoWon:
    return Player::Two;

  default:
    throw std::runtime_error("No player has won.");
  }
};

void GameEngineCore::PrintBoard() {
  std::cout << "Board:" << std::endl << m_board.ToString() << std::flush;
}

PlayerToken GameEngineCore::GetCurrentPlayerToken() {
  if (m_state == State::PlayerOnesTurn)
    return PlayerToken::One;
  if (m_state == State::PlayerTwosTurn)
    return PlayerToken::Two;

  throw std::runtime_error("Game is over!");
}

// Static data and functions
GameEngineCore::PlayStats GameEngineCore::s_stats{};
GameEngineCore::PlayStats GameEngineCore::GetStats() { return s_stats; }
void GameEngineCore::ClearStats() {
  s_stats.PlayerOneWinCount = 0;
  s_stats.PlayerTwoWinCount = 0;
  s_stats.DrawCount = 0;
  s_stats.TurnCount = 0;
}

void GameEngineCore::PrintStats() {
  auto totalGames =
      s_stats.PlayerOneWinCount + s_stats.PlayerTwoWinCount + s_stats.DrawCount;
  auto percentPlayerOneWins =
      totalGames > 0
          ? 100 * static_cast<double>(s_stats.PlayerOneWinCount) / totalGames
          : 0;
  auto percentPlayerTwoWins =
      totalGames > 0
          ? 100 * static_cast<double>(s_stats.PlayerTwoWinCount) / totalGames
          : 0;
  auto percentDraws =
      totalGames > 0 ? 100 * static_cast<double>(s_stats.DrawCount) / totalGames
                     : 0;

  std::cout.precision(2);
  std::cout << "Games Stats: { "
            << "TotalGames: " << totalGames
            << ", PlayerOneWins: " << s_stats.PlayerOneWinCount << "("
            << std::fixed << percentPlayerOneWins << "%)"
            << ", PlayerTwoWins: " << s_stats.PlayerTwoWinCount << "("
            << std::fixed << percentPlayerTwoWins << "%)"
            << ", Draws: " << s_stats.DrawCount << "(" << std::fixed
            << percentDraws << "%)"
            << ", Turns: " << s_stats.TurnCount << " }" << std::endl;
}

} // namespace TicTacToe
