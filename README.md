# OS Command Runner

The OS Command Runner is a simple utility program that reads commands from a file, executes them as separate processes, and displays the output. It utilizes concepts related to operating systems, process management, and inter-process communication.

## Motivation

The motivation behind developing the OS Command Runner stemmed from a desire to deepen understanding of operating system concepts and process management in the context of C programming. By creating this utility, we aimed to:

- Gain hands-on experience with fork(), exec(), and inter-process communication mechanisms such as pipes.
- Explore practical aspects of managing child processes efficiently.
- Improve proficiency in C programming and POSIX-compliant system calls.
- Develop a useful tool for executing multiple commands sequentially from a file.

## Features

- Reads commands from a file and executes them sequentially.
- Manages child processes efficiently using fork() and exec().
- Implements inter-process communication using pipes.
- Cleans up resources after execution.

## Getting Started

### Prerequisites

- C compiler (gcc recommended)
- POSIX-compliant operating system (Linux, macOS)

### Installation

1. Clone the repository:

```bash
git clone https://github.com/your_username/os-command-runner.git
