#include <iostream>
#include <bitset>
#include <cassert>

using std::cout;
using std::cerr;

int main(int argc, char **argv) {
  if (argc != 2) {
    cerr << argv[0] << " num\n";
    return 1;
  }
  assert(sizeof(float) == sizeof(uint32_t));

  union {
    float f;
    uint32_t i;
  } data{};
  data.f = std::stof(std::string(argv[1]));

  std::bitset<sizeof(float) * 8> bits(data.i);
  cout << bits << '\n';

  // print the sign bit
  cout << bits[31] << ' ';

  // print the exponent
  for (int i = 30; i > 22; --i) {
    cout << bits[i];
  }
  cout << ' ';

  // print the fraction
  for (int i = 22; i >= 0; --i) {
    cout << bits[i];
  }
  cout << '\n';
  return 0;
}
