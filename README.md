*This project has been created as part of the 42 curriculum by oabu-awa.*

# Get Next Line

## Description

The **Get Next Line** project is an essential milestone in the 42 Network core curriculum. The objective of this project is to implement a C function, `get_next_line(int fd)`, that reads and returns a single line from a given file descriptor each time it is called.

Key features and behaviors:
- Reads sequentially from standard files, standard input (`stdin`), or pipes.
- Returns each line including the terminating newline (`\n`) character, unless the end-of-file (EOF) is reached without one.
- Returns `NULL` when there is nothing left to read (EOF reached) or when an error occurs.
- Manages memory dynamically with zero memory leaks across varying buffer sizes.
- **Bonus Feature:** Supports simultaneous reading from multiple file descriptors independently using a single static array of pointers (`OPEN_MAX`).

## Instructions

### Prerequisites
- GCC or Clang compiler
- Standard C libraries (`stdlib.h`, `unistd.h`, `limits.h`)

### Compilation

You can compile `get_next_line` with your test application using the `-Wall -Wextra -Werror` flags, optionally specifying a buffer size using `-D BUFFER_SIZE=n`:

```bash
# Mandatory compilation (default BUFFER_SIZE = 42)
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl

# Compilation with custom BUFFER_SIZE (e.g. 1, 32, 10000000)
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c -o gnl

# Bonus compilation (supports multiple fds concurrently)
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

### Execution Example

Create a simple `main.c`:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd = open("sample.txt", O_RDONLY);
	char *line;

	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```

Run the compiled executable:

```bash
./gnl
```

## Resources

### References
- **`read(2)` man page**: Understanding POSIX read semantics, buffer handling, EOF (`0`), and error conditions (`-1`).
- **Static Variables in C**: Deep dive into variable lifetimes, data segment vs. heap allocation, and persisting state across function calls.
- **File Descriptors in Unix/Linux**: Standard streams (`0`, `1`, `2`), open file table limits (`OPEN_MAX`), and resource handling.
- **Valgrind Documentation**: Memory leak detection and memory profiling in C.

### AI Usage
Artificial Intelligence was used as a peer-review and testing assistant during the final validation phase of this project:
- **Test Generation & Coverage**: Writing comprehensive edge-case test harnesses (empty files, single characters, consecutive `\n`, huge buffers, standard input streams, and alternating multiple file descriptors).
- **Static Analysis & Edge Case Discovery**: Identifying potential corner cases such as read errors occurring midway through streams, bounds checking on file descriptors, and verifying strict adherence to 42 Norminette v4 and the Version 14.3 subject guidelines.
- **Documentation**: Assisting in structuring and formatting the project README in full compliance with Chapter V requirements.

## Algorithm Explanation and Justification

The algorithm for `get_next_line` is structured around a static accumulator pointer that preserves unparsed characters between function calls:

1. **Read & Accumulate (`read_str`)**:
   - A heap buffer of size `BUFFER_SIZE + 1` is allocated to read chunks from the file descriptor.
   - The loop reads up to `BUFFER_SIZE` bytes per `read()` call and appends them to the static accumulator `str` using `ft_strjoin`.
   - The loop terminates as soon as a newline (`\n`) is encountered in the accumulated string, EOF is reached (`bytes == 0`), or an error occurs (`bytes == -1`).
   - If an error occurs during reading or memory allocation, all allocated memory is properly freed and `NULL` is returned to prevent leaks or dangling references.

2. **Extract Line (`get_line`)**:
   - Once a newline is present or EOF is reached, `get_line` scans `str` to locate the first `\n` or `\0`.
   - It allocates and copies exactly the required number of characters (including `\n` if present), followed by a null terminator `\0`.
   - This isolated line string is returned to the caller.

3. **Retain Remainder (`next_line`)**:
   - `next_line` extracts the remainder of `str` after the extracted line.
   - It allocates memory for the leftover characters, copies them, frees the previous accumulator buffer, and returns the new trimmed remainder to be stored in the static variable for the next invocation.
   - If no characters remain after the line, the static pointer is freed and set to `NULL`.

4. **Bonus Multi-FD Architecture**:
   - In the bonus implementation, a single static array of pointers (`static char *str[OPEN_MAX]`) tracks independent state for every possible file descriptor up to `OPEN_MAX`. This ensures that interleaving reads between different files preserves each file's cursor and unparsed buffer accurately without any cross-talk.
