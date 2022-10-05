
template <typename T>
Array<T>::Array(size_t reserve) :
        size_(0), capacity_(max((size_t)1, reserve)),
        elements_(new T[capacity_]) {}

template <typename T>
template <size_t N>
Array<T>::Array(const T (&elements)[N]) :
        size_(N), capacity_(max((size_t)1, size_)),
        elements_(new T[capacity_]) {
    memcpy(elements_, elements, sizeof(T) * size_);
}

template <typename T>
Array<T>::Array(const T* elements, size_t size) :
        size_(size), capacity_(max((size_t)1, size_)),
        elements_(new T[capacity_]) {
    memcpy(elements_, elements, sizeof(T) * size_);
}

template <typename T>
Array<T>::Array(const Array<T>& src) :
        size_(src.size_), capacity_(max((size_t)1, size_)),
        elements_(new T[capacity_]) {
    memcpy(elements_, src.elements_, sizeof(T) * size_);
}

template <typename T>
Array<T>::~Array() {
    delete[] elements_;
}

template <typename T>
void Array<T>::reserve(size_t capacity) {
    if (capacity_ >= capacity) {
        return;
    }

    T* new_elements = new T[capacity];
    for (size_t i = 0; i < size_; i++) {
        new_elements[i] = elements_[i];
    }
    delete[] elements_;
    elements_ = new_elements;
    capacity_ = capacity;
}

template <typename T>
void Array<T>::resize(size_t size) {
    reserve(size);
    size_ = size;
}

template <typename T>
void Array<T>::clear() { size_ = 0; };

template <typename T>
void Array<T>::insert(size_t pos, const T& element) {
    if (pos > size_) {
        pos = size_;
    }
    if (size_ == capacity_) {
        reserve(capacity_*2);
    }
    if (pos < size_) {
        memmove(elements_ + pos + 1, elements_ + pos, sizeof(T) * (size_ - pos));
    }
    elements_[pos] = element;
    ++size_;
}

template <typename T>
void Array<T>::erase(size_t pos) {
    if (size_ == 0 || pos >= size_) {
        return;
    }
    if (pos < size_) {
        memmove(elements_ + pos, elements_ + pos + 1, sizeof(T) * (size_ - pos - 1));
    }
    --size_;
}

template <typename T>
void Array<T>::push_back(const T& element) {
    if (size_ == capacity_) {
        reserve(capacity_*2);
    }
    elements_[size_++] = element;
}

template <typename T>
void Array<T>::pop_back() {
    if (size_ > 0) {
        --size_;
    }
}

template <typename T>
void Array<T>::swap(size_t pos_a, size_t pos_b) {
    if (pos_a == pos_b) {
        return;
    }
    if (capacity_ > size_) {
        // use extra capacity as tmp space
        elements_[capacity_ - 1] = elements_[pos_a];
        elements_[pos_a] = elements_[pos_b];
        elements_[pos_b] = elements_[capacity_ - 1];
    } else {
        T tmp = elements_[pos_a];
        elements_[pos_a] = elements_[pos_b];
        elements_[pos_b] = tmp;
    }
}
