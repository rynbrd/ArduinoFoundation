#ifndef _FOUNDATION_BINARY_H_
#define _FOUNDATION_BINARY_H_

#include <Arduino.h>

namespace FDTN {

// Get a bit from a byte array.
bool getBit(const byte* b, uint8_t offset, uint8_t bit);

// Set a bit in a byte array. Return true if the bit was changed.
bool setBit(byte* b, uint8_t offset, uint8_t bit, bool value);

// Return true if a bit in two differet byte arrays differ.
bool xorBits(const byte* b1, const byte* b2, uint8_t offset, uint8_t bit);

// Flip a bit in a byte array. Return the resulting bit.
bool flipBit(byte* b, uint8_t offset, uint8_t bit);

}  // namespace FDTN

#endif  // _FOUNDATION_BINARY_H_
