#include "Book.hpp"
#include <iostream>
Book::Book(const std::string &id, const std::string &title,
           const std::string &author, const std::string &category, int year,
           bool isAvailable)
    : id(id), title(title), author(author), category(category), year(year),
      available(isAvailable) {
  this->id = id;
  this->title = title;
}

std::string Book::getId() const { return id; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
std::string Book::getCategory() const { return category; }
int Book::getYear() const { return year; }
bool Book::isAvailable() const { return available; }
void Book::incrementBorrowCount() { ++borrowCount; } // Tăng số lần mượn
int Book::getBorrowCount() const { return borrowCount; } // Lấy số lần mượn

void Book::display() const {
  std::cout << "Book ID: " << id << ", Title: " << title
            << ", Author: " << author << ", Category: " << category
            << ", Year: " << year
            << ", Available: " << (available ? "Yes" : "No") << std::endl;
}

void Book::setAvailable(bool availability) { available = availability; }