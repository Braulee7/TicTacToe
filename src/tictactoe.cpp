// tictactoe.cpp
// Implementation for the tic tac toe game
#include "tictactoe.h"
#include <iostream>

TicTacToe::TicTacToe()
    : m_state(State::PLAYING), m_moves_left(MAX_ROWS * MAX_ROWS) {
  size_t i = 0;
  for (; i < MAX_ROWS; i++) {
    m_board[i] = "___";
    m_score_board[i] = 0;
  }
  for (; i < MAX_ROWS * 2 + 2; i++) {
    m_score_board[i] = 0;
  }
}

void TicTacToe::PrintBoard() const {
  char row_char = 'A';
  if (m_state == State::WIN) {
    std::cout << "Player " << (char)m_winner << " WINS!!!\n";
  } else if (m_state == State::DRAW) {
    std::cout << "Game ends in DRAW\n";
  }
  for (size_t i = 0; i < MAX_ROWS; i++) {
    std::cout << "\033[32m" << row_char << ": " << "\033[0m";
    for (size_t j = 0; j < m_board[i].length(); j++) {
      const char character = m_board[i][j];
      const char tile = character == Player::NONE ? ' ' : character;
      std::cout << " " << tile;
      if (j < m_board[i].length() - 1) {
        std::cout << " |";
      }
    }
    if (i < MAX_ROWS - 1) {
      std::cout << "\n   -----------\n";
    }
    row_char++;
  }
  std::cout << "\033[32m\n    1   2   3 \n" << "\033[0m";
}

const int TicTacToe::MakeMove(const Player player, const size_t row,
                              const size_t col) {
  if (m_state != State::PLAYING)
    return GAME_OVER;
  if (row >= MAX_ROWS || col >= MAX_ROWS) {
    return OUT_OF_RANGE;
  }
  if (m_board[row][col] != Player::NONE)
    return INVALID_MOVE;

  m_board[row][col] = player;
  m_moves_left--;

  { // update score
    int point = 0;
    if (player == Player::X)
      point = X_POINT;
    else
      point = O_POINT;

    m_score_board[row] += point;
    m_score_board[MAX_ROWS + col] += point;
    if (row == col)
      m_score_board[2 * MAX_ROWS] += point;
    if (MAX_ROWS - 1 - col == row)
      m_score_board[2 * MAX_ROWS + 1] += point;
  }

  if (DetectWin()) {
    return GAME_WIN;
  }

  return 0;
}

std::string TicTacToe::GetGameState() const {
  std::string state;
  for (size_t i = 0; i < MAX_ROWS; i++) {
    state += m_board[i];
    state += '|';
  }
  state += "[";
  state += m_state;
  state += "]";

  return state;
}

const int TicTacToe::UpdateFromState(const std::string &state) {
  size_t curr_row = 0;
  size_t curr_col = 0;
  for (size_t i = 0; i < state.length(); i++) {
    char character = state[i];
    if (character == '|') {
      curr_row++;
      curr_col = 0;
    } else if (character == '[') {
      m_state = (State)state[i + 1];
      break;
    } else {
      m_board[curr_row][curr_col] = character;
      curr_col++;
    }
  }

  return 0;
}

char TicTacToe::InterpretChar(const char character) const {
  switch (character) {
  case 'x':
    return 'X';
  case 'o':
    return 'O';
  default:
    return ' ';
  }
}

bool TicTacToe::DetectWin() {
  if (m_moves_left == 0) {
    m_state = State::DRAW;
    return false;
  }
  for (size_t i = 0; i < SCORE_SIZE; i++) {
    if (m_score_board[i] == (MAX_ROWS * X_POINT)) {
      m_winner = Player::X;
      m_state = State::WIN;
      return true;
    } else if (m_score_board[i] == (MAX_ROWS * O_POINT)) {
      m_winner = Player::O;
      m_state = State::WIN;
      return true;
    }
  }

  return false;
}
