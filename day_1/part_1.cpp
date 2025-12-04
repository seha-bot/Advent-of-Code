#include <cstdlib>
#include <fstream>
#include <iostream>

int main() {
  std::ifstream in("input.txt");
  if (!in) {
    std::cerr << "Can't open input.txt\n";
    return EXIT_FAILURE;
  }

  int dial = 50;
  int cnt = 0;

  while (true) {
    char c;
    int b;
    in >> c;
    in >> b;
    if (!in) {
      break;
    }
    if (c == 'R') {
      dial = (dial + b) % 100;
    } else if (c == 'L') {
      dial = ((dial - b) % 100 + 100) % 100;
    }
    if (dial == 0) {
      ++cnt;
    }
  }

  std::cout << cnt << '\n';
}
