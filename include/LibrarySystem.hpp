#ifndef LIBRARYSYSTEM_HPP
#define LIBRARYSYSTEM_HPP

#include "Book.hpp"
#include "User.hpp"
#include <memory>
#include <string>
#include <vector>

class LibrarySystem {
public:
  void addItem(const std::shared_ptr<Item> &item);
  void loadItemsFromFile(const std::string &filename, bool isUserFile);
  void saveItemsToFile(const std::string &filename, bool isUserFile) const;
  void printLibraryItems(int flag) const;

  bool borrowBook(const std::string &userId, const std::string &bookId);

  bool returnBook(const std::string &userId, const std::string &bookId);

  std::shared_ptr<User> findUserById(const std::string &userId) const;

  std::shared_ptr<Book> findBookById(const std::string &bookId) const;

  std::vector<std::shared_ptr<Book>> searchBooks(const std::string &query,
                                                 const std::string &type) const;

  std::vector<std::shared_ptr<Book>> getMostBorrowedBooks(int topN) const;
  std::vector<std::shared_ptr<Book>> getOverdueBooks(int days) const;
  const std::vector<std::shared_ptr<Item>> &getItems() const;

  bool hasBorrowedBook(const std::string &userId,
                       const std::string &bookId) const;

private:
  std::vector<std::shared_ptr<Item>> items;
};

#endif // LIBRARYSYSTEM_HPP
