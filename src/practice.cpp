#include "game.h"

int main(int argc, char **argv) {
  // if (argc > 1) {
  //   Peer listener;
  //   if (listener.Invite("127.0.0.1", 5001) != 0) {
  //     std::cout << "Failed to connect to peer\n";
  //   } else {
  //     std::cout << "Connected to peer\n";
  //   }

  //   listener.Update();
  // } else {
  //   Peer connector("127.0.0.1", 5001);
  //   if (connector.Connect("127.0.0.1", 5000) != 0) {
  //     std::cout << "Failed to connect to peer\n";
  //   } else {
  //     std::cout << "Connected to peer\n";
  //   }
  //   connector.Update();
  // }
  Game game(argc, argv);
  game.Run();
  return 0;
}
