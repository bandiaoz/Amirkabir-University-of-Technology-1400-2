#ifndef Q3_H
#define Q3_H

#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

namespace q3 {
struct Flight {
  std::string flight_number;
  std::size_t duration;
  std::size_t connections;
  std::size_t connection_times;
  std::size_t price;

  friend auto operator<(const Flight& a, const Flight& b) -> bool {
    // duration + connection_times + 3*price
    int valA = a.duration + a.connection_times + 3 * a.price;
    int valB = b.duration + b.connection_times + 3 * b.price;
    return valA > valB;
  }
};

inline auto gather_flights(std::string file) -> std::priority_queue<Flight> {
  std::priority_queue<Flight> flights;
  auto f = std::ifstream(file);
  std::string line;
  while (std::getline(f, line)) {
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

    std::stringstream ss(line);
    std::string tmp;
    std::string flight_number;
    std::size_t duration;
    std::size_t connections;
    std::size_t connection_times;
    std::size_t price;

    auto to_size_t = [](std::string s) {
      std::size_t ans = 0;
      for (auto c : s) {
        ans *= 10;
        ans += c - '0';
      }
      return ans;
    };

    auto to_time = [](std::string s) {
      std::size_t hours = 0, minutes = 0;
      std::size_t i = 0;
      for (; i < s.size(); ++i) {
        if (s[i] == 'h') break;
        hours *= 10;
        hours += s[i] - '0';
      }
      ++i;
      for (; i < s.size(); ++i) {
        if (s[i] == 'm') break;
        minutes *= 10;
        minutes += s[i] - '0';
      }
      return hours * 60 + minutes;
    };

    auto to_connection_times = [&](std::string s) {
      std::size_t ans = 0;
      for (int i = 0, j; i < s.size(); i = j + 1) {
        j = i;
        while (j < s.size() && s[j] != ',') {
          ++j;
        }
        ans += to_time(s.substr(i, j - i));
      }
      return ans;
    };

    std::getline(ss, tmp, ':');
    std::getline(ss, flight_number, '-');

    std::getline(ss, tmp, ':');
    std::getline(ss, tmp, '-');
    duration = to_time(tmp);

    std::getline(ss, tmp, ':');
    std::getline(ss, tmp, '-');
    connections = to_size_t(tmp);

    std::getline(ss, tmp, ':');
    std::getline(ss, tmp, '-');
    connection_times = to_connection_times(tmp);

    std::getline(ss, tmp, ':');
    ss >> tmp;
    price = to_size_t(tmp);

    Flight flight{flight_number, duration, connections, connection_times, price};
    flights.push(flight);
  }
  return flights;
}


}  // namespace q3

#endif  // Q3_H