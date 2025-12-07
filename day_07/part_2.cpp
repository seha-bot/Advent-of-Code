#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <print>
#include <string>
#include <vector>

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

  std::vector timelines(m.size(), std::vector<std::uint64_t>(m[0].size()));

  std::size_t s = stdr::find(m[0], 'S') - m[0].begin();
  m[1][s] = '|';
  timelines[1][s] = 1;

  for (int i = 2; i < m.size() - 1; i += 2) {
    for (int j = 0; j < m[i].size(); j++) {
      switch (m[i][j]) {
      case '.':
        if (m[i - 1][j] == '|') {
          m[i + 1][j] = '|';
          timelines[i + 1][j] += timelines[i - 1][j];
        }
        break;
      case '^':
        if (m[i - 1][j] == '|') {
          m[i + 1][j - 1] = '|';
          m[i + 1][j + 1] = '|';

          timelines[i + 1][j - 1] += timelines[i - 1][j];
          timelines[i + 1][j + 1] += timelines[i - 1][j];
        }
        break;
      }
    }
  }

  for (auto &r : m) {
    std::println("{}", r);
  }

  auto cnt = *stdr::fold_left_first(timelines.back(), std::plus{});
  std::cout << cnt << '\n';
}
