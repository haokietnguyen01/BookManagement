#include "User.hpp"
#include "LibrarySystem.hpp"
#include <algorithm>
#include <iostream>

// Constructor to initialize a User object with ID, name, email, and phone.
User::User(const std::string &id, const std::string &name,
           const std::string &email, const std::string &phone)
    : id(id), name(name), email(email), phone(phone) {
  // No need to set 'id' again; it's already initialized via member initializer
  // list.
}

std::string User::getId() const { return id; }
std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }
std::string User::getPhone() const { return phone; }

// Returns a list of borrowed books.
std::vector<std::string> User::getBorrowedBooks() const {
  return borrowedBooks;
}

// Sets the list of borrowed books.
void User::setBorrowedBooks(const std::vector<std::string> &books) {
  borrowedBooks = books;
}

// Displays user details.
void User::display() const {
  std::cout << "User ID: " << id << ", Name: " << name << ", Email: " << email
            << ", Phone: " << phone << std::endl;
}

// Adds a book to the borrowed books list and updates the book's borrow count in
// the library system.
void User::addBorrowedBook(const std::string &bookId,
                           LibrarySystem &librarySystem) {
  borrowedBooks.push_back(bookId);

  // Iterate through library items to find and update the borrowed book's count.
  for (const auto &item : librarySystem.getItems()) {
    if (auto book = std::dynamic_pointer_cast<Book>(item)) {
      if (book->getId() == bookId) {
        book->incrementBorrowCount(); // Increment the borrow count of the book.
        break;
      }
    }
  }

  // Record the borrow date for the book.
  borrowDates[bookId] = std::chrono::system_clock::now();
}

// Removes a book from the borrowed books list and clears its borrow date.
void User::removeBorrowedBook(const std::string &bookId) {
  borrowedBooks.erase(
      std::remove(borrowedBooks.begin(), borrowedBooks.end(), bookId),
      borrowedBooks.end());  // Remove the book ID from borrowedBooks vector.
  borrowDates.erase(bookId); // Remove the borrow date entry.
}

// Retrieves the borrow date of a specific book.
std::chrono::system_clock::time_point
User::getBorrowDate(const std::string &bookId) const {
  auto it = borrowDates.find(bookId);
  if (it != borrowDates.end()) {
    return it->second; // Return the stored borrow date.
  }
  throw std::runtime_error("Book not borrowed by this user");
}

// Sets or updates the borrow date for a specific book.
void User::setBorrowedBookDate(
    const std::string &bookId,
    const std::chrono::system_clock::time_point &date) {
  // Check if the book is in the borrowedBooks list.
  if (std::find(borrowedBooks.begin(), borrowedBooks.end(), bookId) !=
      borrowedBooks.end()) {
    borrowDates[bookId] = date; // Update the borrow date.
  } else {
    throw std::runtime_error("Book not borrowed by this user");
  }
}

// Checks if a specific book is in the borrowed books list.
bool User::hasBorrowedBook(const std::string &bookId) const {
  return std::find(borrowedBooks.begin(), borrowedBooks.end(), bookId) !=
         borrowedBooks.end();
}
