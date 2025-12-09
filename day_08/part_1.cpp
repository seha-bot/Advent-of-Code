#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <unordered_set>
#include <vector>

namespace stdr = std::ranges;

struct Vec3 {
  std::uint64_t x, y, z;

  std::uint64_t dist_sq(Vec3 const &v) const {
    Vec3 d{x - v.x, y - v.y, z - v.z};
    return d.x * d.x + d.y * d.y + d.z * d.z;
  }
};

int main() {
  std::ifstream in("input.txt");
  if (!in) {
    std::cerr << "Can't open input.txt\n";
    return EXIT_FAILURE;
  }

  std::vector<Vec3> boxes;

  while (true) {
    Vec3 v;
    in >> v.x;
    in.ignore();
    in >> v.y;
    in.ignore();
    in >> v.z;
    if (!in) {
      break;
    }
    boxes.push_back(v);
  }

  std::vector<std::tuple<std::uint64_t, std::size_t, std::size_t>> distances;
  for (std::size_t i = 0; i < boxes.size(); i++) {
    for (std::size_t j = i + 1; j < boxes.size(); j++) {
      distances.emplace_back(boxes[i].dist_sq(boxes[j]), i, j);
    }
  }
  stdr::partial_sort(distances, distances.begin() + 1000);
  distances.resize(1000);

  std::vector<std::unordered_set<std::size_t>> conns(boxes.size());
  for (auto [_, i, j] : distances) {
    conns[i].insert(j);
    conns[j].insert(i);
  }

  std::vector<bool> visited(boxes.size());
  std::vector<std::unordered_set<std::size_t>> circuits;

  auto discover_circuit = [&](this auto &&self, std::size_t i, std::size_t id) {
    if (visited[i]) {
      return false;
    }
    visited[i] = true;
    circuits[id].insert(i);

    for (std::size_t child : conns[i]) {
      self(child, id);
    }
    return true;
  };

  circuits.emplace_back();
  for (std::size_t i = 0; i < boxes.size(); i++) {
    if (discover_circuit(i, circuits.size() - 1)) {
      circuits.emplace_back();
    }
  }
  circuits.pop_back();

  stdr::partial_sort(circuits, circuits.begin() + 3, stdr::greater(),
                     [](auto &c) { return c.size(); });
  std::cout << circuits[0].size() * circuits[1].size() * circuits[2].size()
            << '\n';
}
