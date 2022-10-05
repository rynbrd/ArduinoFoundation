namespace FDTN {

template <typename T>
Queue<T>::Queue() : Queue(0, nullptr) {}

template <typename T>
Queue<T>::Queue(size_t capacity, void (*init)(T*)) :
        buffer_(nullptr), capacity_(capacity), size_(0), front_(0) {
    if (capacity_ > 0) {
        buffer_ = new T[capacity_];
        if (init != nullptr) {
            for (size_t i = 0; i < capacity_; ++i) {
                init(buffer_ + i);
            }
        }
    }
}

template <typename T>
Queue<T>::~Queue() {
    if (buffer_ != nullptr) {
        delete[] buffer_;
    }
}

template <typename T>
T* Queue<T>::alloc() {
    if (full()) {
        return nullptr;
    }
    return buffer_ + ((front_ + size_) % capacity_);
}

template <typename T>
bool Queue<T>::enqueue(const T& item) {
    if (full()) {
        return false;
    }
    size_t i = (front_ + size_) % capacity_;
    if (&item != buffer_ + i) {
        buffer_[i] = item;
    }
    ++size_;
    return true;
}

template <typename T>
T* Queue<T>::dequeue() {
    T* item = peek();
    if (item != nullptr) {
        front_ = (front_ + 1) % capacity_;
        --size_;
    }
    return item;
}

template <typename T>
T* Queue<T>::peek() const {
    if (empty()) {
        return nullptr;
    }
    return buffer_ + front_;
}

}  // namespace FDTN
