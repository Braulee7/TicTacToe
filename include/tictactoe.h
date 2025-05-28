// tictactoe.h
// The main game state of the Tic-Tac-Toe game
// will manage input validation and rendering
#pragma once
#include <string>

#define MAX_ROWS 3
#define SCORE_SIZE MAX_ROWS * 2 + 2
// errors regarding the gamestate
#define OUT_OF_RANGE 0x401
#define INVALID_MOVE 0x402
#define GAME_OVER 0x410
#define GAME_WIN 0x411
#define GAME_DRAW 0x412

enum Player {
  X = 'x',
  O = 'o',
  NONE = '_',
};

enum State {
  PLAYING = 'P',
  WIN = 'W',
  DRAW = 'D',
};

class TicTacToe {
public:
  TicTacToe();
  ~TicTacToe() = default;
  void PrintBoard() const;
  const int MakeMove(const Player player, const size_t row, const size_t col);
  std::string GetGameState() const;
  const int UpdateFromState(const std::string &state);

private:
  char InterpretChar(const char character) const;
  bool DetectWin();

private:
  std::string m_board[MAX_ROWS];
  int m_score_board[SCORE_SIZE];
  State m_state;
  Player m_winner;
  int m_moves_left;

  const static int X_POINT = 1;
  const static int O_POINT = -1;
};
