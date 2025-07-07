# Minishell

Minishell is an educational project developed as part of the **42 school** program. It implements a basic Unix-like shell in C, supporting:

- program execution with arguments
- pipes
- input/output redirections
- heredoc
- environment variable expansion
- signal handling

## Features

**Lexer and Parser**  
A lexer to tokenize user input and a recursive parser to build the internal command structure.
**Signal Handling**  
Support for Ctrl+C and Ctrl+D, including correct heredoc termination.
**Heredoc**  
Implementation of heredoc with variable expansion and EOF handling.
**Variable Expansion**  
Expanding environment variables in commands.
**Command Execution**  
Running binaries and built-in commands with pipes and redirections.
**Error Handling**  
Displaying appropriate error messages for invalid commands or syntax errors.
**Memory Management**  
Careful cleanup of all allocated resources.

## Work Split

**I worked on:**
- Lexer and parser
- Signal handling
- Built-ins
- Heredoc

**My teammate worked on:**
- Environment variable expansion
- Executor
- Error handling

**We worked together on:**
- Memory management
- Testing and debugging

## Build and Run

```bash
make
./minishell
```
