# C++ SQL-like Data Structure Program

This C++ program implements a SQL-like data structure for managing tables and executing SQL commands. It utilizes various self-implemented data structures and algorithms, including binary files handling, SQL parsing, Bplus Tree, mapping, multi-mapping, tokenization, and state machine algorithms. The provided `basic_test.cpp` file tests the functionality of the program with a set of predefined SQL commands.

Link to the demonstration of the program : https://www.youtube.com/watch?v=Kzt5-230PEI

## Table of Contents

- [Overview](#overview)
- [Files and Directory Structure](#files-and-directory-structure)
- [Features](#features)
- [How to Run](#how-to-run)
- [Testing](#testing)
- [Dependencies](#dependencies)
- [Development Environment](#development-environment)
- [Credits](#credits)

## Overview

The program implements a SQL-like environment where users can create tables, insert data into tables, and perform select queries. It includes features such as creating tables with specified fields, inserting values into tables, and executing select queries with various conditions. The `basic_test.cpp` file demonstrates the functionality of the SQL commands supported by the program.

## Files and Directory Structure

The program's directory structure includes various modules and utility files:

- `binary_files`: Handling binary files with classes like `file_record` and utility functions.
- `bplustree`: Implementation of Bplus Tree algorithms and related classes.
- `linked_list_functions`: Functions for linked list manipulation.
- `node`: Classes related to nodes in data structures.
- `parser`: Parsing SQL commands and related functions.
- `queue`: Implementation of queues and related classes.
- `shunting_yard`: Shunting Yard algorithm implementation.
- `sql`: Main SQL-like data structure and command execution classes.
- `stack`: Implementation of stacks and related classes.
- `stl_utils`: Utility functions for STL containers.
- `table`: Table-related classes and definitions.
- `token`: Tokenization classes and functions.
- `tokenizer`: Tokenizer classes and state machine algorithms.

## Features

- **SQL-like Commands:** Support for SQL-like commands such as creating tables, inserting values, and executing select queries.
- **Table Management:** Create and manage tables with specified fields and data types.
- **Data Insertion:** Insert values into tables with specified columns.
- **Select Queries:** Execute select queries with various conditions and retrieve data from tables.
- **Tokenization:** Tokenize SQL commands for parsing and execution.
- **File Handling:** Read and write data to binary files using custom file handling classes.

## How to Run

1. Clone or download the entire program repository to your local machine.
2. Navigate to the root directory of the program in your terminal or command prompt.
3. Compile the program using a C++ compiler (e.g., GCC or Clang) with appropriate flags and include directories.
4. Execute the compiled binary to run the program.

## Testing

The program includes unit tests using the Google Test framework. To run the tests, compile the program with the test files and execute the compiled binary.

## Dependencies

The program depends on the following libraries and tools:

- C++ Standard Library
- Google Test (for unit testing)
- Compiler with C++11 support (e.g., GCC, Clang)

## Development Environment

The program can be developed and tested in any C++ development environment or IDE. Make sure to configure the include paths and link the necessary libraries for successful compilation.

## Credits

This SQL-like data structure program was developed by [Myat-Thiha]. Credits to Google Test for testing support.

---

