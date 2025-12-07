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
#include <string>

namespace stdr = std::ranges;

int main() {
  std::ifstream in("input.txt");
  if (!in) {
    std::cerr << "Can't open input.txt\n";
    return EXIT_FAILURE;
  }

  std::vector<std::string> m;

  while (true) {
    std::string row;
    if (!getline(in, row)) {
      break;
    }
    m.push_back(std::move(row));
  }

  int cnt = 0;

  auto it = stdr::find(m[0], 'S');
  m[1][it - m[0].begin()] = '|';

  for (int i = 2; i < m.size() - 1; i += 2) {
    for (int j = 0; j < m[i].size(); j++) {
      switch (m[i][j]) {
        case '.':
          if (m[i - 1][j] == '|') {
            m[i + 1][j] = '|';
          }
          break;
        case '^':
          if (m[i - 1][j] == '|') {
            m[i + 1][j - 1] = '|';
            m[i + 1][j + 1] = '|';
            ++cnt;
          }
          break;
      }
    }
  }

  for (auto& r : m) {
    std::println("{}", r);
  }

  std::cout << cnt << '\n';
}
