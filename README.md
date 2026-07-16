# Minishell

Minishell is a project for the **42 school** curriculum. It is a simple Unix-like shell written in C that supports command execution, pipes, redirections, and other basic shell features. The project uses an abstract syntax tree (AST) for parsing, dispatch tables for built-in commands, and clear error handling.

Developed in collaboration with [@tetiana-cherni](https://github.com/tetiana-cherni).

## Features

- Command execution with arguments
- Pipes and redirections (including heredoc)
- Environment variable expansion
- Built-in commands
- Command history
- Signal handling (Ctrl+C, Ctrl+D)
- Exit status handling (`$?`)
- Memory management to prevent leaks

## Work Split

**Me:**

- Lexer and parser
- Signal handling
- Built-ins
- Heredoc

**[@tetiana-cherni](https://github.com/tetiana-cherni):**

- Environment variable expansion
- Execution engine
- Centralised error handling
- Shell lifecycle

**Shared responsibilities:**

- Memory management
- Testing and debugging

## Build and Run

```bash
make
./minishell
```

### Run with Docker

You can run minishell in an isolated Linux environment using Docker. This ensures the project runs identically across macOS, Windows and Linux.

Prerequisites:
- Docker Desktop installed and running

1. Build the Docker image:
```bash
docker build -t minishell_img .
```

2. Run the interactive container:
```bash
docker run -it --rm minishell_img
```
