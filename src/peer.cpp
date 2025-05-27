#include "peer.h"
#include <iostream>

Peer::Peer(const char *ip, const int port) {
  m_socket = new Hev::TBD(Hev::TBD::Bind(ip, port));
}

Peer::~Peer() { delete m_socket; }

const int Peer::Invite(const char *peer_ip, const int peer_port) {
  if (!m_socket) {
    return NOT_INITIALIZED;
  }
  return m_socket->Listen(peer_ip, peer_port);
}

const int Peer::Connect(const char *peer_ip, const int peer_port) {
  if (!m_socket) {
    return NOT_INITIALIZED;
  }
  return m_socket->Connect(peer_ip, peer_port);
}

const int Peer::Update() {
  bool finished = false;
  do {
    std::string move;
    // poll for moves
    std::cout << "Enter space you want to place your move (ie A1):";
    std::cin >> move;
    std::cout << "Registered move is: " << move << '\n';
  } while (finished);
}
