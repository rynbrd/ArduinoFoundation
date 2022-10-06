#include "Ticker.h"

Ticker::Ticker(uint32_t interval, bool paused, Faker::Clock* clock) :
        paused_(paused), interval_(interval), last_tick_(0), clock_(clock) {}

bool Ticker::active() const {
    if (paused_) {
        return false;
    }
    if (clock_->millis() - last_tick_ >= interval_) {
        return true;
    }
    return false;
}

void Ticker::reset() {
    last_tick_ = clock_->millis();
}

void Ticker::reset(uint32_t interval) {
    interval_ = interval;
    reset();
}

void Ticker::pause() {
    paused_ = true;
}

void Ticker::resume() {
    paused_ = false;
    reset();
}
