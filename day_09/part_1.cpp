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

int main() {
  std::ifstream in("input.txt");
  if (!in) {
    std::cerr << "Can't open input.txt\n";
    return EXIT_FAILURE;
  }

  std::vector<std::pair<long, long>> tiles;

  while (true) {
    long x, y;
    in >> x;
    in.ignore();
    in >> y;
    if (!in) {
      break;
    }
    tiles.emplace_back(x, y);
  }

  long max_area = 0;
  for (std::size_t i = 0; i < tiles.size(); i++) {
    for (std::size_t j = i + 1; j < tiles.size(); j++) {
      auto [x1, y1] = tiles[i];
      auto [x2, y2] = tiles[j];
      max_area = std::max(max_area, (std::abs(x2 - x1) + 1) * (std::abs(y2 - y1) + 1));
    }
  }
  std::cout << max_area << '\n';
}
