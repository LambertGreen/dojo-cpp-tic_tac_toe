#include "GameEngineCore.h"

#include <exception>
#include <iomanip>
#include <iostream>

using namespace TicTacToe;

namespace TicTacToe {

void GameEngineCore::PlayTurn(int pos) {
  // Throw if game is over
  if (IsGameOver()) {
    throw std::runtime_error("Game is already over");
  }

  // Place player token on board
  auto playerToken = GetCurrentPlayerToken();
  m_board.PlaceToken(playerToken, pos);

  // Check if player won
  if (IsWinningPlay(playerToken, pos)) {
    switch (GetCurrentPlayer()) {
    case Player::One:
      UpdateState(State::PlayerOneWon);
      break;

    case Player::Two:
      UpdateState(State::PlayerTwoWon);
      break;
    }
    return;
  }

  // Check if game is a draw
  if (m_board.IsBoardFull()) {
    UpdateState(State::Draw);
    return;
  }

  // Switch turn to other player
  if (m_state == State::PlayerOnesTurn) {
    UpdateState(State::PlayerTwosTurn);
  } else if (m_state == State::PlayerTwosTurn) {
    UpdateState(State::PlayerOnesTurn);
  }
}

GameEngineCore::Player GameEngineCore::GetCurrentPlayer() const {
  switch (m_state) {
  case State::PlayerOnesTurn:
    return Player::One;

  case State::PlayerTwosTurn:
    return Player::Two;

  default:
    throw std::runtime_error("Game is over!");
  }
}

bool GameEngineCore::IsGameOver() const {
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

bool GameEngineCore::IsDraw() const { return m_state == State::Draw; }

GameEngineCore::Player GameEngineCore::GetWinner() const {
  switch (m_state) {
  case State::PlayerOneWon:
    return Player::One;

  case State::PlayerTwoWon:
    return Player::Two;

  default:
    throw std::runtime_error("No player has won.");
  }
};

GameBoard GameEngineCore::GetBoard() const { return m_board; }

PlayerToken GameEngineCore::GetCurrentPlayerToken() const {
  if (m_state == State::PlayerOnesTurn)
    return PlayerToken::One;
  if (m_state == State::PlayerTwosTurn)
    return PlayerToken::Two;

  throw std::runtime_error("Game is over!");
}

void GameEngineCore::UpdateState(State newState) { m_state = newState; }

bool GameEngineCore::IsWinningPlay(PlayerToken token, int pos) const {

  return (m_board.GetTokenCountInRow(token, pos) == 3 ||
          m_board.GetTokenCountInCol(token, pos) == 3 ||
          m_board.GetTokenCountInDiag(token, true /*topLeftBottomRightDiag*/) ==
              3 ||
          m_board.GetTokenCountInDiag(token,
                                      false /*topLeftBottomRightDiag*/) == 3);
}

// void GameEngineCore::PrintStats() {
//   auto totalGames =
//       s_stats.PlayerOneWinCount + s_stats.PlayerTwoWinCount +
//       s_stats.DrawCount;
//   auto percentPlayerOneWins =
//       totalGames > 0
//           ? 100 * static_cast<double>(s_stats.PlayerOneWinCount) / totalGames
//           : 0;
//   auto percentPlayerTwoWins =
//       totalGames > 0
//           ? 100 * static_cast<double>(s_stats.PlayerTwoWinCount) / totalGames
//           : 0;
//   auto percentDraws =
//       totalGames > 0 ? 100 * static_cast<double>(s_stats.DrawCount) /
//       totalGames
//                      : 0;

//   std::cout.precision(2);
//   std::cout << "Games Stats: { "
//             << "TotalGames: " << totalGames
//             << ", PlayerOneWins: " << s_stats.PlayerOneWinCount << "("
//             << std::fixed << percentPlayerOneWins << "%)"
//             << ", PlayerTwoWins: " << s_stats.PlayerTwoWinCount << "("
//             << std::fixed << percentPlayerTwoWins << "%)"
//             << ", Draws: " << s_stats.DrawCount << "(" << std::fixed
//             << percentDraws << "%)"
//             << ", Turns: " << s_stats.TurnCount << " }" << std::endl;
// }

} // namespace TicTacToe
