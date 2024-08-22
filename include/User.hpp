#ifndef USER_HPP
#define USER_HPP

#include "Item.hpp"
#include <string>
#include <vector>

class LibrarySystem;

class User : public Item {
public:
  User(const std::string &id, const std::string &name, const std::string &email,
       const std::string &phone);

  std::string getId() const override;
  void display() const override;

  // Getter và setter cho các thuộc tính
  std::string getName() const;
  std::string getEmail() const;
  std::string getPhone() const;
  void setBorrowedBooks(const std::vector<std::string> &borrowedBooks);
  std::vector<std::string> getBorrowedBooks() const;
  void addBorrowedBook(const std::string &bookId, LibrarySystem &librarySystem);
  void removeBorrowedBook(const std::string &bookId);
  std::chrono::system_clock::time_point
  getBorrowDate(const std::string &bookId) const;
  void setBorrowedBookDate(const std::string &bookId,
                           const std::chrono::system_clock::time_point &date);

private:
  std::string id;
  std::string name;
  std::string email;
  std::string phone;
  std::vector<std::string> borrowedBooks;
  std::unordered_map<std::string, std::chrono::system_clock::time_point>
      borrowDates;
};

#endif // USER_HPP
