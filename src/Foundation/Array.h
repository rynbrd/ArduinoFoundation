#ifndef _FDTN_ARRAY_H_
#define _FDTN_ARRAY_H_

#include <Arduino.h>

// A dynamic array. Capacity is generally increased by doubling the current
// capacity to avoid excessive allocations when adding multiple items. It is
// always better to reserve anticipated capacity up front via the constructor
// or by calling reserve().
template <typename T>
class Array {
    public:
        // Construct an array. Optionally reserve capacity.
        explicit Array(size_t reserve = 0);

        // Construct an array containing the contents of an initializer list. The
        // capacity is set to the size of the list. 
        template <size_t N>
        explicit Array(const T (&elements)[N]);

        // Construct an array containing a copy of the elements in the provided
        // array with the given size.
        Array(const T* elements, size_t size);

        // Copy constructor. The new array only allocates enough capacity to
        // store the number of elements in src.
        Array(const Array<T>& src);

        virtual ~Array();

        // Return the size of the array.
        size_t size() const { return size_; }

        // Return the capacity of the array.
        size_t capacity() const { return capacity_; }

        // Ensure the array has at least the requested capacity.
        void reserve(size_t capacity);

        // Shrink or grow the array. Capacity is allocated if the new size
        // exceeds the current capacity. Capacity is not freed when shrinking.
        void resize(size_t size);

        // Clear the contents of the array. This retains the array's allocated
        // capacity.
        void clear();

        // Insert an item into the array at the given position. Increases
        // capacity if necessary.
        void insert(size_t pos, const T& element);

        // Remove an item from the array at the given position. Does not reduce
        // the capacity of the array.
        void erase(size_t pos);

        // Push an element to the end of the array. Allocates additional
        // capacity if necessary.
        void push_back(const T& element);

        // Remove an element from the end of the array. Does not reduce the
        // capacity of the array.
        void pop_back();

        // Swap two elements in the array identified by their positions.
        void swap(size_t pos_a, size_t pos_b);

        // Return a pointer to the underlying array.
        const T* data() const { return elements_; };
        const T* operator*() const { return elements_; }

        // Return the element at the given index.
        T operator[](size_t i) const { return elements_[i]; }
        T& operator[](size_t i) { return elements_[i]; }

    private:
        size_t size_;
        size_t capacity_;
        T* elements_;
};

#include "Array.tpp"

#endif  // _FDTN_ARRAY_H_
