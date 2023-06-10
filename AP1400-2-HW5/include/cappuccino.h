#ifndef CAPPUCCINO
#define CAPPUCCINO

#include <string>
#include <vector>
#include "espresso_based.h"
#include "ingredient.h"

class Cappuccino : public EspressoBased {
 public:
  Cappuccino();
  Cappuccino(const Cappuccino& cap);
  ~Cappuccino() override;
  auto operator=(const Cappuccino& cap) -> Cappuccino&;

  auto price() -> double override;
  auto brew() -> void override;

  auto add_side_item(Ingredient* side) -> void;
  auto get_side_items() -> std::vector<Ingredient*>&;

 private:
  std::vector<Ingredient*> side_items;
};

#endif  // CAPPUCCINO