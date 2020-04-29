#include "game.h"

#include <exception>
#include <iostream>

using namespace TicTacToe;

namespace TicTacToe {

void Game::NewGame() {
  m_board.Clear();
  m_state = State::PlayerOnesTurn;
}

Game::Player Game::GetCurrentPlayer() {
  switch (m_state) {
  case State::PlayerOnesTurn:
    return Player::One;

  case State::PlayerTwosTurn:
    return Player::Two;

  default:
    throw std::runtime_error("Game is over!");
  }
}

void Game::PlayTurn(int index) {
  auto row = index / 3;
  auto col = index % 3;
  PlayTurn(row, col);
}

void Game::PlayTurn(int row, int col) {
  ThrowIfGameAlreadyOver();

  auto playerToken = GetCurrentPlayerToken();
  m_board.PlaceToken(playerToken, row, col);

  // Check if player won
  if (m_board.GetTokenCountInRow(playerToken, row) == 3 ||
      m_board.GetTokenCountInCol(playerToken, col) == 3 ||
      m_board.GetTokenCountInDiag(playerToken,
                                  true /*topLeftBottomRightDiag*/) == 3 ||
      m_board.GetTokenCountInDiag(playerToken,
                                  false /*topLeftBottomRightDiag*/) == 3) {
    m_state = State::PlayerOneWon;
    return;
  }

  // Check if game is finished
  if (m_board.IsBoardFull()) {
    m_state = State::Draw;
    return;
  }

  // Switch turn to other player
  if (m_state == State::PlayerOnesTurn) {
    m_state = State::PlayerTwosTurn;
  } else if (m_state == State::PlayerTwosTurn) {
    m_state = State::PlayerOnesTurn;
  }
}

bool Game::IsGameOver() {
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

bool Game::IsDraw() { return m_state == State::Draw; }

Game::Player Game::GetWinner() {
  switch (m_state) {
  case State::PlayerOneWon:
    return Player::One;

  case State::PlayerTwoWon:
    return Player::Two;

  default:
    throw std::runtime_error("No player has won.");
  }
};

void Game::PrintBoard() {
  std::cout << "Board:" << std::endl << m_board.ToString() << std::flush;
}

PlayerToken Game::GetCurrentPlayerToken() {
  if (m_state == State::PlayerOnesTurn)
    return PlayerToken::One;
  if (m_state == State::PlayerTwosTurn)
    return PlayerToken::Two;

  throw std::runtime_error("Game is over!");
}

void Game::ThrowIfGameAlreadyOver() {
  switch (m_state) {
  case State::PlayerOnesTurn:
  case State::PlayerTwosTurn:
    return;

  case State::Draw:
  case State::PlayerOneWon:
  case State::PlayerTwoWon:
    throw std::runtime_error("Game is already over");
  }
}

} // namespace TicTacToe
