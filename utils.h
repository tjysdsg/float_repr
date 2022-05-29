#ifndef FLOAT_REPR__UTILS_H
#define FLOAT_REPR__UTILS_H

#include <bitset>

const uint32_t FP32_EXPONENT_MASK = 0x7F800000;
const uint32_t FP32_FRACTION_MASK = 0x7FFFFF;

const uint64_t FP64_EXPONENT_MASK = 0x7FF0000000000000;
const uint64_t FP64_FRACTION_MASK = 0xFFFFFFFFFFFFF;

std::bitset<sizeof(uint32_t) * 8> as_bits(uint32_t val);

#endif // FLOAT_REPR__UTILS_H
