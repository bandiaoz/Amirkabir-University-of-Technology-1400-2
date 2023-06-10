#ifndef MOCHA_H
#define MOCHA_H

#include "espresso_based.h"
class Mocha : public EspressoBased {
 public:
  Mocha();
  Mocha(const Mocha& mocha);
  ~Mocha() override;
  auto operator=(const Mocha& mocha) -> Mocha&;

  auto price() -> double override;
  auto brew() -> void override;

  auto add_side_item(Ingredient* side) -> void;
  auto get_side_items() -> std::vector<Ingredient*>&;

 private:
  std::vector<Ingredient*> side_items;
};

#endif // MOCHA_H