#ifndef _FOUNDATION_TICKER_H_
#define _FOUNDATION_TICKER_H_

#include <Arduino.h>
#include <Faker.h>

// Ticker is used to trigger actions repeatedly after a time interval.
class Ticker {
    public:
        // Construct a ticker which triggers after interval ms have passed. A
        // zero interval will trigger on every call to active. The ticker can
        // be created in a paused state by passing true to the paused arg.
        explicit Ticker(uint32_t interval, bool paused = false,
                Faker::Clock* clock = Faker::Clock::real());

        // Return true if the interval has passed. This will return true for
        // subsequent calls until reset is called.
        bool active() const;

        // Reset the ticker's interval. Optionally set a new interval value.
        void reset();
        void reset(uint32_t interval);

        // Pause the ticker. Calls to active() will return false until resume()
        // is called. This is a noop if the ticker is already paused.
        void pause();

        // Return true if the ticker is paused.
        bool paused();

        // Reset and resume the ticker after it was paused. Calls to active()
        // will behave normally. This is a noop if the ticker is not paused.
        // Optionally set a new interval value.
        void resume();
        void resume(uint32_t interval);

        // Return true if the ticker has ever been active since last being
        // resumed.
        bool triggered();
    private:
        bool paused_;
        bool triggered_;
        uint32_t interval_;
        uint32_t last_tick_;
        Faker::Clock* clock_;
};

#endif  // _FOUNDATION_TICKER_H_
