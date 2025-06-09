# Tic Tac Toe
This is a program as a final project for CS492P @ Portland State University

It's a simple multiplayer tic tac toe game which uses a custom built reliable
UDP protocol for the messaging between the users. It currently only supports
POSIX sockets and is a command line project.

## Build
To built the program, run `git clone https://github.com/Braulee7/TicTacToe.git --recursive` to make sure you also
grab the [HevNet](https://github.com/Braulee7/TicTacToe) repository which holds the socket functionality.
The project then uses CMake to built so once everything is downloaded, simply
run `cmake -B build` to create a the cmake build directory. Finally, to 
compile run `cmake --build build` from the root repository and everything
should compile fine. 

## Usage
To run the program you have two options. 
1. To be the "host" user and invite the peer to join you
  To invite a user run
  ```bash
./build/TicTacToed -i
  ```
2. Join another user who has already invited you
   To join a user run:
   ```bash
   ./build/TicTacToed -c
   ```
Either of these commands will use the default IP and port numbers in the 
program which are **127.0.0.1** and **5000** to run locally on LAN. You can
change these via the following paramaters:
  `-l | --listen <ip>` will change the IP address to accept connections and messages from
  `-p | --port <port>` will change the port number to listen on
  `-<c or i depending on your mode> <ip>` will change the IP address you are either joining or inviting
  `-o | --other <port>` will change the port number of your peer
All these options can be seen with the `-h | --help` command line arg
If no command line args are given you are going to be inviting on the default port and IPs

