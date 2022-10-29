#include <iostream>

typedef std::uint64_t hash_t;

constexpr hash_t prime = 0x100000001B3ull;     // 散列的质数
constexpr hash_t basis = 0xCBF29CE484222325ull;// 初始的哈希值

hash_t hash_(std::string_view str) {
  hash_t ret{basis};
  for (auto c : str) {
    ret ^= c;
    ret *= prime;
  }
  return ret;
}

constexpr hash_t hash(std::string_view str, hash_t last = basis) {
  return !str.empty() ? hash(str.substr(1), (str[0] ^ last) * prime) : last;
}

constexpr unsigned long long operator"" _hash(char const *p, size_t) {
  return hash(p);
}

void switch_string(char const *str) {
  switch (hash_(str)) {
  case "first"_hash:
    std::cout << 1 << std::endl;
    break;
  case "second"_hash:
    std::cout << 2 << std::endl;
    break;
  case "third"_hash:
    std::cout << 3 << std::endl;
    break;
  default:
    std::cout << 0 << std::endl;
  }
}

int main() {
  switch_string("first");
  switch_string("second");
  switch_string("third");
  switch_string("fourth");

  return 0;
}
