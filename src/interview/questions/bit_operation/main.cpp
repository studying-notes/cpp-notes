#include <iostream>
#include <map>

int add(int x, int y) {
  int sum = x ^ y;
  int carry = x & y;
  return carry ? add(sum, carry << 1) : sum;
}

int multiply(int x, int y) {
  bool negative = false;

  if (y < 0) {
    negative = true;
    y = add(~y, 1);
  }

  int sum = 0;

  std::map<int, int> bit_map;
  for (int i = 0; i < 32; i++) {
    bit_map.insert(std::pair<int, int>(1 << i, i));
  }

  while (y > 0) {
    int last_bit = bit_map[y & ~(y - 1)];
    sum += (x << last_bit);
        y &= y - 1;
  }

  return negative ? add(~sum, 1) : sum;
}

int main() {
  std::cout << multiply(-15, -3) << std::endl;
  return 0;
}
