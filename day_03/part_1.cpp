#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

namespace stdr = std::ranges;

int main() {
  std::ifstream in("input.txt");
  if (!in) {
    std::cerr << "Can't open input.txt\n";
    return EXIT_FAILURE;
  }

  long total = 0;

  while (true) {
    std::string bank;
    if (!getline(in, bank)) {
      break;
    }
    std::string max(2, '0');
    for (char c : bank) {
      auto it = stdr::adjacent_find(max, stdr::less{});
      if (it != max.end()) {
        std::copy(it + 1, max.end(), it);
        max.back() = c;
      } else if (c > max.back()) {
        if (max.back() > max[max.size() - 2]) {
          max[max.size() - 2] = max.back();
        }
        max.back() = c;
      }
    }

    total += std::stol(max);
  }

  std::cout << total << '\n';
}
