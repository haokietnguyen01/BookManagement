#ifndef LIBRARYSYSTEM_HPP
#define LIBRARYSYSTEM_HPP

#include "Book.hpp"
#include "User.hpp"
#include <memory>
#include <string>
#include <vector>

// Manages books and users in the library system.
class LibrarySystem {
private:
  // List of all items in the library system (books and users).
  std::vector<std::shared_ptr<Item>> items;

public:
  // Adds an item to the library system.
  void addItem(const std::shared_ptr<Item> &item);

  // Loads items from a file (users or books based on isUserFile).
  void loadItemsFromFile(const std::string &filename, bool isUserFile);

  // Saves items to a file (users or books based on isUserFile).
  void saveItemsToFile(const std::string &filename, bool isUserFile) const;

  // Prints library items with a specified flag for formatting.
  void printLibraryItems(int flag) const;

  // Handles borrowing a book by a user.
  bool borrowBook(const std::string &userId, const std::string &bookId);

  // Handles returning a book by a user.
  bool returnBook(const std::string &userId, const std::string &bookId);

  // Finds a user by their ID.
  std::shared_ptr<User> findUserById(const std::string &userId) const;

  // Finds a book by its ID.
  std::shared_ptr<Book> findBookById(const std::string &bookId) const;

  // Searches for books based on a query and type (title, author, etc.).
  std::vector<std::shared_ptr<Book>> searchBooks(const std::string &query,
                                                 const std::string &type) const;

  // Retrieves the top N most borrowed books.
  std::vector<std::shared_ptr<Book>> getMostBorrowedBooks(int topN) const;

  // Retrieves books that are overdue by a specified number of days.
  std::vector<std::shared_ptr<Book>> getOverdueBooks(int days) const;

  // Returns a constant reference to all items in the system.
  const std::vector<std::shared_ptr<Item>> &getItems() const;

  // Checks if a user has borrowed a specific book.
  bool hasBorrowedBook(const std::string &userId,
                       const std::string &bookId) const;
};

#endif // LIBRARYSYSTEM_HPP
