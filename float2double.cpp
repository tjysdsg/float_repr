#include "utils.h"
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>

using std::cerr;
using std::cout;
int main(int argc, char **argv) {
  if (argc != 2) {
    cerr << argv[0] << " num\n";
    return 1;
  }
  static_assert(sizeof(float) == sizeof(uint32_t));

  union {
    float f;
    uint32_t i;
  } data{};
  // data.i = 0x400000;
  data.f = std::stof(std::string(argv[1]));

  cout << "num = " << data.f << '\n';

  uint64_t sign = data.i & (1 << 31);
  sign <<= 32;

  uint64_t exp = data.i & FP32_EXPONENT_MASK;
  uint64_t frac = data.i & FP32_FRACTION_MASK;
  if (exp) {
    exp >>= 23;
    exp -= (1 << 7) - 1;
    exp += (1 << 10) - 1;
    exp <<= 52;
    frac <<= 29;
  } else {
    exp <<= 52 - 23;
  }

  uint64_t fp64 = sign | exp | frac;
  cout << *(double *)&fp64 << '\n';

  return 0;
}
