#include <AUnit.h>
#include <Arduino.h>
#include <Foundation.h>

using namespace aunit;

namespace FDTN {

class Object {
    public:
        Object() : Object(0, {0x00, 0x00}) {}

        Object(uint8_t id, const uint8_t (&data)[2]) : id_(id) {
            memcpy(data_, data, 2);
        }

        uint8_t id() const { return id_; }
        const uint8_t* data() const { return data_; }

        void id(uint8_t id) { id_ = id; }
        void data(const uint8_t (&data)[2]) { memcpy(data_, data, 2); }
    private:
        uint8_t id_;
        uint8_t data_[2];
};

bool operator==(const Object& left, const Object& right) {
    return left.id() == right.id() && memcmp(left.data(), right.data(), 2) == 0;
}

bool operator!=(const Object& left, const Object& right) {
    return left.id() != right.id() || memcmp(left.data(), right.data(), 2) != 0;
}

test(QueueTest, ZeroCapacity) {
    Object expect(0x10, {0x11, 0x22});
    Queue<Object> q;
    assertEqual(q.enqueue(expect), false);
    assertEqual(q.dequeue(), nullptr);
    assertEqual(q.peek(), nullptr);
    assertEqual(q.size(),  (size_t)0);
    assertEqual(q.capacity(), (size_t)0);
    assertEqual(q.empty(), true);
    assertEqual(q.full(), true);
    assertEqual(q.alloc(), nullptr);
}

test(QueueTest, ExtraCapacity) {
    Object expect(0x10, {0x11, 0x22});

    Queue<Object> q(2);
    assertEqual(q.capacity(), (size_t)2);
    assertEqual(q.empty(), true);
    assertEqual(q.peek(), nullptr);

    assertEqual(q.enqueue(expect), true);
    assertEqual(q.size(),  (size_t)1);
    assertEqual(q.empty(), false);
    assertEqual(q.full(), false);

    assertTrue(*q.peek() == expect);
    assertTrue(*q.dequeue() == expect);

    assertEqual(q.peek(), nullptr);
    assertEqual(q.dequeue(), nullptr);
    assertEqual(q.empty(), true);
    assertEqual(q.full(), false);
}

test(QueueTest, NotEnoughCapacity) {
    Object expect1(0x10, {0x11, 0x22});
    Object expect2(0x20, {0x11, 0x22});
    Object expect3(0x30, {0x11, 0x22});

    Queue<Object> q(2);
    assertEqual(q.capacity(), (size_t)2);
    assertEqual(q.empty(), true);
    assertEqual(q.peek(), nullptr);

    assertEqual(q.enqueue(expect1), true);
    assertEqual(q.size(),  (size_t)1);
    assertEqual(q.empty(), false);
    assertEqual(q.full(), false);
    assertTrue(*q.peek() == expect1);

    assertEqual(q.enqueue(expect2), true);
    assertEqual(q.size(),  (size_t)2);
    assertEqual(q.empty(), false);
    assertEqual(q.full(), true);
    assertTrue(*q.peek() == expect1);

    assertEqual(q.enqueue(expect3), false);
    assertEqual(q.size(),  (size_t)2);
    assertEqual(q.empty(), false);
    assertEqual(q.full(), true);

    assertTrue(*q.peek() == expect1);
    assertTrue(*q.dequeue() == expect1);
    assertEqual(q.size(), (size_t)1);
    assertEqual(q.empty(), false);
    assertEqual(q.full(), false);

    assertTrue(*q.peek() == expect2);
    assertTrue(*q.dequeue() == expect2);
    assertEqual(q.size(), (size_t)0);
    assertEqual(q.empty(), true);
    assertEqual(q.full(), false);

    assertEqual(q.dequeue(), nullptr);
}

test(QueueTest, MixedUsage) {
    Object expect1(0x10, {0x11, 0x22});
    Object expect2(0x20, {0x11, 0x22});
    Object expect3(0x30, {0x11, 0x22});

    Queue<Object> q(2);
    assertTrue(q.enqueue(expect1));
    assertTrue(*q.peek() == expect1);

    assertTrue(q.enqueue(expect2));
    assertTrue(*q.dequeue() == expect1);

    assertTrue(q.enqueue(expect3));
    assertTrue(*q.dequeue() == expect2);
    assertTrue(*q.dequeue() == expect3);
}

void initObjectData(Object* obj) {
    obj->id(0x10);
    obj->data({0x11, 0x22});
}

test(QueueTest, Init) {
    Object expect(0x10, {0x11, 0x22});

    Queue<Object> q(1, initObjectData);
    Object* alloc = q.alloc();
    assertTrue(*alloc == expect);
}

test(QueueTest, AllocAndQueue) {
    Object expect(0x23, {0x12, 0x13});

    Queue<Object> q(1);
    Object* actual = q.alloc();
    actual->id(0x23);
    actual->data({0x12, 0x13});
    q.enqueue(*actual);

    assertEqual(q.size(), (size_t)1);
    assertTrue(*q.peek() == expect);
    assertTrue(*q.dequeue() == expect);
    assertTrue(q.empty());
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
