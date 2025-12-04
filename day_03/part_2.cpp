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
    std::string max(12, '0');
    for (char c : bank) {
      max.push_back(c);
      if (auto it = stdr::adjacent_find(max, stdr::less{}); it != max.end()) {
        max.erase(it);
      } else {
        max.pop_back();
      }
    }

    total += std::stol(max);
  }

  std::cout << total << '\n';
}
