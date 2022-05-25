#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>

using std::cerr;
using std::cout;

const uint32_t EXPONENT_MASK = 0x7F800000;
const uint32_t EXPONENT_START = 23;
const uint32_t EXPONENT_END = 31;

const uint32_t FRACTION_MASK = 0x7FFFFF;
const uint32_t FRACTION_START = 0;
const uint32_t FRACTION_END = 23;

std::bitset<sizeof(uint32_t) * 8> as_bits(uint32_t val) { return {val}; }

void print_exponent(std::bitset<sizeof(uint32_t) * 8> bits) {
  for (int i = EXPONENT_END - 1; i >= (int)EXPONENT_START; --i) {
    cout << bits[i];
  }
}

void print_fraction(std::bitset<sizeof(uint32_t) * 8> bits) {
  for (int i = FRACTION_END - 1; i >= (int)FRACTION_START; --i) {
    cout << bits[i];
  }
}

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
  // data.i = EXPONENT_MASK;
  // data.i = FRACTION_MASK;
  data.f = std::stof(std::string(argv[1]));
  auto bits = as_bits(data.i);

  cout << "The number is " << data.f << '\n';

  // print float as bits
  cout << "" << bits[31] << ' ';
  print_exponent(bits);
  cout << ' ';
  print_fraction(bits);
  cout << "\nS    E               F            \n";

  // explain sign
  cout << "The sign bit is " << bits[31] << ", so the number is ";
  cout << (bits[31] ? "negative\n" : "positive\n");

  // explain exponent
  int expo = (data.i & EXPONENT_MASK) >> EXPONENT_START;
  cout << "Exp = " << expo;
  expo -= 127;
  cout << " - 127 = " << expo << '\n';

  // explain fraction
  uint32_t fraction = data.i & FRACTION_MASK;
  auto fraction_bits = as_bits(fraction);

  // find the base for the highest digit
  float base = 1;
  int curr_expo = expo;
  while (curr_expo < 0) {
    base /= 2;
    ++curr_expo;
  }
  float frac = base;
  cout << "Fraction = 1 * 2^" << expo << " (prepended 1)";

  curr_expo = expo - 1;
  base /= 2;
  uint32_t fraction_n_bits = FRACTION_END - FRACTION_START;
  for (int i = fraction_n_bits - 1; i >= 0; --i) {
    if (fraction_bits[i]) {
      cout << " + 1 * 2^";
      cout << curr_expo << " (the " << i + 1 << "-th bit)";
    }

    frac += fraction_bits[i] * base;
    base /= 2;
    --curr_expo;
  }

  cout << " = " << frac << '\n';

  cout << "num = " << frac << " * 2^" << expo << " = "
       << pow(2, expo) * frac << '\n';
  return 0;
}
