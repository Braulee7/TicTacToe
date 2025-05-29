#include "peer.h"
#include "errors.h"
#include "tictactoe.h"
#include <iostream>
#include <memory>

Peer::Peer(const char *ip, const int port)
    : m_connected(false), m_my_turn(false), m_me(Player::NONE) {
  m_socket = new Hev::TBD(Hev::TBD::Bind(ip, port));
}

Peer::~Peer() { delete m_socket; }

const int Peer::Invite(const char *peer_ip, const int peer_port) {
  if (!m_socket) {
    return NOT_INITIALIZED;
  }
  const int status = m_socket->Listen(peer_ip, peer_port);
  if (status == 0) {
    m_my_turn = true;
    m_me = Player::X;
    m_connected = true;
  }
  return status;
}

const int Peer::Connect(const char *peer_ip, const int peer_port) {
  if (!m_socket) {
    return NOT_INITIALIZED;
  }
  const int status = m_socket->Connect(peer_ip, peer_port);
  if (status == 0) {
    m_me = Player::O;
    m_connected = true;
  }
  return status;
}

const int Peer::Update() {
  int status = 0;
  if (m_my_turn) {
    status = PollMove();
  } else {
    status = WaitForMove();
  }
  return status;
}

const int Peer::Draw() {
  m_state.PrintBoard();
  return 0;
}

const int Peer::ParseMove(std::string &move, size_t *parsed_row,
                          size_t *parsed_col) {
  if (move.length() < 2) {
    return INVALID_MOVE;
  }

  move[3] = 0;
  if (move[0] < 'A' || move[0] > 'C') {
    std::cout << "Invalid row: " << move[0] << "\nTry again\n";
    return INVALID_MOVE;
  }
  if (move[1] < '1' || move[1] > '3') {
    std::cout << "Invalid column: " << move[1] << "\nTry again\n";
    return INVALID_MOVE;
  }
  if (!parsed_row || !parsed_col) {
    return NOT_INITIALIZED;
  }
  *parsed_row = (int)(move[0] - 'A');
  *parsed_col = (int)(move[1] - '1');
  return 0;
}

const int Peer::PollMove() {
  std::string move;
  size_t row = 0, col = 0;
  // poll for moves
  std::cout << "Enter space you want to place your move (ie A1):";
  std::cin >> move;
  int status = ParseMove(move, &row, &col);
  if (status != 0) {
    return status;
  }
  status = m_state.MakeMove(m_me, row, col);
  if (status != INVALID_MOVE) {
    m_my_turn = false;
    SendMove(move);
  }
  return status;
}
const int Peer::WaitForMove() {
  std::cout << "Waiting for other player ...\n";
  int status = 0;
  Hev::Buffer state;
  status = m_socket->Receive(&state);
  if (!state) {
    return status;
  }
  std::string response(reinterpret_cast<const char *>(state.get()));
  // get move and player
  std::string move;
  std::string player;
  SplitResponse(response, move, player);

  size_t row, col;
  ParseMove(move, &row, &col);
  status = m_state.MakeMove((Player)player[0], row, col);

  if (status != INVALID_MOVE) {
    m_my_turn = true;
  } else {
    // tell peer to redo move
  }
  return status;
}

const int Peer::SendMove(std::string &move) {
  move += "-";
  move += m_me;
  Hev::Buffer buff = std::make_unique<uint8_t[]>(move.size());
  strncpy((char *)buff.get(), move.c_str(), move.size());

  return m_socket->Send(buff, move.size());
}

const int Peer::SplitResponse(std::string &response, std::string &move,
                              std::string &player) {
  const size_t split_index = response.find('-');
  if (split_index == std::string::npos)
    return INVALID_MOVE;
  player = response.substr(split_index + 1);
  response[split_index] = '\0';
  move = response;
  return 0;
}
