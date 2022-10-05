#ifndef _FOUNDATION_QUEUE_H_
#define _FOUNDATION_QUEUE_H_

#include <Arduino.h>

namespace FDTN {

// A fixed-size queue.
template <typename T>
class Queue {
    public:
        // Default constructor. Creates a queue with no capacity. All calls
        // to the queue fail.
        Queue();

        // Construct a queue with the given capacity. If init is not null then
        // it is called on each of the allocated items to initialize them.
        Queue(size_t capacity, void (*init)(T*) = nullptr);

        // Destroy the queue.
        ~Queue();

        // Return a pointer to the storage location of the next slot in the
        // queue. This should be set to a value and then enqueued via the
        // regular enqueue function. This allow the queue's buffer to be
        // written to directly, thus avoiding allocating an extra item where
        // not necessary. Return nullptr if the queue is full. The queue
        // retains ownership of the pointer. The pointer is invalid after any
        // additional method call.
        T* alloc();

        // Enqueue a copy of an item. Return true on success or false if the
        // queue is full.
        bool enqueue(const T& item);

        // Dequeue an item and return a pointer ot it. The queue retains
        // ownership of the pointer. The pointer is valid until a call to
        // enqueue, dequeue, or the destructor is made. Return nullptr if the
        // queue is empty.
        T* dequeue();

        // Return a pointer to the next item in the queue. The queue retains
        // ownership of the pointer. The pointer is valid until a call to
        // enqueue, dequeue, or the destructor is made. Return nullptr if the
        // queue is empty.
        T* peek() const;

        // Return the number of items in the queue.
        size_t size() const { return size_; }

        // Return the capacity of the queue.
        size_t capacity() const { return capacity_; }

        // Return true if the queue is empty;
        bool empty() const { return size_ == 0; }

        // Return true if the queue is full.
        bool full() const { return size_ >= capacity_; }

    private:
        T* buffer_;
        size_t capacity_;
        size_t size_;
        size_t front_;
};

}  // namespace FDTN

#include "Queue.tpp"
#endif  // _FOUNDATION_QUEUE_H_
