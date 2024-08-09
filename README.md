# Minishell

## Introduction

Minishell is a simplified version of a Unix shell, developed as part of the 42 school curriculum. The project aims to create a basic shell that can execute commands, manage processes, and handle signals, mimicking some of the core functionalities of Bash or other Unix-like command-line interpreters. The project was made possible thanks to the contribution of fgori; I personally took care of the parsing part and the signal management, while my colleague contributed to the development of the executor.

## Table of Contents

- [Minishell](#minishell)
	- [Introduction](#introduction)
	- [Table of Contents](#table-of-contents)
	- [Features](#features)
	- [Installation](#installation)
	- [To compile Minishell, follow these steps:](#to-compile-minishell-follow-these-steps)
	- [Usage](#usage)
	- [Built-in Commands](#built-in-commands)
	- [External Commands](#external-commands)
	- [Signal Handling](#signal-handling)
	- [Project Requirements](#project-requirements)
	- [Testing](#testing)
	- [Contributing](#contributing)
	- [License](#license)
## Features

- **Command execution with arguments**: Run commands with options (e.g., `ls -la`).
- **Input and output redirection**: Support for `<`,`<<`, and `>>`, `>` operators.
- **Piping**: Connect the output of one command to the input of another using `|`.
- **Environment variable handling**: Use and manage environment variables (e.g., `$VARIABLE`).
- **Basic signal handling**: Proper management of signals such as `Ctrl+C`, `CTRL+\` and `Ctrl+D` .
- **Built-in commands**: Includes essential commands like `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- **Error handling**: Displays appropriate error messages for invalid inputs and commands.

## Installation

### To compile Minishell, follow these steps:

1. **Clone the repository:**

    ```bash
    git clone https://github.com/yourusername/minishell.git
    ```

2. **Navigate to the project directory:**

    ```bash
    cd minishell
    ```

3. **Build the project using `make`:**

    ```bash
    make
    ```

    This will generate an executable named `minishell`.

## Usage

To start the shell, run the following command:
./minishell
```bash

$ pwd
/home/user/minishell

$ echo "Hello, World!"
Hello, World!

$ ls -la | grep minishell
-rwxr-xr-x  1 user  user  40960 Aug  9 12:00 minishell

$ export MY_VAR="42"
$ echo $MY_VAR
42

$ exit
```
## Built-in Commands

Minishell includes several built-in commands that are executed within the shell process:

- **`echo [args]`**: Prints the arguments to the standard output.
- **`cd [directory]`**: Changes the current directory.
- **`pwd`**: Prints the current working directory.
- **`export [name[=value]]`**: Sets or exports an environment variable.
- **`unset [name]`**: Unsets an environment variable.
- **`env`**: Prints the environment variables.
- **`exit [status]`**: Exits the shell with an optional status code.

## External Commands

For commands that are not built-in, Minishell searches for the executable in the directories listed in the `PATH` environment variable. It then creates a child process using `fork()` and executes the command in the child process using `execve()`.

## Signal Handling

Minishell handles the following signals:
- **`SIGINT` (Ctrl+C)**: Interrupts the current command and returns to the prompt without exiting the shell.
- **`SIGQUIT` (Ctrl+\)**: Ignored.
- **`EOF` (Ctrl+D)**: Exits the shell if the prompt is empty.

## Project Requirements

Minishell meets the following requirements set by the 42 school:
- No memory leaks, invalid reads/writes, or other memory issues (tested with `valgrind`).
- No use of external libraries other than those specified by the project guidelines.
- Proper handling of edge cases and errors, including invalid commands, permissions issues, and more.
- The shell works correctly with various test cases, as defined by the 42 school project.

## Testing

To test Minishell, you can manually run various commands to ensure correct behavior. You can also use tools like `valgrind` to check for memory issues:

```bash
valgrind --leak-check=full ./minishell
```

## Contributing

Contributions are welcome! If you find any bugs or have suggestions for improvements, please feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the LICENSE file for details.
