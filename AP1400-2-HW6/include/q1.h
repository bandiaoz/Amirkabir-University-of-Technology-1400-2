#ifndef Q1_H
#define Q1_H

#include <functional>

namespace q1 {

const double EPSILON = 0.0001;
const double DELTA = 0.0001;

inline auto gradient_descent(double init, double step, std::function<double(double)> func) -> double {
  auto derivative = [&func](double x) { return (func(x + DELTA) - func(x)) / DELTA; };

  double next = init;
  double d = derivative(next);
  while (abs(d) > EPSILON) {
    next -= step * d;
    d = derivative(next);
  }
  return next;
}

template <typename T, typename F>
T gradient_descent(double init, double step) {
    return gradient_descent(init, step, F());
}

}  // namespace q1

#endif  // Q1_H