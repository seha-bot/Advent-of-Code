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
      dial += b;
      cnt += dial / 100;
      dial %= 100;
    } else if (c == 'L') {
      // for (int i = dial - b; i < dial; i++) {
      //     if (i % 100 == 0) {
      //         ++cnt;
      //     }
      // }

      auto floor_div_100 = [](int n) {
        return n / 100 - (n < 0 && n % 100 != 0);
      };
      cnt += floor_div_100(dial - 1) - floor_div_100(dial - b - 1);
      dial = ((dial - b) % 100 + 100) % 100;
    }
  }

  std::cout << cnt << '\n';
}
