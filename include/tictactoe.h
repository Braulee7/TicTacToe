// tictactoe.h
// The main game state of the Tic-Tac-Toe game
// will manage input validation and rendering
#pragma once
#include <string>

#define MAX_ROWS 3
// errors regarding the gamestate
#define OUT_OF_RANGE 0x401
#define INVALID_MOVE 0x402

class TicTacToe {
public:
  TicTacToe();
  ~TicTacToe() = default;
  void PrintBoard() const;
  const int MakeMove(const size_t row, const size_t col);
  std::string GetGameState() const;
  const int UpdateFromState(const std::string &state);

private:
  char InterpretChar(const char character) const;

private:
  std::string m_board[MAX_ROWS];
  bool m_turn;
};
