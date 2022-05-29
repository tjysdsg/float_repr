#include "utils.h"

std::bitset<sizeof(uint32_t) * 8> as_bits(uint32_t val) { return {val}; }
