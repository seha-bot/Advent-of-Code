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

  std::size_t offset = 1;
  for (std::size_t i = 0; i + offset < ranges.size();) {
    if (ranges[i].second + 1 >= ranges[i + offset].first) {
      ranges[i].second = std::max(ranges[i].second, ranges[i + offset].second);
      ranges[i + offset] = {1, 0};
      ++offset;
    } else {
      i += offset;
      offset = 1;
    }
  }

  long cnt = 0;
  for (auto [a, b] : ranges) {
    cnt += b - a + 1;
  }
  std::cout << cnt << '\n';
}
