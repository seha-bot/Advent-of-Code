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
#include <numeric>

namespace stdr = std::ranges;

int main() {
  std::ifstream in("input.txt");
  if (!in) {
    std::cerr << "Can't open input.txt\n";
    return EXIT_FAILURE;
  }

  std::vector<std::uint64_t> cols;
  std::uint64_t res = 0;

  while (true) {
    std::string row;
    getline(in, row);

    if (row[0] == '+' || row[0] == '*') {
      std::uint64_t m = 0;
      char op;
      for (std::size_t i = 0; i < cols.size(); i++) {
        if (row[i] == '+') {
          res += m;
          op = '+';
          m = 0;
        } else if (row[i] == '*') {
          res += m;
          op = '*';
          m = 1;
        }

        if (cols[i] == 0) {
          continue;
        }

        if (op == '+') {
          m += cols[i];
        } else {
          m *= cols[i];
        }
      }
      res += m;
      break;
    }

    std::size_t i = 0;
    for (char c : row) {
      if (i == cols.size()) {
        cols.push_back(0);
      }
      if (c == ' ') {
        ++i;
        continue;
      }

      cols[i] *= 10;
      cols[i] += c - '0';

      ++i;
    }
  }

  // std::println("{}", cols);

  std::cout << res << '\n';
}
