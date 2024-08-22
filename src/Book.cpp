#include "Book.hpp"
#include <iostream>

// Constructor to initialize a Book object with its attributes.
Book::Book(const std::string &id, const std::string &title,
           const std::string &author, const std::string &category, int year,
           bool isAvailable)
    : id(id), title(title), author(author), category(category), year(year),
      available(isAvailable) {
  // Initialization of member variables done through the initializer list.
}

// Getter for the book ID.
std::string Book::getId() const { return id; }

// Getter for the book title.
std::string Book::getTitle() const { return title; }

// Getter for the book author.
std::string Book::getAuthor() const { return author; }

// Getter for the book category.
std::string Book::getCategory() const { return category; }

// Getter for the book publication year.
int Book::getYear() const { return year; }

// Getter for the book availability status.
bool Book::isAvailable() const { return available; }

// Increment the borrow count for the book.
void Book::incrementBorrowCount() { ++borrowCount; }

// Getter for the borrow count of the book.
int Book::getBorrowCount() const { return borrowCount; }

// Display the book's details.
void Book::display() const {
  std::cout << "Book ID: " << id << ", Title: " << title
            << ", Author: " << author << ", Category: " << category
            << ", Year: " << year
            << ", Available: " << (available ? "Yes" : "No") << std::endl;
}

// Setter for updating the availability status of the book.
void Book::setAvailable(bool availability) { available = availability; }
