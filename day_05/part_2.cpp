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

  stdr::sort(ranges);

  long cnt = 0, prev_max = 0;
  for (auto &[a, b] : ranges) {
    if (prev_max >= a) {
      long new_max = std::max(prev_max, b);
      cnt += new_max - prev_max;
      prev_max = new_max;
    } else {
      cnt += b - a + 1;
      prev_max = b;
    }
  }

  std::cout << cnt << '\n';
}
