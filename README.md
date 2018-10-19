TCP Programming Project for CSCI 450

GitHub Repository Link:
    https://github.com/Elicarter20/TCProgrammingProject

To run program:

    client        gcc ./src/client.c -o client
            ./client <server IP> <server port> <file path> <to format> <to name>

    server        gcc server.c translator.c -o server
            ./server.exe <port>

    Program was written in a Unix environment (Unix libraries for socket programming, etc..) in Cygwin for Windows.

Application Protocol
Types of messages
There is only one type of message
1 single byte representing a request or response
Syntax and semantics of each message type
1 byte messages are read through a read($socket, $c, 1) command or written through a write($socket, $c, 1) command
Format of messages
[data] - 1 byte
Meaning of each field in the format
[data]: a single ASCII character
Value range of each field
0 to 255 for unsigned

Rules of sending messages
Messages must follow the format described above or the server disconnects, and client program ends.
Messages are always 1 byte
Messages sending and receiving follows the algorithm laid out below
Both client and server send same message type (1 single byte)
