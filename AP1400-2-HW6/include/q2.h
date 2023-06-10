#ifndef Q2_H
#define Q2_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace q2 {
struct Patient {
  std::string name;
  std::size_t age;
  std::size_t smokes;
  std::size_t area_q;
  std::size_t alkhol;
};

inline auto read_file(std::string filename) -> std::vector<Patient> {
  std::vector<Patient> patients;
  auto f = std::ifstream(filename);
  std::string line;
  std::getline(f, line);
  std::getline(f, line);
  while (std::getline(f, line)) {
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

    std::stringstream ss(line);
    std::string name, surname, age, smokes, area_q, alkhol;
    std::getline(ss, name, ',');
    std::getline(ss, surname, ',');
    std::getline(ss, age, ',');
    std::getline(ss, smokes, ',');
    std::getline(ss, area_q, ',');
    ss >> alkhol;
    
    auto to_size_t = [](std::string s) {
      std::size_t ans = 0;
      for (auto c : s) {
        ans *= 10;
        ans += c - '0';
      }
      return ans;
    };

    patients.push_back(Patient{name + " " + surname, to_size_t(age), to_size_t(smokes), to_size_t(area_q), to_size_t(alkhol)});
  }
  return patients;
}

inline auto sort(std::vector<Patient>& patients) -> void {
  std::sort(patients.begin(), patients.end(), [](const Patient& a, const Patient& b) {
    int valA = 3 * a.age + 5 * a.smokes + 2 * a.area_q + 4 * a.alkhol;
    int valB = 3 * b.age + 5 * b.smokes + 2 * b.area_q + 4 * b.alkhol;
    return valA > valB;
  });
}

}  // namespace q2

#endif  // Q2_H