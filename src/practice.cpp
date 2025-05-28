#include "peer.h"
#include "rudp.h"
#include "tictactoe.h"
#include <cstring>
#include <iostream>
#include <memory>

std::unique_ptr<uint8_t[]> CreateBuffer(const char *message);

int main(int argc, const char **argv) {
  // if (argc > 1) {
  //   std::cout << "sending message\n";
  //   Hev::TBD net = Hev::TBD::Bind("127.0.0.1", 5000);
  //   if (net.Listen("127.0.0.1", 5001) != 0) {
  //     std::cout << "Didn't receive any peer connections\n";
  //     return -1;
  //   }
  //   std::cout << "Connected to peer\n";
  //   const std::string message = "hello world\n";
  //   auto buff = CreateBuffer(message.c_str());
  //   net.Send(buff, message.length());
  //   std::cout << "sent message " << message << "\n";
  //   // wait for a message back
  //   auto ack = net.Receive();
  //   std::cout << "Got back: " << ack.get() << std::endl;
  // } else {
  //   std::cout << "waiting for message\n";
  //   Hev::TBD net = Hev::TBD::Bind("127.0.0.1", 5001);
  //   if (net.Connect("127.0.0.1", 5000) < 0) {
  //     std::cout << "failed to connect to peer\n";
  //     return -1;
  //   }
  //   std::cout << "connected to peer\n";
  //   auto message = net.Receive();
  //   std::cout << message.get() << std::endl;
  //   // send back a hello
  //   std::string msg_back = "hello back to yuh\n";
  //   std::cout << "sending back " << msg_back << "\n";
  //   auto buff = CreateBuffer(msg_back.c_str());
  //   net.Send(buff, msg_back.length() + 1);
  // }
  //
  if (argc > 1) {
    Peer listener;
    if (listener.Invite("127.0.0.1", 5001) != 0) {
      std::cout << "Failed to connect to peer\n";
    } else {
      std::cout << "Connected to peer\n";
    }

    listener.Update();
  } else {
    Peer connector("127.0.0.1", 5001);
    if (connector.Connect("127.0.0.1", 5000) != 0) {
      std::cout << "Failed to connect to peer\n";
    } else {
      std::cout << "Connected to peer\n";
    }
    connector.Update();
  }
  return 0;
}

std::unique_ptr<uint8_t[]> CreateBuffer(const char *message) {
  const size_t message_len = strlen(message);
  std::unique_ptr<uint8_t[]> buff =
      std::make_unique<uint8_t[]>(message_len + 1);
  strncpy((char *)buff.get(), message, message_len + 1);

  return buff;
}
