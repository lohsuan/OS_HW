# Programming Problems 2.15

## Execute
This file was written in C language. Please make sure your environment work well with gcc.

1. open terminal in this directory
2. create your source file to copy or just use `source.txt` I provide
3. enter `gcc copy.c -o copy.o` in terminal
4. enter `./copy.o`  to run
5. follow the instruction in terminal

## Strace code in Linux

- enter `strace ./copy.o` to see the system calls OS makes while running the program
- `strace -ostrace_log ./copy.o` can store your system call into `strace_log` file after execution

