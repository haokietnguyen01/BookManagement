#ifndef USER_HPP
#define USER_HPP

#include "Item.hpp"
#include <chrono>
#include <string>
#include <unordered_map>
#include <vector>

class LibrarySystem; // Forward declaration of LibrarySystem for use in User
                     // class.

// Represents a user in the library system, inheriting from Item.
class User : public Item {
private:
  // Private member variables for storing user attributes and borrowed book
  std::string id;
  std::string name;
  std::string email;
  std::string phone;
  std::vector<std::string> borrowedBooks;
  std::unordered_map<std::string, std::chrono::system_clock::time_point>
      borrowDates;

public:
  // Constructor to initialize a User object with its attributes.
  User(const std::string &id, const std::string &name, const std::string &email,
       const std::string &phone);

  // Overrides from Item class.
  std::string getId() const override;
  void display() const override;

  // Getter and setter methods for user attributes.
  std::string getName() const;
  std::string getEmail() const;
  std::string getPhone() const;
  void setBorrowedBooks(const std::vector<std::string> &borrowedBooks);
  std::vector<std::string> getBorrowedBooks() const;

  // Methods to manage borrowed books.
  void addBorrowedBook(const std::string &bookId, LibrarySystem &librarySystem);
  void removeBorrowedBook(const std::string &bookId);
  std::chrono::system_clock::time_point
  getBorrowDate(const std::string &bookId) const;
  void setBorrowedBookDate(const std::string &bookId,
                           const std::chrono::system_clock::time_point &date);
  bool hasBorrowedBook(const std::string &bookId) const;
};

#endif // USER_HPP
