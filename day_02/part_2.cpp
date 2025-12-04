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

      for (auto m = s.size() / 2; m >= 1; --m) {
        if (s.size() % m != 0) {
          continue;
        }

        auto ref = s.substr(0, m);
        bool isti = true;

        for (std::size_t i = 0; i + m <= s.size(); i += m) {
          if (s.substr(i, m) != ref) {
            isti = false;
            break;
          }
        }

        if (isti) {
          total += a;
          break;
        }
      }
    }
  }

  std::cout << total;
}
