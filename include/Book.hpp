#ifndef BOOK_HPP
#define BOOK_HPP

#include "Item.hpp"
#include <string>

class Book : public Item {
public:
  Book(const std::string &id, const std::string &title,
       const std::string &author, const std::string &category, int year,
       bool available);

  std::string getId() const override;
  void display() const override;

  // Getter và setter cho các thuộc tính
  std::string getTitle() const;
  std::string getAuthor() const;
  std::string getCategory() const;
  int getYear() const;
  bool isAvailable() const;
  void setAvailable(bool availability);
  void incrementBorrowCount();
  int getBorrowCount() const;

private:
  std::string id;
  std::string title;
  std::string author;
  std::string category;
  int year;
  bool available;
  int borrowCount;
};

#endif // BOOK_HPP
