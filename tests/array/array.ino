#include <AUnit.h>
#include <Arduino.h>
#include <Foundation.h>

using namespace aunit;

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

test(ArrayTest, ConstructEmpty) {
    Array<Object> arr;
    assertEqual(arr.size(), (size_t)0);
    assertEqual(arr.capacity(), (size_t)1);
    assertNotEqual(*arr, nullptr);
}

test(ArrayTest, ConstructReserve) {
    Array<Object> arr(32);
    assertEqual(arr.size(), (size_t)0);
    assertEqual(arr.capacity(), (size_t)32);
    assertNotEqual(*arr, nullptr);
}

test(ArrayTest, ConstructInitializerEmpty) {
    Array<Object> arr({});
    assertEqual(arr.size(), (size_t)0);
    assertEqual(arr.capacity(), (size_t)1);
    assertNotEqual(*arr, nullptr);
}

test(ArrayTest, ConstructInitializer) {
    Object obj1(0x01, {0x11, 0x11});
    Object obj2(0x02, {0x22, 0x22});

    Array<Object> arr({obj1, obj2});
    assertEqual(arr.size(), (size_t)2);
    assertEqual(arr.capacity(), (size_t)2);
    assertNotEqual(*arr, nullptr);
    assertTrue(arr[0] == obj1);
    assertTrue(arr[1] == obj2);
}

test(ArrayTest, ConstructFromArray) {
    Object obj1(0x01, {0x11, 0x11});
    Object obj2(0x02, {0x22, 0x22});
    Object objs[] = {obj1, obj2};

    Array<Object> arr(objs, 2);
    assertEqual(arr.size(), (size_t)2);
    assertEqual(arr.capacity(), (size_t)2);
    assertNotEqual(*arr, nullptr);
    assertTrue(arr[0] == obj1);
    assertTrue(arr[1] == obj2);
}

test(ArrayTest, Copy) {
    Object obj1(0x01, {0x11, 0x11});
    Object obj2(0x02, {0x22, 0x22});
    Object obj3(0x03, {0x33, 0x33});

    Array<Object> arr({obj1, obj2, obj3});
    Array<Object> cpy = arr;
    assertNotEqual(*arr, *cpy);
    assertEqual(cpy.size(), (size_t)3);
    assertEqual(cpy.capacity(), (size_t)3);
    assertTrue(cpy[0] == obj1);
    assertTrue(cpy[1] == obj2);
    assertTrue(cpy[2] == obj3);
}

test(ArrayTest, Reserve) {
    Array<Object> arr;
    assertEqual(arr.capacity(), (size_t)1);

    arr.reserve(12);
    assertEqual(arr.size(), (size_t)0);
    assertEqual(arr.capacity(), (size_t)12);

    arr.reserve(5);
    assertEqual(arr.size(), (size_t)0);
    assertEqual(arr.capacity(), (size_t)12);
}

test(ArrayTest, ResizeExpand) {
    Array<Object> arr;
    arr.resize(15);
    assertEqual(arr.size(), (size_t)15);
    assertEqual(arr.capacity(), (size_t)15);
}

test(ArrayTest, ResizeShrink) {
    Array<Object> arr(15);
    arr.resize(2);
    assertEqual(arr.size(), (size_t)2);
    assertEqual(arr.capacity(), (size_t)15);
}

test(ArrayTest, Clear) {
    Object obj1(0x01, {0x11, 0x11});
    Object obj2(0x02, {0x22, 0x22});
    Object obj3(0x03, {0x33, 0x33});

    Array<Object> arr;
    arr.push_back(obj1);
    arr.push_back(obj2);
    arr.push_back(obj3);
    assertEqual(arr.size(), (size_t)3);
    assertEqual(arr.capacity(), (size_t)4);

    arr.clear();
    assertEqual(arr.size(), (size_t)0);
    assertEqual(arr.capacity(), (size_t)4);
}

test(ArrayTest, InsertFront) {
    Object obj1(0x01, {0x11, 0x11});
    Object obj2(0x02, {0x22, 0x22});
    Object obj3(0x03, {0x33, 0x33});
    Object obj4(0x04, {0x44, 0x44});
    Object objN(0x05, {0x55, 0x55});

    Array<Object> arr;
    arr.push_back(obj1);
    arr.push_back(obj2);
    arr.push_back(obj3);
    arr.push_back(obj4);
    arr.insert(0, objN);
    assertEqual(arr.size(), (size_t)5);
    assertEqual(arr.capacity(), (size_t)8);
    assertTrue(arr[0] == objN);
    assertTrue(arr[1] == obj1);
    assertTrue(arr[2] == obj2);
    assertTrue(arr[3] == obj3);
    assertTrue(arr[4] == obj4);
}

test(ArrayTest, InsertMiddle) {
    Object obj1(0x01, {0x11, 0x11});
    Object obj2(0x02, {0x22, 0x22});
    Object obj3(0x03, {0x33, 0x33});
    Object obj4(0x04, {0x44, 0x44});
    Object objN(0x05, {0x55, 0x55});

    Array<Object> arr;
    arr.push_back(obj1);
    arr.push_back(obj2);
    arr.push_back(obj3);
    arr.push_back(obj4);
    arr.insert(2, objN);
    assertEqual(arr.size(), (size_t)5);
    assertEqual(arr.capacity(), (size_t)8);
    assertTrue(arr[0] == obj1);
    assertTrue(arr[1] == obj2);
    assertTrue(arr[2] == objN);
    assertTrue(arr[3] == obj3);
    assertTrue(arr[4] == obj4);
}

test(ArrayTest, InsertBack) {
    Object obj1(0x01, {0x11, 0x11});
    Object obj2(0x02, {0x22, 0x22});
    Object obj3(0x03, {0x33, 0x33});
    Object obj4(0x04, {0x44, 0x44});
    Object objN(0x05, {0x55, 0x55});

    Array<Object> arr;
    arr.push_back(obj1);
    arr.push_back(obj2);
    arr.push_back(obj3);
    arr.push_back(obj4);
    arr.insert(4, objN);
    assertEqual(arr.size(), (size_t)5);
    assertEqual(arr.capacity(), (size_t)8);
    assertTrue(arr[0] == obj1);
    assertTrue(arr[1] == obj2);
    assertTrue(arr[2] == obj3);
    assertTrue(arr[3] == obj4);
    assertTrue(arr[4] == objN);
}

test(ArrayTest, EraseFront) {
    Object obj1(0x01, {0x11, 0x11});
    Object obj2(0x02, {0x22, 0x22});
    Object obj3(0x03, {0x33, 0x33});
    Object obj4(0x04, {0x44, 0x44});

    Array<Object> arr;
    arr.push_back(obj1);
    arr.push_back(obj2);
    arr.push_back(obj3);
    arr.push_back(obj4);
    arr.erase(0);
    assertEqual(arr.size(), (size_t)3);
    assertEqual(arr.capacity(), (size_t)4);
    assertTrue(arr[0] == obj2);
    assertTrue(arr[1] == obj3);
    assertTrue(arr[2] == obj4);
}

test(ArrayTest, EraseMiddle) {
    Object obj1(0x01, {0x11, 0x11});
    Object obj2(0x02, {0x22, 0x22});
    Object obj3(0x03, {0x33, 0x33});
    Object obj4(0x04, {0x44, 0x44});

    Array<Object> arr;
    arr.push_back(obj1);
    arr.push_back(obj2);
    arr.push_back(obj3);
    arr.push_back(obj4);
    arr.erase(1);
    assertEqual(arr.size(), (size_t)3);
    assertEqual(arr.capacity(), (size_t)4);
    assertTrue(arr[0] == obj1);
    assertTrue(arr[1] == obj3);
    assertTrue(arr[2] == obj4);
}

test(ArrayTest, EraseBack) {
    Object obj1(0x01, {0x11, 0x11});
    Object obj2(0x02, {0x22, 0x22});
    Object obj3(0x03, {0x33, 0x33});
    Object obj4(0x04, {0x44, 0x44});

    Array<Object> arr;
    arr.push_back(obj1);
    arr.push_back(obj2);
    arr.push_back(obj3);
    arr.push_back(obj4);
    arr.erase(3);
    assertEqual(arr.size(), (size_t)3);
    assertEqual(arr.capacity(), (size_t)4);
    assertTrue(arr[0] == obj1);
    assertTrue(arr[1] == obj2);
    assertTrue(arr[2] == obj3);
}

test(ArrayTest, PushBack) {
    Object obj1(0x01, {0x11, 0x11});
    Object obj2(0x02, {0x11, 0x11});
    Object obj3(0x03, {0x11, 0x11});

    Array<Object> arr;
    arr.push_back(obj1);
    assertEqual(arr.size(), (size_t)1);
    assertEqual(arr.capacity(), (size_t)1);
    assertTrue(arr[0] == obj1);

    arr.push_back(obj2);
    assertEqual(arr.size(), (size_t)2);
    assertEqual(arr.capacity(), (size_t)2);
    assertTrue(arr[1] == obj2);

    arr.push_back(obj3);
    assertEqual(arr.size(), (size_t)3);
    assertEqual(arr.capacity(), (size_t)4);
    assertTrue(arr[2] == obj3);
}

test(ArrayTest, PopBack) {
    Object obj1(0x01, {0x11, 0x11});
    Object obj2(0x02, {0x11, 0x11});

    Array<Object> arr;
    arr.push_back(obj1);
    arr.push_back(obj2);
    arr.pop_back();
    assertEqual(arr.size(), (size_t)1);
    assertEqual(arr.capacity(), (size_t)2);
    assertTrue(arr[0] == obj1);
}

test(ArrayTest, SwapAtCapacity) {
    Object obj1(0x01, {0x11, 0x11});
    Object obj2(0x02, {0x22, 0x22});
    Object obj3(0x03, {0x33, 0x33});
    Object obj4(0x04, {0x44, 0x44});

    Array<Object> arr;
    arr.push_back(obj1);
    arr.push_back(obj2);
    arr.push_back(obj3);
    arr.push_back(obj4);
    arr.swap(0, 2);

    assertEqual(arr.size(), (size_t)4);
    assertEqual(arr.capacity(), (size_t)4);
    assertTrue(arr[0] == obj3);
    assertTrue(arr[1] == obj2);
    assertTrue(arr[2] == obj1);
    assertTrue(arr[3] == obj4);
}

test(ArrayTest, SwapExtraCapacity) {
    Object obj1(0x01, {0x11, 0x11});
    Object obj2(0x02, {0x22, 0x22});
    Object obj3(0x03, {0x33, 0x33});
    Object obj4(0x04, {0x44, 0x44});

    Array<Object> arr(10);
    arr.push_back(obj1);
    arr.push_back(obj2);
    arr.push_back(obj3);
    arr.push_back(obj4);
    arr.swap(1, 3);

    assertEqual(arr.size(), (size_t)4);
    assertEqual(arr.capacity(), (size_t)10);
    assertTrue(arr[0] == obj1);
    assertTrue(arr[1] == obj4);
    assertTrue(arr[2] == obj3);
    assertTrue(arr[3] == obj2);
}

test(ArrayTest, SwapSame) {
    Object obj1(0x01, {0x11, 0x11});
    Object obj2(0x02, {0x22, 0x22});
    Object obj3(0x03, {0x33, 0x33});
    Object obj4(0x04, {0x44, 0x44});

    Array<Object> arr(10);
    arr.push_back(obj1);
    arr.push_back(obj2);
    arr.push_back(obj3);
    arr.push_back(obj4);
    arr.swap(2, 2);

    assertEqual(arr.size(), (size_t)4);
    assertEqual(arr.capacity(), (size_t)10);
    assertTrue(arr[0] == obj1);
    assertTrue(arr[1] == obj2);
    assertTrue(arr[2] == obj3);
    assertTrue(arr[3] == obj4);
}

test(ArrayTest, SetElement) {
    Object obj1(0x01, {0x11, 0x11});
    Object obj2(0x02, {0x22, 0x22});

    Array<Object> arr;
    arr.resize(2);
    arr[0] = obj1;
    arr[1] = obj2;
    assertEqual(arr.size(), (size_t)2);
    assertEqual(arr.capacity(), (size_t)2);
    assertTrue(arr[0] == obj1);
    assertTrue(arr[1] == obj2);
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
    TestRunner::run();
    delay(1);
}
