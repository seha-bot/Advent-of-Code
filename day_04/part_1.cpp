#include <cstdlib>
#include <fstream>
#include <iostream>
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

  int cnt = 0;
  for (int i = 0; i < paper.size(); i++) {
    for (int j = 0; j < paper[i].size(); j++) {
      if (paper[i][j] == '@') {
        int neighbours = 0;
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
            neighbours += paper[i + x][j + y] == '@';
          }
        }
        if (neighbours < 4) {
          ++cnt;
        }
      }
    }
  }

  std::cout << cnt << '\n';
}
