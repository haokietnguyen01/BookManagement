cmake_minimum_required(VERSION 3.29.0)

project(BookManagement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(BookManagement
    src/main.cpp
    src/LibrarySystem.cpp
    src/Book.cpp
    src/User.cpp
)