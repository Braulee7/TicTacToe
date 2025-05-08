#include "rudp.h"
#include <cstring>
#include <iostream>
#include <memory>

std::unique_ptr<uint8_t[]> CreateBuffer(const char *message);

int main(int argc, const char **argv) {
  if (argc > 1) {
    std::cout << "sending message\n";
    Hev::TBD net("127.0.0.1", 5000, "127.0.0.1", 5001);
    net.Connect();
    const std::string message = "hello world\n";
    auto buff = CreateBuffer(message.c_str());
    net.Send(buff, message.length() + 1);
    // wait for a message back
    auto ack = net.Receive();
    std::cout << "Got back: " << ack.get() << std::endl;
  } else {
    std::cout << "waiting for message\n";
    Hev::TBD net("127.0.0.1", 5001, "127.0.0.1", 5000);
    net.Connect();
    auto message = net.Receive();
    std::cout << message.get() << std::endl;
    // send back a hello
    std::string msg_back = "hello back to yuh\n";
    auto buff = CreateBuffer(msg_back.c_str());
    net.Send(buff, msg_back.length() + 1);
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
