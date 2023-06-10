#include "cappuccino.h"
#include <iostream>
#include "sub_ingredients.h"

Cappuccino::Cappuccino() : EspressoBased("Cappuccino") { 
  ingredients.push_back(new Espresso{2});
  ingredients.push_back(new Milk{2});
  ingredients.push_back(new MilkFoam{1});
}

Cappuccino::Cappuccino(const Cappuccino& cap) : EspressoBased(cap) {
  for (const auto& i : cap.side_items) {
    side_items.push_back(i->clone());
  }
}

Cappuccino::~Cappuccino() {
  for (const auto& i : side_items) {
    delete i;
  }
  side_items.clear();
}

auto Cappuccino::operator=(const Cappuccino& cap) -> Cappuccino& {
  if (this == &cap) {
    return *this;
  }
  for (const auto& i : side_items) {
    delete i;
  }
  side_items.clear();
  for (const auto& i : cap.side_items) {
    side_items.push_back(i->clone());
  }
  return *this;
}

auto Cappuccino::price() -> double {
  double price = 0;
  for (const auto& i : ingredients) {
    price += i->price();
  }
  for (const auto& i : side_items) {
    price += i->price();
  }
  return price;
}

auto Cappuccino::brew() -> void {
  std::cout << "Brewing " << this->name << "..." << std::endl;
  for (const auto& i : ingredients) {
    std::cout << "adding " << i->get_name() << "..." << std::endl;
  }
  for (const auto& i : side_items) {
    std::cout << "adding " << i->get_name() << "..." << std::endl;
  }
}

auto Cappuccino::add_side_item(Ingredient* side) -> void {
  side_items.push_back(side);
}

auto Cappuccino::get_side_items() -> std::vector<Ingredient*>& {
  return side_items;
}