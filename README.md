# Struct Array Sorting in C

A command-line C project for working with arrays of structures: reading data from the keyboard, text files and binary files, sorting it with different algorithms, and benchmarking the sorts.

Developed as a university lab assignment on arrays of structures and sorting methods. The original assignment files are not included in this repository, so the task is described below.

## Assignment

The project consists of two programs:

1. **Program 1**: reads an array of records, sorts it and outputs the result.
2. **Program 2**: measures how long sorting takes on generated arrays.

Both programs support three sorting algorithms: **shaker sort**, **heap sort**, and the standard library function **`qsort()`**.

### Data model

Each record describes a **detail** (part):

| Field      | Type                         |
|------------|------------------------------|
| `id`       | string, 8 characters         |
| `name`     | string of arbitrary length   |
| `quantity` | natural number               |

### Requirements
- Command-line arguments parsed with `getopt()`
- Input and output via stdin/stdout, text files and binary files
- Custom storage formats for text and binary files
- Text files handled with `fopen`, `fclose`, `fprintf`, `fscanf`; binary files with `fopen`, `fclose`, `fread`, `fwrite`
- Validation of user input and file contents: errors are reported and the program continues, skipping invalid records
- Logically complete parts of the algorithm are separate functions; no global variables
- Source code split into several files
- No memory leaks (checked with `valgrind`)

## Features

### Program 1: input, sorting, output
- **Input** from stdin, a text file, or a binary file
- **Output** to stdout, a text file, or a binary file
- **Sorting** with a choice of:
  - algorithm: shaker sort, heap sort, or `qsort()`
  - field to sort by
  - direction: ascending or descending

### Program 2: sort timing
- Benchmarks the chosen algorithm, sort field and direction
- Configurable number of elements per array and number of generated arrays

## Project structure

| File                   | Purpose                              |
|------------------------|--------------------------------------|
| `detail.h`             | Structure definition                 |
| `file.c`, `file.h`     | [File input/output]                  |
| `sort.c`, `sort.h`     | [Sorting algorithms]                 |
| `main.c`               | [Program 1 entry point]              |
| `time.c`               | [Program 2: sort timing]             |

## Build

```bash
[gcc command for program 1]
[gcc command for program 2]
```

## Usage

```bash
[example run of program 1]
[example run of program 2]
```

### Options

| Option | Description |
|--------|-------------|
| [-x]   | [...]       |

## File formats

**Text:** [describe]

**Binary:** [describe]

## License

MIT
