#include "espresso_based.h"

EspressoBased::~EspressoBased() {
  for (const auto& i : ingredients) {
    delete i;
  }
  ingredients.clear();
}

EspressoBased::EspressoBased(const EspressoBased& esp) : EspressoBased(esp.name) {
  for (const auto& i : esp.ingredients) {
    ingredients.push_back(i->clone());
  }
}