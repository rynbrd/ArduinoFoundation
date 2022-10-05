#include <AUnit.h>
#include <Arduino.h>
#include <Foundation.h>

using namespace aunit;

namespace FDTN {

test(BinaryTest, GetBit) {
    uint8_t bytes[8] = {0x01, 0x02, 0x03, 0x04};
    assertTrue(getBit(bytes, 0, 0));
    assertFalse(getBit(bytes, 0, 1));
    assertFalse(getBit(bytes, 1, 0));
    assertTrue(getBit(bytes, 1, 1));
}

test(BinaryTest, SetBit) {
    uint8_t bytes[8] = {0x01, 0x02, 0x03, 0x04};
    assertTrue(setBit(bytes, 0, 1, 1));
    assertEqual(bytes[0], 0x03);

    assertFalse(setBit(bytes, 1, 1, 1));
    assertEqual(bytes[1], 0x02);

    assertTrue(setBit(bytes, 2, 0, 0));
    assertEqual(bytes[2], 0x02);
}

test(BinaryTest, XorBits) {
    uint8_t bytes1[8] = {0x01, 0x03, 0x03, 0x04};
    uint8_t bytes2[8] = {0x01, 0x02, 0x05, 0x05};
    assertFalse(xorBits(bytes1, bytes2, 0, 0));
    assertFalse(xorBits(bytes1, bytes2, 0, 1));
    assertTrue(xorBits(bytes1, bytes2, 1, 0));
    assertFalse(xorBits(bytes1, bytes2, 1, 1));
    assertFalse(xorBits(bytes1, bytes2, 2, 0));
    assertTrue(xorBits(bytes1, bytes2, 2, 1));
}

test(BinaryTest, FlipBit) {
    uint8_t bytes[8] = {0x01, 0x02, 0x03, 0x04};
    assertTrue(flipBit(bytes, 0, 1));
    assertEqual(bytes[0], 0x03);

    assertFalse(flipBit(bytes, 1, 1));
    assertEqual(bytes[1], 0x00);

    assertTrue(flipBit(bytes, 2, 0));
    assertEqual(bytes[2], 0x02);
}

}  // namespace FDTN

// Test boilerplate.
void setup() {
#ifdef ARDUINO
    delay(1000);
#endif
    SERIAL_PORT_MONITOR.begin(115200);
    while(!SERIAL_PORT_MONITOR);
}

void loop() {
    TestRunner::run();
    delay(1);
}
