#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <print>
#include <vector>

namespace stdr = std::ranges;

int main() {
  std::ifstream in("input.txt");
  if (!in) {
    std::cerr << "Can't open input.txt\n";
    return EXIT_FAILURE;
  }

  std::vector<std::vector<std::uint64_t>> m;
  std::size_t i = 0;
  while (true) {
    if (in.peek() == '+' || in.peek() == '*') {
      break;
    }
    std::uint64_t x;
    in >> x;
    if (m.size() == i) {
      m.emplace_back();
    }
    m[i++].push_back(x);

    while (in.peek() == ' ') {
      in.ignore();
    }
    if (in.peek() == '\n') {
      in.ignore();
      i = 0;
    }
  }

  std::uint64_t res = 0;
  i = 0;

  in.clear();

  while (true) {
    char op;
    if (!(in >> op)) {
      break;
    }

    while (in.peek() == ' ') {
      in.ignore();
    }

    if (op == '*') {
      res += stdr::fold_left(m[i++], std::uint64_t(1), std::multiplies());
    } else if (op == '+') {
      res += stdr::fold_left(m[i++], std::uint64_t(0), std::plus());
    }
  }

  assert(i == m.size());

  std::cout << res << '\n';
}
