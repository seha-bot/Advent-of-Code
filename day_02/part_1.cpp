#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::ifstream in("input.txt");
  if (!in) {
    std::cerr << "Can't open input.txt\n";
    return EXIT_FAILURE;
  }

  std::uint64_t total = 0;

  while (true) {
    std::uint64_t a, b;
    in >> a;
    in.ignore();
    in >> b;
    if (!in) {
      break;
    }
    in.ignore();

    for (; a <= b; ++a) {
      auto s = std::to_string(a);
      if (s.size() % 2 != 0) {
        continue;
      }
      auto m = s.size() / 2;
      bool isti = std::equal(s.begin(), s.begin() + m, s.begin() + m);
      if (isti) {
        total += a;
      }
    }
  }

  std::cout << total;
}
