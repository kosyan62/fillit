[![42](https://img.shields.io/badge/-Project-black?logo=42&logoColor=white)](https://42.fr/)
[![Test](https://github.com/kosyan62/fillit/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/kosyan62/libft/actions/workflows/c-cpp.yml)
![C](https://img.shields.io/badge/Language-%2300599C.svg?logo=c&logoColor=white)

# Fillit

Fillit is a project developed as part of the 42 School curriculum. It focuses on solving a common algorithmic challenge: finding the optimal arrangement of geometric shapes within minimal space. The goal of this project is to arrange a given set of **Tetriminos** (blocks from the game Tetris) into the smallest possible square, using an efficient algorithm that works within reasonable time limits.

This project introduces backtracking and combinatorial optimization problems, emphasizing data structures, algorithm efficiency, and clean code practices.

## Project Overview

- **Language:** C
- **Objective:** Solve an optimization problem by fitting multiple Tetriminos into the smallest square.
- **Focus:** Algorithm design, recursion, backtracking, memory management, and clean C coding (42 Norm).
- [Original task](static/fillit.en.pdf)

## Features

### Input
- Takes exactly **one argument**: a file describing a list of Tetriminos.
- Validates the file format:
  - Tetriminos are represented in 4x4 grids with `#` for blocks and `.` for empty spaces.
  - Validations include format, connectivity of blocks, and correct number of Tetriminos (1 to 26).
  - Displays `error` for invalid inputs.

### Algorithm
- Finds the **smallest square** in which all Tetriminos can fit.
- Uses efficient backtracking techniques to minimize computation time.
- Arranges Tetriminos in **upper-leftmost** positions when multiple solutions exist.

### Output
- Displays the solution as a grid where each Tetrimino is labeled with a unique uppercase letter (A, B, C...).
- If the input is invalid, the program outputs `error` and exits.

### Constraints
- Only allowed C functions: `exit`, `open`, `close`, `write`, `read`, `malloc`, and `free`.
- Must comply with the 42 School coding standards (Norme).
- No memory leaks allowed.
- The executable must be named `fillit`.

## Compilation

```bash
make
```

### Makefile Targets

| Target   | Description                      |
|----------|----------------------------------|
| `all`    | Compile the binary                |
| `clean`  | Remove object files               |
| `fclean` | Remove object files and binary    |
| `re`     | Rebuild the project from scratch  |

## Example

```bash
./fillit sample.fillit
```

Example solution:
```
ABBBB
ACCCB
A.DDB
ADDDB
```

## License

This project is developed for educational purposes as part of the 42 School program.
