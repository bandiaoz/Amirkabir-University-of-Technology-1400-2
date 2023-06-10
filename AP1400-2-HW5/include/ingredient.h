#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {
 public:
  double get_price_unit() const { return price_unit; }
  std::size_t get_units() const { return units; }
  std::string get_name() const { return name; }
  virtual double price() = 0;
  virtual ~Ingredient() = default;
  virtual Ingredient* clone() = 0;

 protected:
  Ingredient(double price_unit, size_t units) : price_unit{price_unit}, units{units} {}

  double price_unit;
  std::size_t units;
  std::string name;
};

#endif  // INGREDIENT_H