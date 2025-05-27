// tictactoe.cpp
// Implementation for the tic tac toe game
#include "tictactoe.h"
#include <iostream>

TicTacToe::TicTacToe() : m_turn(false) {
  for (size_t i = 0; i < MAX_ROWS; i++) {
    m_board[i] = "___";
  }
}

void TicTacToe::PrintBoard() const {
  char row_char = 'A';
  for (size_t i = 0; i < MAX_ROWS; i++) {
    std::cout << "\033[32m" << row_char << ": " << "\033[0m";
    for (size_t j = 0; j < m_board[i].length(); j++) {
      const char character = m_board[i][j];
      const char tile = InterpretChar(character);
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

const int TicTacToe::MakeMove(const size_t row, const size_t col) {
  if (row >= MAX_ROWS || col >= MAX_ROWS) {
    return OUT_OF_RANGE;
  }
  if (m_board[row][col] != '_')
    return INVALID_MOVE;
  if (m_turn) {
    m_board[row][col] = 'x';
  } else {
    m_board[row][col] = 'o';
  }
  m_turn = !m_turn;
  return 0;
}

std::string TicTacToe::GetGameState() const {
  std::string state;
  for (size_t i = 0; i < MAX_ROWS; i++) {
    state += m_board[i];
    state += '|';
  }
  state += "[";
  state += m_turn ? "X]" : "O]";

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
      m_turn = state[i + 1] == 'X' ? true : false;
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
