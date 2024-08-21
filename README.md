# 42-MiniShell

![MiniShell](https://img.shields.io/badge/42-Project-blue.svg) ![Shell](https://img.shields.io/badge/Shell-Bash-green.svg)

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The **42-MiniShell** project is a simplified version of a Unix shell, created as part of the 42 school curriculum. The project aims to replicate the behavior of a shell, enabling users to execute commands, manage processes, and handle redirections and pipes, among other shell features.

This project was designed to deepen the understanding of system calls, process management, and the intricacies of how a shell works under the hood.

## Features

- **Prompt Display:** Displays a customizable prompt to the user.
- **Command Execution:** Supports the execution of basic Unix commands.
- **Pipes and Redirections:** Implements command piping and I/O redirection.
- **Built-in Commands:** Includes basic built-in commands like `cd`, `echo`, `exit`, etc.
- **Signal Handling:** Handles typical shell signals like `Ctrl+C`, `Ctrl+D`, etc.
- **Environment Variables:** Manages and manipulates environment variables.
- **Error Handling:** Provides basic error handling for unsupported commands and incorrect syntax.

## Installation

To get started with the 42-MiniShell, clone the repository and compile the project:

```bash
git clone https://github.com/mehdisalim/42-MiniShell.git
cd 42-MiniShell
make
```
This will generate the minishell executable in the project directory.

## Usage
After compiling, you can start the shell by running:
```bash
./minishell
```
Once inside the shell, you can start typing commands just as you would in a regular Unix shell.

```bash
minishell> ls -la
minishell> echo "Hello, World!"
minishell> cd /path/to/directory
minishell> exit
```

## Built-in Commands
The shell includes several built-in commands:

- `echo`: Displays a line of text.
- `cd`: Changes the current directory.
- `pwd`: Prints the current working directory.
- `export`: Sets environment variables.
- `unset`: Unsets environment variables.
- `env`: Displays the environment variables.
- `exit`: Exits the shell.

## Contributing
Contributions are welcome! If you'd like to improve or extend the functionality of this project, feel free to fork the repository, make your changes, and submit a pull request.

Please make sure to follow the project's coding guidelines and best practices when contributing.

## License
This project is licensed under the MIT License. See the LICENSE file for details.
