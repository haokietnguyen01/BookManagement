#include "User.hpp"
#include "LibrarySystem.hpp"
#include <iostream>

User::User(const std::string &id, const std::string &name,
           const std::string &email, const std::string &phone)
    : id(id), name(name), email(email), phone(phone) {
  this->id = id;
}

std::string User::getId() const { return id; }
std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }
std::string User::getPhone() const { return phone; }

std::vector<std::string> User::getBorrowedBooks() const {
  return borrowedBooks;
}

void User::setBorrowedBooks(const std::vector<std::string> &books) {
  borrowedBooks = books;
}

void User::display() const {
  std::cout << "User ID: " << id << ", Name: " << name << ", Email: " << email
            << ", Phone: " << phone << std::endl;
}

void User::addBorrowedBook(const std::string &bookId,
                           LibrarySystem &librarySystem) {
  borrowedBooks.push_back(bookId);
  for (const auto &item : librarySystem.getItems()) {
    if (auto book = std::dynamic_pointer_cast<Book>(item)) {
      if (book->getId() == bookId) {
        book->incrementBorrowCount();
        break;
      }
    }
  }
  borrowDates[bookId] = std::chrono::system_clock::now();
}

void User::removeBorrowedBook(const std::string &bookId) {
  borrowedBooks.erase(
      std::remove(borrowedBooks.begin(), borrowedBooks.end(), bookId),
      borrowedBooks.end());
  borrowDates.erase(bookId);
}

std::chrono::system_clock::time_point
User::getBorrowDate(const std::string &bookId) const {
  auto it = borrowDates.find(bookId);
  if (it != borrowDates.end()) {
    return it->second;
  }
  throw std::runtime_error("Book not borrowed by this user");
}

void User::setBorrowedBookDate(
    const std::string &bookId,
    const std::chrono::system_clock::time_point &date) {
  if (std::find(borrowedBooks.begin(), borrowedBooks.end(), bookId) !=
      borrowedBooks.end()) {
    borrowDates[bookId] = date;
  } else {
    throw std::runtime_error("Book not borrowed by this user");
  }
}