#include "LibrarySystem.hpp"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <unordered_map>

// Mutex to ensure thread safety in library operations.
std::mutex libraryMutex;

// Adds an item (book or user) to the library system.
void LibrarySystem::addItem(const std::shared_ptr<Item> &item) {
  items.push_back(item);
}

// Loads items (books or users) from a file into the library system.
void LibrarySystem::loadItemsFromFile(const std::string &filename,
                                      bool isUserFile) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file for reading: " << filename << std::endl;
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    if (isUserFile) {
      // Read user information.
      std::string id, name, email, phone;
      std::getline(iss, id, ',');
      std::getline(iss, name, ',');
      std::getline(iss, email, ',');
      std::getline(iss, phone, ',');

      auto user = std::make_shared<User>(id, name, email, phone);

      // Read borrowed books.
      std::string borrowedBooksStr;
      if (std::getline(iss, borrowedBooksStr, ',')) {
        std::istringstream borrowedBooksStream(borrowedBooksStr);
        std::string bookId;
        while (std::getline(borrowedBooksStream, bookId, ';')) {
          user->addBorrowedBook(bookId, *this); // Adds borrowed book.
        }
      }

      addItem(user);
    } else {
      // Read book information.
      std::string id, title, author, category;
      int year;
      bool available;
      std::getline(iss, id, ',');
      std::getline(iss, title, ',');
      std::getline(iss, author, ',');
      std::getline(iss, category, ',');
      iss >> year;
      iss.ignore();
      iss >> available;

      auto book =
          std::make_shared<Book>(id, title, author, category, year, available);
      addItem(book);
    }
  }
  file.close();
}

// Saves items (books or users) from the library system to a file.
void LibrarySystem::saveItemsToFile(const std::string &filename,
                                    bool isUserFile) const {
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file for writing: " << filename << std::endl;
    return;
  }

  for (const auto &item : items) {
    if (isUserFile && std::dynamic_pointer_cast<User>(item)) {
      auto user = std::dynamic_pointer_cast<User>(item);
      file << user->getId() << "," << user->getName() << "," << user->getEmail()
           << "," << user->getPhone() << ",";

      // Save borrowed books.
      const auto &borrowedBooks = user->getBorrowedBooks();
      for (size_t i = 0; i < borrowedBooks.size(); ++i) {
        file << borrowedBooks[i];
        if (i < borrowedBooks.size() - 1) {
          file << ";"; // Separator between borrowed books.
        }
      }
      file << "\n";
    } else if (!isUserFile && std::dynamic_pointer_cast<Book>(item)) {
      auto book = std::dynamic_pointer_cast<Book>(item);
      file << book->getId() << "," << book->getTitle() << ","
           << book->getAuthor() << "," << book->getCategory() << ","
           << book->getYear() << "," << book->isAvailable() << "\n";
    }
  }
  file.close();
}

// Prints details of library items based on the flag.
void LibrarySystem::printLibraryItems(int flag) const {
  for (const auto &item : items) {
    if (flag == 0) {
      std::shared_ptr<User> user = std::dynamic_pointer_cast<User>(item);
      if (user) {
        // Print user information.
        std::cout << "User ID: " << user->getId()
                  << ", Name: " << user->getName()
                  << ", Email: " << user->getEmail()
                  << ", Phone: " << user->getPhone() << ", Borrowed Books: ";
        for (const auto &bookId : user->getBorrowedBooks()) {
          std::cout << bookId << " ";
        }
        std::cout << "\n";
      }
    } else if (flag == 1) {
      std::shared_ptr<Book> book = std::dynamic_pointer_cast<Book>(item);
      if (book) {
        // Print book information.
        std::cout << "Book ID: " << book->getId()
                  << ", Title: " << book->getTitle()
                  << ", Author: " << book->getAuthor()
                  << ", Category: " << book->getCategory()
                  << ", Year: " << book->getYear()
                  << ", Available: " << (book->isAvailable() ? "Yes" : "No")
                  << "\n";
      }
    }
  }
}

// Handles borrowing a book for a user.
bool LibrarySystem::borrowBook(const std::string &userId,
                               const std::string &bookId) {
  std::lock_guard<std::mutex> lock(libraryMutex);

  auto user = findUserById(userId);
  auto book = findBookById(bookId);

  if (user && book && book->isAvailable()) {
    user->addBorrowedBook(bookId, *this);
    book->setAvailable(false);
    saveItemsToFile("./database/books.txt", false); // Update book file.
    saveItemsToFile("./database/users.txt", true);  // Update user file.
    return true;
  }
  return false;
}

// Handles returning a book from a user.
bool LibrarySystem::returnBook(const std::string &userId,
                               const std::string &bookId) {
  std::lock_guard<std::mutex> lock(libraryMutex);

  auto user = findUserById(userId);
  auto book = findBookById(bookId);

  if (!user || !book) {
    // If user or book not found, return false.
    return false;
  }

  if (!book->isAvailable() && user->hasBorrowedBook(bookId)) {
    user->removeBorrowedBook(bookId);
    book->setAvailable(true);
    saveItemsToFile("./database/books.txt", false); // Update book file.
    saveItemsToFile("./database/users.txt", true);  // Update user file.
    return true;
  }

  // If book was not borrowed or user does not have it, return false.
  return false;
}

// Finds a user by their ID.
std::shared_ptr<User>
LibrarySystem::findUserById(const std::string &userId) const {
  for (const auto &item : items) {
    if (auto user = std::dynamic_pointer_cast<User>(item)) {
      if (user->getId() == userId) {
        return user;
      }
    }
  }
  return nullptr;
}

// Finds a book by its ID.
std::shared_ptr<Book>
LibrarySystem::findBookById(const std::string &bookId) const {
  for (const auto &item : items) {
    if (auto book = std::dynamic_pointer_cast<Book>(item)) {
      if (book->getId() == bookId) {
        return book;
      }
    }
  }
  return nullptr;
}

// Searches for books based on the query and type (title, author, or category).
std::vector<std::shared_ptr<Book>>
LibrarySystem::searchBooks(const std::string &query,
                           const std::string &type) const {
  std::vector<std::shared_ptr<Book>> results;
  for (const auto &item : items) {
    if (auto book = std::dynamic_pointer_cast<Book>(item)) {
      if ((type == "title" &&
           book->getTitle().find(query) != std::string::npos) ||
          (type == "author" &&
           book->getAuthor().find(query) != std::string::npos) ||
          (type == "category" &&
           book->getCategory().find(query) != std::string::npos)) {
        results.push_back(book);
      }
    }
  }
  return results;
}

// Returns the top N most borrowed books.
std::vector<std::shared_ptr<Book>>
LibrarySystem::getMostBorrowedBooks(int topN) const {
  std::unordered_map<std::string, int> borrowCount;
  for (const auto &item : items) {
    if (auto user = std::dynamic_pointer_cast<User>(item)) {
      for (const auto &bookId : user->getBorrowedBooks()) {
        borrowCount[bookId]++;
      }
    }
  }

  std::vector<std::pair<std::string, int>> borrowVec(borrowCount.begin(),
                                                     borrowCount.end());
  std::sort(
      borrowVec.begin(), borrowVec.end(), [](const auto &a, const auto &b) {
        return b.second < a.second; // Sort by borrow count in descending order.
      });

  std::vector<std::shared_ptr<Book>> mostBorrowedBooks;
  for (int i = 0; i < topN && i < borrowVec.size(); ++i) {
    for (const auto &item : items) {
      if (auto book = std::dynamic_pointer_cast<Book>(item)) {
        if (book->getId() == borrowVec[i].first) {
          mostBorrowedBooks.push_back(book);
          break;
        }
      }
    }
  }
  return mostBorrowedBooks;
}

// Returns books that are overdue by a specified number of days.
std::vector<std::shared_ptr<Book>>
LibrarySystem::getOverdueBooks(int days) const {
  std::vector<std::shared_ptr<Book>> overdueBooks;
  auto now = std::chrono::system_clock::now();

  for (const auto &item : items) {
    if (auto user = std::dynamic_pointer_cast<User>(item)) {
      for (const auto &bookId : user->getBorrowedBooks()) {
        try {
          auto borrowDate = user->getBorrowDate(bookId);
          auto duration =
              std::chrono::duration_cast<std::chrono::hours>(now - borrowDate)
                  .count();
          int daysOverdue = duration / 24; // Convert hours to days.
          if (daysOverdue > days) {
            for (const auto &item : items) {
              if (auto book = std::dynamic_pointer_cast<Book>(item)) {
                if (book->getId() == bookId) {
                  overdueBooks.push_back(book);
                  break;
                }
              }
            }
          }
        } catch (const std::runtime_error &) {
          std::cerr << "Error: Book not found in borrow dates." << std::endl;
        }
      }
    }
  }
  return overdueBooks;
}

// Returns all items in the library system.
const std::vector<std::shared_ptr<Item>> &LibrarySystem::getItems() const {
  return items;
}

// Checks if a user has borrowed a specific book.
bool LibrarySystem::hasBorrowedBook(const std::string &userId,
                                    const std::string &bookId) const {
  std::lock_guard<std::mutex> lock(libraryMutex);

  // Find user by userId.
  auto user = findUserById(userId);
  if (!user) {
    // If user not found, return false.
    return false;
  }

  // Check if the book is in the user's borrowed books.
  return user->hasBorrowedBook(bookId);
}
