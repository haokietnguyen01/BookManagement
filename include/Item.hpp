#ifndef ITEM_HPP
#define ITEM_HPP

#include <memory>
#include <string>
#include <vector>

// Abstract base class representing an item with an ID and display
// functionality.
class Item {
public:
  virtual ~Item() =
      default; // Virtual destructor for proper cleanup of derived classes.

  // Pure virtual function to get the item's ID.
  virtual std::string getId() const = 0;

  // Pure virtual function to display item details.
  virtual void display() const = 0;
};

#endif // ITEM_HPP
