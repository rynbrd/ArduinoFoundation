#include "Ticker.h"

Ticker::Ticker(uint32_t interval, bool paused, Faker::Clock* clock) :
        paused_(paused), triggered_(false), interval_(interval),
        last_tick_(0), clock_(clock) {}

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
    if (!paused_ && clock_->millis() - last_tick_ >= interval_) {
        triggered_ = true;
    }
    last_tick_ = clock_->millis();
}

void Ticker::reset(uint32_t interval) {
    reset();
    interval_ = interval;
}

void Ticker::pause() {
    if (!paused_ && clock_->millis() - last_tick_ >= interval_) {
        triggered_ = true;
    }
    paused_ = true;
}

bool Ticker::paused() {
    return paused_;
}

void Ticker::resume() {
    paused_ = false;
    triggered_ = false;
    last_tick_ = clock_->millis();
}

void Ticker::resume(uint32_t interval) {
    resume();
    interval_ = interval;
}

bool Ticker::triggered() {
    if (!paused_ && clock_->millis() - last_tick_ >= interval_) {
        triggered_ = true;
    }
    return triggered_;
}
