#include "Book.hpp"
#include "LibrarySystem.hpp"
#include "User.hpp"
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
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
  std::cout << "0. Exit\n";
}

int main() {
  LibrarySystem librarySystem;

  bool running = true;
  while (running) {
    displayMenu();

    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    std::cin.ignore(); // Đọc newline còn lại trong buffer

    switch (choice) {
    case 1: {
      // Thêm sách
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
      std::cin.ignore(); // Đọc newline còn lại trong buffer

      auto book =
          std::make_shared<Book>(id, title, author, category, year, available);
      librarySystem.addItem(book);
      std::cout << "Book added successfully.\n";
      break;
    }
    case 2: {
      // Thêm người dùng
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
      // Mượn sách
      std::string userId, bookId;

      std::cout << "Enter user ID: ";
      std::getline(std::cin, userId);
      std::cout << "Enter book ID: ";
      std::getline(std::cin, bookId);

      if (librarySystem.borrowBook(userId, bookId)) {
        std::cout << "Book borrowed successfully.\n";
      } else {
        std::cout << "Failed to borrow book.\n";
      }
      break;
    }
    case 4: {
      // Trả sách
      std::string userId, bookId;

      std::cout << "Enter user ID: ";
      std::getline(std::cin, userId);
      std::cout << "Enter book ID: ";
      std::getline(std::cin, bookId);

      if (librarySystem.returnBook(userId, bookId)) {
        std::cout << "Book returned successfully.\n";
      } else {
        std::cout << "Failed to return book.\n";
      }
      break;
    }
    case 5: {
      // Tìm kiếm sách
      std::string query, type;

      std::cout << "Enter search query: ";
      std::getline(std::cin, query);
      std::cout << "Enter search type (title, author, category): ";
      std::getline(std::cin, type);

      auto results = librarySystem.searchBooks(query, type);
      std::cout << "Search Results:\n";
      for (const auto &book : results) {
        std::cout << "Book ID: " << book->getId()
                  << ", Title: " << book->getTitle()
                  << ", Author: " << book->getAuthor()
                  << ", Category: " << book->getCategory()
                  << ", Year: " << book->getYear()
                  << ", Available: " << (book->isAvailable() ? "Yes" : "No")
                  << "\n";
      }
      break;
    }
    case 6: {
      // In tất cả sách
      librarySystem.printLibraryItems(1); // 1 = sách
      break;
    }
    case 7: {
      // In tất cả người dùng
      librarySystem.printLibraryItems(0); // 0 = người dùng
      break;
    }
    case 8: {
      // Báo cáo sách mượn nhiều nhất
      int topN;
      std::cout << "Enter the number of top books to list: ";
      std::cin >> topN;
      std::cin.ignore(); // Đọc newline còn lại trong buffer

      auto mostBorrowedBooks = librarySystem.getMostBorrowedBooks(topN);
      std::cout << "Most Borrowed Books:\n";
      for (const auto &book : mostBorrowedBooks) {
        std::cout << "Book ID: " << book->getId()
                  << ", Title: " << book->getTitle()
                  << ", Author: " << book->getAuthor()
                  << ", Borrow Count: " << book->getBorrowCount() << "\n";
      }
      break;
    }
    case 9: {
      // Báo cáo sách quá hạn
      int days;
      std::cout << "Enter the number of days for overdue: ";
      std::cin >> days;
      std::cin.ignore(); // Đọc newline còn lại trong buffer

      auto overdueBooks = librarySystem.getOverdueBooks(days);
      std::cout << "Overdue Books:\n";
      for (const auto &book : overdueBooks) {
        std::cout << "Book ID: " << book->getId()
                  << ", Title: " << book->getTitle()
                  << ", Author: " << book->getAuthor()
                  << ", Borrow Count: " << book->getBorrowCount() << "\n";
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
  }

  return 0;
}
