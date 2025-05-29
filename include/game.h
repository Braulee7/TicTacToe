// game.h
// main class to drive the game
// this will handle creating the peers
// and setting everything up
#include "peer.h"

class Game {
public:
  Game(int argc, char **argv);
  ~Game();
  void Run();

private:
  void ParseCommandLine(int argc, char **argv);
  void static PrintHelp();

private:
  Peer *m_client;
};
