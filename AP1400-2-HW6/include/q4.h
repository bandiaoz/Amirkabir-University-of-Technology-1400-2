#ifndef Q4_H
#define Q4_H

#include <numeric>
#include <vector>

namespace q4 {
struct Vector2D {
  double x{};
  double y{};
};

struct Sensor {
  Vector2D pos;
  double accuracy;
};

inline Vector2D kalman_filter(std::vector<Sensor> sensors) {
  Vector2D ans;
  // double sum_x = 0, sum_y = 0, sum_acc = 0;
  double sum_x = std::accumulate(sensors.begin(), sensors.end(), 0.0,
                                 [](double sum, Sensor sensor) {
                                   return sum + sensor.pos.x * sensor.accuracy;
                                 });
  double sum_y = std::accumulate(sensors.begin(), sensors.end(), 0.0,
                                 [](double sum, Sensor sensor) {
                                   return sum + sensor.pos.y * sensor.accuracy;
                                 });
  double sum_acc = std::accumulate(sensors.begin(), sensors.end(), 0.0,
                                   [](double sum, Sensor sensor) {
                                     return sum + sensor.accuracy;
                                   });
  ans.x = sum_x / sum_acc;
  ans.y = sum_y / sum_acc;
  return ans;
}
}  // namespace q4

#endif  // Q4_H