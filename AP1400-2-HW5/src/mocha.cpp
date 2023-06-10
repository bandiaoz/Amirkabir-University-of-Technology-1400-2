#include "mocha.h"
#include "sub_ingredients.h"
#include <iostream>

Mocha::Mocha() : EspressoBased("Mocha") {
  ingredients.push_back(new Espresso{2});
  ingredients.push_back(new Milk{2});
  ingredients.push_back(new MilkFoam{1});
  ingredients.push_back(new Chocolate{1});
}

Mocha::Mocha(const Mocha& mocha) : EspressoBased(mocha) {
  for (const auto& i : mocha.side_items) {
    side_items.push_back(i->clone());
  }
}

Mocha::~Mocha() {
  for (const auto& i : side_items) {
    delete i;
  }
  side_items.clear();
}

auto Mocha::operator=(const Mocha& mocha) -> Mocha& {
  if (this == &mocha) {
    return *this;
  }
  for (const auto& i : side_items) {
    delete i;
  }
  side_items.clear();
  for (const auto& i : mocha.side_items) {
    side_items.push_back(i->clone());
  }
  return *this;
}

auto Mocha::price() -> double {
  double price = 0;
  for (const auto& i : ingredients) {
    price += i->price();
  }
  for (const auto& i : side_items) {
    price += i->price();
  }
  return price;
}

auto Mocha::brew() -> void {
  std::cout << "Brewing " << this->name << "..." << std::endl;
  for (const auto& i : ingredients) {
    std::cout << "adding " << i->get_name() << "..." << std::endl;
  }
  for (const auto& i : side_items) {
    std::cout << "adding " << i->get_name() << "..." << std::endl;
  }
}

auto Mocha::add_side_item(Ingredient* side) -> void {
  side_items.push_back(side);
}

auto Mocha::get_side_items() -> std::vector<Ingredient*>& {
  return side_items;
}

