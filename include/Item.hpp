#ifndef ITEM_HPP
#define ITEM_HPP

#include <memory>
#include <string>
#include <vector>

class Item {
public:
  virtual ~Item() = default;
  virtual std::string getId() const = 0;
  virtual void display() const = 0;
};

#endif // ITEM_HPP
