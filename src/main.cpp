#include "Book.hpp"
#include "LibrarySystem.hpp"
#include "User.hpp"
#include <chrono>
#include <cstdlib> // For system("clear") or system("cls")
#include <iomanip> // For std::setw
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

void displayMenu() {
  std::cout << "Library System Menu:\n";
  std::cout << "1. Add Book\n";
  std::cout << "2. Add User\n";
  std::cout << "3. Borrow Book\n";
  std::cout << "4. Return Book\n";
  std::cout << "5. Search Books\n";
  std::cout << "6. Print All Books\n";
  std::cout << "7. Print All Users\n";
  std::cout << "8. Get Most Borrowed Books\n";
  std::cout << "9. Get Overdue Books\n";
  std::cout << "10. Test Set Borrowed Book Date\n";
  std::cout << "0. Exit\n";
}

void clearScreen() {
#ifdef _WIN32
  std::system("cls"); // Windows
#else
  std::system("clear"); // Unix-based (Linux, macOS)
#endif
}

int main() {
  LibrarySystem librarySystem;

  // Load existing items from files
  librarySystem.loadItemsFromFile("./database/books.txt", false);
  librarySystem.loadItemsFromFile("./database/users.txt", true);

  bool running = true;
  while (running) {
    clearScreen();
    displayMenu();

    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    std::cin.ignore(); // Clear newline from buffer

    switch (choice) {
    case 1: {
      // Add book
      std::string id, title, author, category;
      int year;
      bool available;

      std::cout << "Enter book ID: ";
      std::getline(std::cin, id);
      std::cout << "Enter book title: ";
      std::getline(std::cin, title);
      std::cout << "Enter book author: ";
      std::getline(std::cin, author);
      std::cout << "Enter book category: ";
      std::getline(std::cin, category);
      std::cout << "Enter book year: ";
      std::cin >> year;
      std::cout << "Is the book available (1 for yes, 0 for no): ";
      std::cin >> available;
      std::cin.ignore(); // Clear newline from buffer

      auto book =
          std::make_shared<Book>(id, title, author, category, year, available);
      librarySystem.addItem(book);
      std::cout << "Book added successfully.\n";
      break;
    }
    case 2: {
      // Add user
      std::string id, name, email, phone;

      std::cout << "Enter user ID: ";
      std::getline(std::cin, id);
      std::cout << "Enter user name: ";
      std::getline(std::cin, name);
      std::cout << "Enter user email: ";
      std::getline(std::cin, email);
      std::cout << "Enter user phone: ";
      std::getline(std::cin, phone);

      auto user = std::make_shared<User>(id, name, email, phone);
      librarySystem.addItem(user);
      std::cout << "User added successfully.\n";
      break;
    }
    case 3: {
      // Borrow book
      std::string userId, bookId;

      std::cout << "Enter user ID: ";
      std::getline(std::cin, userId);
      std::cout << "Enter book ID: ";
      std::getline(std::cin, bookId);

      bool success = false;
      std::shared_ptr<Book> borrowedBook;

      std::thread borrowThread(
          [&librarySystem, userId, bookId, &success, &borrowedBook]() {
            success = librarySystem.borrowBook(userId, bookId);
            if (success) {
              borrowedBook = librarySystem.findBookById(bookId);
            }
          });

      borrowThread.join();

      std::thread printThread([success, borrowedBook, bookId]() {
        if (success) {
          std::cout << "Book borrowed successfully.\n";
          if (borrowedBook) {
            std::cout << "Details of the borrowed book:\n";
            std::cout << "Book ID: " << std::setw(10) << borrowedBook->getId()
                      << ", Title: " << std::setw(20)
                      << borrowedBook->getTitle()
                      << ", Author: " << std::setw(20)
                      << borrowedBook->getAuthor()
                      << ", Category: " << std::setw(15)
                      << borrowedBook->getCategory()
                      << ", Year: " << std::setw(4) << borrowedBook->getYear()
                      << ", Available: "
                      << (borrowedBook->isAvailable() ? "Yes" : "No") << "\n";
          } else {
            std::cout << "Book with ID " << bookId << " not found.\n";
          }
        } else {
          std::cout << "Failed to borrow book.\n";
        }
      });

      printThread.join();

      break;
    }

    case 4: {
      // Return book
      std::string userId, bookId;

      std::cout << "Enter user ID: ";
      std::getline(std::cin, userId);
      std::cout << "Enter book ID: ";
      std::getline(std::cin, bookId);

      bool success = false;
      std::shared_ptr<Book> returnedBook;

      std::thread returnThread(
          [&librarySystem, userId, bookId, &success, &returnedBook]() {
            success = librarySystem.returnBook(userId, bookId);
            if (success) {
              returnedBook = librarySystem.findBookById(bookId);
            }
          });

      returnThread.join();

      std::thread printThread([success, returnedBook, bookId]() {
        if (success) {
          std::cout << "Book returned successfully.\n";
          if (returnedBook) {
            std::cout << "Details of the returned book:\n";
            std::cout << "Book ID: " << std::setw(10) << returnedBook->getId()
                      << ", Title: " << std::setw(20)
                      << returnedBook->getTitle()
                      << ", Author: " << std::setw(20)
                      << returnedBook->getAuthor()
                      << ", Category: " << std::setw(15)
                      << returnedBook->getCategory()
                      << ", Year: " << std::setw(4) << returnedBook->getYear()
                      << ", Available: "
                      << (returnedBook->isAvailable() ? "Yes" : "No") << "\n";
          } else {
            std::cout << "Book with ID " << bookId << " not found.\n";
          }
        } else {
          std::cout << "Failed to return book.\n";
        }
      });

      printThread.join();

      break;
    }
    case 5: {
      std::string query, type;

      std::cout << "Enter search query: ";
      std::getline(std::cin, query);
      std::cout << "Enter search type (title, author, category): ";
      std::getline(std::cin, type);

      auto results = librarySystem.searchBooks(query, type);
      std::cout << "Search Results:\n";
      for (const auto &book : results) {
        std::cout << "Book ID: " << std::setw(10) << book->getId()
                  << ", Title: " << std::setw(20) << book->getTitle()
                  << ", Author: " << std::setw(20) << book->getAuthor()
                  << ", Category: " << std::setw(15) << book->getCategory()
                  << ", Year: " << std::setw(4) << book->getYear()
                  << ", Available: " << (book->isAvailable() ? "Yes" : "No")
                  << "\n";
      }
      break;
    }
    case 6: {
      // Print all books
      librarySystem.printLibraryItems(1); // 1 = books
      break;
    }
    case 7: {
      // Print all users
      librarySystem.printLibraryItems(0); // 0 = users
      break;
    }
    case 8: {
      // Get most borrowed books
      int topN;
      std::cout << "Enter the number of top books to list: ";
      std::cin >> topN;
      std::cin.ignore(); // Clear newline from buffer

      auto mostBorrowedBooks = librarySystem.getMostBorrowedBooks(topN);
      std::cout << "Most Borrowed Books:\n";
      for (const auto &book : mostBorrowedBooks) {
        std::cout << "Book ID: " << std::setw(10) << book->getId()
                  << ", Title: " << std::setw(20) << book->getTitle()
                  << ", Author: " << std::setw(20) << book->getAuthor()
                  << ", Borrow Count: " << std::setw(4)
                  << book->getBorrowCount() << "\n";
      }
      break;
    }
    case 9: {
      // Get overdue books
      int days;
      std::cout << "Enter the number of days for overdue: ";
      std::cin >> days;
      std::cin.ignore(); // Clear newline from buffer

      auto overdueBooks = librarySystem.getOverdueBooks(days);
      std::cout << "Overdue Books:\n";
      for (const auto &book : overdueBooks) {
        std::cout << "Book ID: " << std::setw(10) << book->getId()
                  << ", Title: " << std::setw(20) << book->getTitle()
                  << ", Author: " << std::setw(20) << book->getAuthor()
                  << ", Borrow Count: " << std::setw(4)
                  << book->getBorrowCount() << "\n";
      }
      break;
    }
    case 10: {
      // Test setBorrowedBookDate for a specific user
      std::string userId, bookId;
      std::cout << "Enter user ID: ";
      std::getline(std::cin, userId);
      std::cout << "Enter book ID to set borrowed date: ";
      std::getline(std::cin, bookId);

      // Find the user by ID from the list of items
      auto items = librarySystem.getItems();
      auto userIt = std::find_if(items.begin(), items.end(),
                                 [&userId](const std::shared_ptr<Item> &item) {
                                   auto userPtr =
                                       std::dynamic_pointer_cast<User>(item);
                                   return userPtr && userPtr->getId() == userId;
                                 });

      if (userIt != items.end()) {
        auto user = std::dynamic_pointer_cast<User>(*userIt);
        // Set the current time as the borrowed date
        auto now = std::chrono::system_clock::now();
        user->setBorrowedBookDate(bookId, now);
        std::cout << "Borrowed date set for book ID " << bookId << " by user "
                  << userId << ".\n";
      } else {
        std::cout << "User with ID " << userId << " not found.\n";
      }
      break;
    }

    case 0:
      running = false;
      std::cout << "Exiting...\n";
      break;
    default:
      std::cout << "Invalid choice. Please try again.\n";
      break;
    }

    std::cout << "\nPress Enter to continue...";
    std::cin.get(); // Wait for user input before clearing screen
  }

  // Save items to files before exiting
  librarySystem.saveItemsToFile("./database/books.txt", false);
  librarySystem.saveItemsToFile("./database/users.txt", true);

  return 0;
}
