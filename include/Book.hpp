#ifndef BOOK_HPP
#define BOOK_HPP

#include "Item.hpp"
#include <string>

// Represents a book in the library system, inheriting from Item.
class Book : public Item {
private:
  std::string id;
  std::string title;
  std::string author;
  std::string category;
  int year;
  bool available;
  int borrowCount;

public:
  // Constructor for initializing a Book object.
  Book(const std::string &id, const std::string &title,
       const std::string &author, const std::string &category, int year,
       bool available);

  // Overrides from Item class.
  std::string getId() const override;
  void display() const override;

  // Getters and setters for book attributes.
  std::string getTitle() const;
  std::string getAuthor() const;
  std::string getCategory() const;
  int getYear() const;
  bool isAvailable() const;
  void setAvailable(bool availability);

  // Manage borrow count.
  void incrementBorrowCount();
  int getBorrowCount() const;
};

#endif // BOOK_HPP
