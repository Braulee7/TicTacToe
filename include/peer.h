// peer.h
// This is a player in the game that will
// have a game state, make connections
// and play the game
#pragma once
#include "rudp.h"
#include "tictactoe.h"

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT 5000

#define NOT_INITIALIZED 0x404
class Peer {
public:
  Peer(const char *ip = DEFAULT_IP, const int port = DEFAULT_PORT);
  ~Peer();
  const int Invite(const char *peer_ip, const int peer_port);
  const int Connect(const char *peer_ip, const int peer_port);
  const int Update();

private:
  Hev::TBD *m_socket;
  TicTacToe m_state;
};
