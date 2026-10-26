# get_next_line

A function that reads a file descriptor line by line, written for the 42 Network core curriculum.

> **Status:** Work in progress (WIP)

## Overview

The purpose of `get_next_line` is to implement a function with the prototype:

```c
char *get_next_line(int fd);
```

Repeated calls to `get_next_line` read text from the file descriptor `fd` one line at a time until reaching EOF or an error. Each returned line includes the terminating `\n` character unless the end of file was reached without one.

## Implementation Details

- **Static buffer:** Uses a static pointer to persist leftover bytes from previous `read()` operations across function invocations.
- **Buffer size:** Configurable via `-D BUFFER_SIZE=n` at compile time, defaulting to 42.
- **Reading loop:** Reads chunks of `BUFFER_SIZE` bytes into a temporary buffer, appending them to the static accumulator with `ft_strjoin` until a newline (`\n`) is encountered or `read()` returns 0.
- **Line extraction:** Extracts the line up to and including `\n` to return to the caller, while reallocating the static pointer to retain only the unread remainder.

## Compilation

To compile with a main program and custom buffer size:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

## Norminette

All source files adhere to 42's Norminette (v4) requirements.
