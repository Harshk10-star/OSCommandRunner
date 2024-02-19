# OS Command Runner

The OS Command Runner is a simple utility program that reads commands from a file, executes them as separate processes, and displays the output. It utilizes concepts related to operating systems, process management, and inter-process communication.

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
