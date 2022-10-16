#include <AUnit.h>
#include <Arduino.h>
#include <Faker.h>
#include <Foundation.h>

using namespace aunit;
using ::Faker::FakeClock;

test(TickerTest, TickAndReset) {
    FakeClock clock;
    Ticker t(500, false, &clock);

    assertFalse(t.active());

    clock.set(200);
    assertFalse(t.active());

    clock.set(500);
    assertTrue(t.active());
    clock.set(501);
    assertTrue(t.active());
    t.reset();

    clock.set(502);
    assertFalse(t.active());

    clock.set(1000);
    assertFalse(t.active());
    clock.set(1001);
    assertTrue(t.active());
}

test(TickerTest, EarlyReset) {
    FakeClock clock;
    Ticker t(500, false, &clock);
    assertFalse(t.active());

    clock.set(200);
    assertFalse(t.active());

    t.reset();
    assertFalse(t.active());

    clock.set(500);
    assertFalse(t.active());

    clock.set(700);
    assertTrue(t.active());
}

test(TickerTest, TickAndResetNewInterval) {
    FakeClock clock;
    Ticker t(500, false, &clock);

    assertFalse(t.active());

    clock.set(500);
    assertTrue(t.active());
    t.reset(1000);

    clock.set(1000);
    assertFalse(t.active());

    clock.set(1500);
    assertTrue(t.active());
}

test(TickerTest, ZeroTick) {
    FakeClock clock;
    Ticker t(0, false, &clock);

    assertTrue(t.active());
    clock.set(1000000000);
    assertTrue(t.active());
}

test(TickerTest, StartPaused) {
    FakeClock clock;
    Ticker t(0, true, &clock);

    assertTrue(t.paused());
    assertFalse(t.active());
    assertFalse(t.triggered());
    clock.set(1000000000);
    assertFalse(t.active());
    t.reset();
    assertFalse(t.triggered());
}

test(TickerTest, PauseResume) {
    FakeClock clock;
    Ticker t(100, false, &clock);

    assertFalse(t.paused());
    assertFalse(t.active());
    t.reset();
    assertFalse(t.triggered());
    clock.set(101);
    assertTrue(t.active());
    t.reset();
    assertTrue(t.triggered());
    t.pause();
    clock.set(201);
    assertTrue(t.paused());
    assertFalse(t.active());
    t.reset();
    assertTrue(t.triggered());
    t.resume();
    assertFalse(t.paused());
    assertFalse(t.triggered());
    clock.set(301);
    assertTrue(t.active());
    t.reset();
    assertTrue(t.triggered());
}

// Test boilerplate.
void setup() {
#ifdef ARDUINO
    delay(1000);
#endif
    SERIAL_PORT_MONITOR.begin(115200);
    while(!SERIAL_PORT_MONITOR);
}

void loop() {
    aunit::TestRunner::run();
    delay(1);
}
