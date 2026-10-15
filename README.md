# Client-Server Calculator in C

A simple client-server application written in C using TCP sockets. The client sends a mathematical expression to the server, the server evaluates it, and the result is sent back to the client.

## Features

- TCP communication using IPv4 sockets.
- Client-server architecture.
- Supports basic mathematical operations:
  - Addition (`+`)
  - Subtraction (`-`)
  - Multiplication (`*`)
  - Division (`/`)
  - Modulo (`%`)
- Validates mathematical expressions.
- Handles division by zero.
- Returns the calculation result or an error message.

## Technologies Used

- **C** — application logic
- **POSIX Sockets** — network communication
- **TCP/IP** — reliable client-server communication
- **Linux** — compilation and execution environment
- **GCC** — C compiler

## Project Structure

```text
client-server/
├── client.c
├── server.c
└── README.md
```

## Requirements

- Linux or another POSIX-compatible operating system
- GCC compiler
- Terminal

## Installation and Setup

### 1. Clone the repository

```bash
git clone <YOUR_REPOSITORY_URL>
cd client-server
```

Replace `<YOUR_REPOSITORY_URL>` with your repository's Git URL.

### 2. Compile the server

```bash
gcc server.c -o server
```

### 3. Compile the client

```bash
gcc client.c -o client
```

## How to Run

### 1. Start the server

Open a terminal and run:

```bash
./server
```

The server listens for incoming TCP connections on port `3000`.

Expected output:

```text
Server is listening on port 3000...
```

### 2. Start the client

Open a second terminal in the same project directory and run:

```bash
./client
```

Enter a mathematical expression when prompted.

Example:

```text
Input your mathematical expression -> 10 + 5
Server response: Result: 15.000000
```

### 3. Try different expressions

| Expression | Expected result |
|---|---:|
| `10 + 5` | `15` |
| `10 - 5` | `5` |
| `4 * 3` | `12` |
| `20 / 4` | `5` |
| `10 % 3` | `1` |
| `10 / 0` | Error message |

**Note:** The modulo operator (`%`) accepts integers only. The server currently handles one client connection and one expression per execution.

## How It Works

1. **Socket creation:** The server and client create TCP sockets.
2. **Server binding:** The server binds its socket to port `3000` and listens for connections.
3. **Client connection:** The client connects to `127.0.0.1:3000`.
4. **Expression input:** The client reads a mathematical expression from the user.
5. **Data transmission:** The client sends the expression to the server.
6. **Expression evaluation:** The server parses the expression, validates the operator and operands, and calculates the result.
7. **Response:** The server sends the result or an error message back to the client.
8. **Connection closure:** Both sides close their sockets.

## Networking Concepts Demonstrated

- TCP socket programming
- Client-server communication
- IPv4 addressing
- Port numbers
- `socket()`, `bind()`, `listen()`, `accept()`, `connect()`, `send()`, `recv()`, and `close()`
- Data exchange between processes
- Basic input validation and error handling

## Limitations

- The client connects to localhost (`127.0.0.1`), so both programs are intended to run on the same machine.
- The server handles only one client connection per execution.
- Only expressions with two operands and one supported operator are accepted.
- The current implementation does not guarantee that an entire message is transferred in a single `send()` or `recv()` call.

## Future Improvements

- Support multiple simultaneous clients.
- Add robust handling for partial TCP sends and receives.
- Implement stricter expression validation.
- Add unit tests for mathematical operations.
- Allow the client to connect to a configurable server IP address.
- Improve error handling for malformed input.

## Learning Objectives

This project demonstrates the fundamentals of TCP networking in C, socket programming, client-server architecture, data transmission, and basic server-side processing.

## Author

**Siranush Sargsyan**

GitHub: [Sir-c573](https://github.com/Sir-c573)
