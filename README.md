# Struct Array Sorting in C

A command-line C project for working with arrays of structures: reading data from the keyboard, text files and binary files, sorting it with different algorithms, and benchmarking the sorts.

Developed as a university lab assignment on arrays of structures and sorting methods. The original assignment files are not included in this repository, so the task is described below.

## Assignment

The project consists of two programs:

1. **Program 1** reads an array of records, sorts it and outputs the result.
2. **Program 2** measures how long sorting takes on randomly generated arrays.

Both programs support three sorting algorithms: **shaker sort**, **heap sort** (both implemented from scratch) and the standard library function **`qsort()`**.

### Data model

Each record describes a **detail** (part):

| Field  | Type                          |
|--------|-------------------------------|
| `id`   | string, up to 8 characters    |
| `name` | string of arbitrary length    |
| `n`    | quantity, natural number      |

### Requirements
- Command-line arguments parsed with `getopt()`
- Input and output via stdin/stdout, text files and binary files
- Custom storage formats for text and binary files
- Text files handled with `fopen`, `fclose`, `fprintf`, `fscanf`; binary files with `fopen`, `fclose`, `fread`, `fwrite`
- Validation of user input and file contents: invalid records are skipped
- Logically complete parts of the algorithm are separate functions; no global variables
- Source code split into several files

## Features

### Program 1: input, sorting, output
- **Input** from the keyboard, a `.txt` file, or a `.bin` file
- **Output** to the screen, a `.txt` file, or a `.bin` file
- **Sorting** with a choice of algorithm, sort field and direction
- Input validation: `id` longer than 8 characters and non-positive quantities are rejected on keyboard input; invalid records are skipped when reading files

### Program 2: sort timing
- Generates random arrays (random `id`, `name` of 1-50 characters, random `n`)
- Sorts each array with the chosen algorithm, field and direction
- Prints the **average sorting time per array, in seconds**, measured with `clock()`

## Project structure

| File               | Purpose                                                              |
|--------------------|----------------------------------------------------------------------|
| `detail.h`         | `Detail` structure definition                                        |
| `file.c`, `file.h` | Keyboard, text and binary input/output, record cleanup               |
| `sort.c`, `sort.h` | Comparators, shaker sort, heap sort, `qsort()` dispatch, array generation and timing |
| `main.c`           | Program 1 entry point (read, sort, write)                            |
| `time.c`           | Program 2 entry point (sort timing)                                  |

## Build

```bash
gcc main.c file.c sort.c -o prog1
gcc time.c file.c sort.c -o prog2
```

## Usage

### Program 1

```bash
./prog1 -i <source> -o <destination> [-s <algorithm>] [-f <field>] [-d]
```

| Option | Description |
|--------|-------------|
| `-i`   | Input source: `keyboard`, or a file name ending in `.txt` or `.bin` |
| `-o`   | Output destination: `screen`, or a file name ending in `.txt` or `.bin` |
| `-s`   | Sorting algorithm: `shacer` (shaker sort), `heap`, or `qsort` |
| `-f`   | Field to sort by: `id`, `name`, or `n` (quantity) |
| `-d`   | Sort in descending order (ascending by default) |
| `-h`   | Help |

Defaults: shaker sort, by `id`, ascending. Note that the shaker sort value is spelled `shacer` in the code.

Examples:

```bash
# Enter records from the keyboard, sort by name with heap sort, print to screen
./prog1 -i keyboard -s heap -f name -o screen

# Read a text file, sort by quantity in descending order with qsort, save as binary
./prog1 -i data.txt -s qsort -f n -d -o sorted.bin
```

### Program 2

```bash
./prog2 -e <elements> -n <arrays> [-s <algorithm>] [-f <field>] [-d]
```

| Option | Description |
|--------|-------------|
| `-e`   | Number of elements in each generated array |
| `-n`   | Number of arrays to generate |
| `-s`, `-f`, `-d` | Same as in Program 1 |
| `-h`   | Help |

Example:

```bash
./prog2 -s heap -f id -e 10000 -n 10
```

## File formats

**Text (`.txt`):** the first line holds the number of records, followed by three lines per record: `id`, `name`, `n`.

```
2
A1000001
Hex bolt M8
150
B2000002
Steel washer
900
```

**Binary (`.bin`):**

| Part              | Size             | Content                                  |
|-------------------|------------------|------------------------------------------|
| Signature         | 4 bytes          | `.CAT`                                   |
| Record count      | 8 bytes          | unsigned integer                         |
| Each record       | variable         | `id` bytes + `\n`, `name` bytes + `\n`, `n` as a 4-byte integer |

## License

MIT
