#include "game.h"
#include "errors.h"
#include "peer.h"
#include <getopt.h>
#include <iostream>
#include <unistd.h>

Game::Game(int argc, char **argv) : m_client(nullptr) {
  ParseCommandLine(argc, argv);
}

Game::~Game() {
  if (m_client)
    delete m_client;
}

void Game::Run() {
  if (!m_client) {
    std::cout << "Game not initialized properly, no client\n";
    return;
  }
  bool finished = false;
  m_client->Draw();
  do {
    int status = 0;
    status = m_client->Update();

    if (status == SOCKET_CLOSED) {
      std::cout << "Lost connection to peer\n";
      finished = true;
      break;
    }
    if (((status & GAME_OVER) == GAME_OVER)) {
      finished = true;
    }
    system("clear");
    m_client->Draw();
  } while (!finished);
}

// options for the command line
// -l --listen : local ip address
// -p --port : local port number
// -c --connect: indicates that player wants to connect
//  to a peer
// -i --invite : indicates that players wants to invite
//  a peer
//  both i and c options have an optional argument of
//  the ip address to connect to. If not provided then
//  the default ip of 127.0.0.1 is used
// -o --other-port : the peer port to connect to
// -h --help : print this
void Game::ParseCommandLine(int argc, char **argv) {
  int opt = 0;
  std::string my_ip = DEFAULT_IP, peer_ip = DEFAULT_IP;
  int my_port = DEFAULT_PORT, peer_port = DEFAULT_PORT;
  bool invite = false;
  int status = 0;
  static const int CONNECT_FLAG = 0x01;
  static const int INVITE_FLAG = 0x02;

  static struct option long_options[] = {
      {"listen", required_argument, 0, 'l'},
      {"port", required_argument, 0, 'p'},
      {"connect", optional_argument, 0, 'c'},
      {"invite", optional_argument, 0, 'i'},
      {"other-port", required_argument, 0, 'o'},
      {"help", no_argument, 0, 'h'},
      {0, 0, 0, 0}};
  while ((opt = getopt_long(argc, argv, "l:p:c::i::o:h", long_options, NULL)) !=
         -1) {
    switch (opt) {

    case 'l': // ip address this client will listen on
      my_ip = optarg;
      break;
    case 'p': // listening port
      my_port = atoi(optarg);
      if (my_port == 0) {
        std::cout << "Couldn't convert " << optarg << " to a port value\n";
        exit(EXIT_FAILURE);
      }
      break;
    case 'c':
      if (optarg) {
        peer_ip = optarg;
      }
      break;
    case 'i':
      if (optarg) {
        peer_ip = optarg;
      }
      invite = true;
      break;
    case 'o':
      peer_port = atoi(optarg);
      if (peer_port == 0) {
        std::cout << "Couldn't convert " << optarg << " to a port value\n";
        exit(EXIT_FAILURE);
      }
      break;
    case 'h':
      PrintHelp();
      exit(0);
    default: /* '?' */
      std::cout << "Unknown option [" << (char)opt << "]\n";
      exit(EXIT_FAILURE);
    }
  }
  // build client
  m_client = new Peer(my_ip.c_str(), my_port);
  if (invite) {
    status = m_client->Invite(peer_ip.c_str(), peer_port);
  } else {
    status = m_client->Connect(peer_ip.c_str(), peer_port);
  }
  if (status != 0) {
    std::cout << "Failed to make connection with peer at ip: [" << peer_ip
              << ":" << peer_port << "\nError code: " << status << '\n';
  }
}

void Game::PrintHelp() {
  std::cout
      << "Tic-Tac-Toe game <CS494P @ Portland State University>\n-l --listen "
         "<ip address> \t Change the local ip port to "
         "listen on\n"
      << "-p --port <number> \t\t Change local port to listen on \n"
      << "-c --connect ?<ip address> \t Set this client to connect to a "
         "peer on the\n\t\t\t\t given address if any. If none is given "
         "client\n\t\t\t\t will "
         "connect to default ip address 127.0.01.\n\t\t\t\t If neither this "
         "n'or the invite flag is given, the\n\t\t\t\t"
         " client will be set to connect to the default ip\n"
      << "-i --invite ?<ip address> \t Set this client to invite and wait for "
         "a connection\n\t\t\t\t to the given ip address if any. If none "
         "\n\t\t\t\t "
         "is given, "
         "client will invite the default ip address of\n\t\t\t\t 127.0.0.1. If "
         "neither "
         "this n'or "
         "the invite flag is given,\n\t\t\t\t the client will be set to "
         "connect "
         "to the "
         "default ip\n"
      << "-o --other-port <number> \t Give a different peer port to connect "
         "to. If this\n\t\t\t\t this option is ommitted the client will try "
         "to\n\t\t\t\t connect to a peer on port 5000\n"
      << "-h --help \t\t\t display this message\n";
}
