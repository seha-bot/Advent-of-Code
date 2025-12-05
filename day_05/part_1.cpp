#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

namespace stdr = std::ranges;

int main() {
  std::ifstream in("input.txt");
  if (!in) {
    std::cerr << "Can't open input.txt\n";
    return EXIT_FAILURE;
  }

  std::vector<std::pair<long, long>> ranges;

  while (true) {
    long a, b;
    in >> a;
    in.ignore();
    in >> b;
    in.ignore();

    ranges.emplace_back(a, b);

    if (in.peek() == '\n') {
      break;
    }
  }

  int cnt = 0;

  while (true) {
    long x;

    if (!(in >> x)) {
      break;
    }

    cnt += stdr::any_of(ranges, [x](auto &r) {
      auto [a, b] = r;
      return a <= x && x <= b;
    });
  }

  std::cout << cnt << '\n';
}
