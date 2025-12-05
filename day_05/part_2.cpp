#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

int main() {
  std::ifstream in("input.txt");
  if (!in) {
    std::cerr << "Can't open input.txt\n";
    return EXIT_FAILURE;
  }

  std::vector<std::pair<long, long>> ranges;

  do {
    long a, b;
    in >> a;
    in.ignore();
    in >> b;
    in.ignore();

    ranges.emplace_back(a, b);
  } while (in.peek() != '\n');

  std::ranges::sort(ranges);

  long cnt = 0, prev_b = 0;
  for (auto &[a, b] : ranges) {
    long new_b = std::max(prev_b, b);
    cnt += new_b - std::max(prev_b, a - 1);
    prev_b = new_b;
  }

  std::cout << cnt << '\n';
}
