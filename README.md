# Book Management System

## Introduction

The Book Management System provides features for adding books, adding users, borrowing and returning books, searching for books, and generating reports related to books and users.

## Requirements

- C++17
- g++ (GNU Compiler Collection)
- CMake 3.29.0 or higher

## Project Structure

- `src/main.cpp`: Entry point of the application, where the main menu and user command handling are located.
- `src/Book.cpp`, `src/Book.hpp`: Definitions and implementations for the `Book` class.
- `src/User.cpp`, `src/User.hpp`: Definitions and implementations for the `User` class.
- `src/LibrarySystem.cpp`, `src/LibrarySystem.hpp`: Definitions and implementations for the `LibrarySystem` class to manage books and users.
- `include/Item.hpp`: Abstract base class representing an item with an ID and display functionality, used as a base for different types of items within the library system.
- `include/`: Directory containing header files.
- `database/`: Contains data files for storing book and user information.

## Multithreading

The Book Management System utilizes multithreading to simultaneously handle operations like borrowing and returning books. This method improves application responsiveness by executing tasks concurrently, including:
- `Borrowing Books`: One thread manages the borrowing operation while another thread handles the display of results.
- `Returning Books`: Similarly, one thread processes the return operation, and another manages the result display.

## Data Files

The system uses two data files to store information about books and users:

- **`database/books.txt`**: Stores information about books.
- **`database/users.txt`**: Stores information about users.

## Building and Running

To build and run the application, simply use the provided `build.sh` script:
1. **Run the build script**:
   - Open a terminal and navigate to the directory containing `build.sh`.
   - Execute the following command:
     ```bash
     ./build.sh
     ```

   This script will:
   - Create a build directory.
   - Compile the source code.

2. **Run the application**:
   - After building, you can run the executable by executing on Unix-based systems (Linux, macOS):
        ```bash
        ./build/BookManagement
        ```


