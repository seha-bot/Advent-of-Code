#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ranges>
#include <unordered_map>
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

struct UnionFind {
  UnionFind(std::size_t node_count) {
    islands.reserve(node_count);
    for (auto i : std::views::iota(0uz, node_count)) {
      islands.insert({i, std::unordered_set{i}});
    }
  }

  std::size_t get_island(std::size_t i) {
    for (auto [k, v] : islands) {
      if (v.contains(i)) {
        return k;
      }
    }
    std::unreachable();
  }

  // can either:
  // --island_count; [i] != [j]
  //   island_count; [i] == [j]
  void join(std::size_t i, std::size_t j) {
    auto i_i = get_island(i);
    auto i_j = get_island(j);
    if (i_i != i_j) {
      islands[i_i].insert_range(islands[i_j]);
      islands.erase(i_j);
    }
  }

  std::size_t island_count() const { return islands.size(); }

  std::unordered_map<std::size_t, std::unordered_set<std::size_t>> islands;
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
  stdr::sort(distances);

  UnionFind uf(boxes.size());
  for (auto [_, i, j] : distances) {
    uf.join(i, j);
    if (uf.island_count() == 1) {
      std::cout << boxes[i].x * boxes[j].x << '\n';
      break;
    }
  }
}
