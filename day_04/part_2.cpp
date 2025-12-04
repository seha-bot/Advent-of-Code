#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

int main() {
  std::ifstream in("input.txt");
  if (!in) {
    std::cerr << "Can't open input.txt\n";
    return EXIT_FAILURE;
  }

  std::vector<std::string> paper;
  while (true) {
    std::string row;
    if (!(in >> row)) {
      break;
    }
    paper.push_back(std::move(row));
  }

  auto for_each_neighbour = [&paper](int i, int j, auto &&f) {
    for (int x : {-1, 0, 1}) {
      for (int y : {-1, 0, 1}) {
        if (x == 0 && y == 0) {
          continue;
        }
        if (i + x < 0 || i + x >= paper.size()) {
          continue;
        }
        if (j + y < 0 || j + y >= paper[i].size()) {
          continue;
        }
        if (paper[i + x][j + y] == '@') {
          f(i + x, j + y);
        }
      }
    }
  };

  auto neighbour_count = [&](int i, int j) {
    int neighbours = 0;
    for_each_neighbour(i, j, [&](...) { ++neighbours; });
    return neighbours;
  };

  std::queue<std::pair<int, int>> q;

  for (int i = 0; i < paper.size(); i++) {
    for (int j = 0; j < paper[i].size(); j++) {
      if (paper[i][j] == '@' && neighbour_count(i, j) < 4) {
        q.emplace(i, j);
      }
    }
  }

  int cnt = 0;
  while (!q.empty()) {
    auto [i, j] = q.front();
    q.pop();

    if (paper[i][j] == '.') {
      continue;
    }
    paper[i][j] = '.';
    ++cnt;

    for_each_neighbour(i, j, [&](int x, int y) {
      if (neighbour_count(x, y) < 4) {
        q.emplace(x, y);
      }
    });
  }

  std::cout << cnt << '\n';
}
