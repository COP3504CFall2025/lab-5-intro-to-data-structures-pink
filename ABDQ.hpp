#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() : data_(new T[4]), capacity_(4), size_(0), front_(0), back_(0){}
    explicit ABDQ(std::size_t capacity) : data_(new T[capacity]), capacity_(capacity), size_(0), front_(0), back_(0){}
    ABDQ(const ABDQ& other) : data_(new T[other.capacity_]), capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_) {
        for (size_t i = 0; i < other.size_; i++) {
            data_[(other.front_ + i) % capacity_] = other.data_[(other.front_ + i) % capacity_];
        }
    }
    ABDQ(ABDQ&& other) noexcept : data_(other.data_), capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_){
        other.data_ = nullptr;
    }
    ABDQ& operator=(const ABDQ& other) {
        if (&other == this) return *this;
        T* temp = new T[other.capacity_];
        for (size_t i = 0; i < other.size_; i++) {
            data_[(other.front_ + i) % capacity_] = other.data_[(other.front_ + i) % capacity_];
        }
        delete[] data_;
        data_ = temp;
        size_ = other.size_;
        capacity_ = other.capacity_;
        front_ = other.front_;
        back_ = other.back_;
        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (&other == this) return *this;
        delete[] data_;
        data_ = other.data_;
        other.data_ = nullptr;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        return *this;
    }
    ~ABDQ() override {
        delete[] data_;
    }

    // Insertion
    void pushFront(const T& item) override {
        ensureCapacity();
        front_ = (capacity_ + front_ - 1)%capacity_;
        data_[front_] = item;
        size_++;
    }
    void pushBack(const T& item) override {
        ensureCapacity();
        data_[back_++] = item;
        back_ %= capacity_; 
        size_++;
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) throw(std::runtime_error("no"));
        T ret = data_[front_++];
        front_ %= capacity_;
        size_--;
        shrinkIfNeeded();
        return ret;
    }
    T popBack() override {
        if (size_ == 0) throw(std::runtime_error("no"));
        back_ = (capacity_ + back_ - 1) % capacity_;
        T ret = data_[back_];
        size_--;
        shrinkIfNeeded();
        return ret;
    }

    // Access
    const T& front() const override {
        if (size_ == 0) throw(std::runtime_error("no"));
        return data_[front_];
    }
    const T& back() const override {
        if (size_ == 0) throw(std::runtime_error("no"));
        return data_[(capacity_ + back_-1)%capacity_];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

    void ensureCapacity() {
        if (size_ == capacity_) {
            T* temp = new T[capacity_ * SCALE_FACTOR];
            for (size_t i = 0; i < size_; i++) {
                temp[i] = data_[(front_ + i) % capacity_];
            }
            delete[] data_;
            data_ = temp;
            front_ = 0;
            back_ = size_;
            temp = nullptr;
            capacity_ *= SCALE_FACTOR;
        }
    }

    void shrinkIfNeeded() {
        while (size_ <= capacity_ / SCALE_FACTOR && capacity_ > 7) {
            T* temp = new T[capacity_/SCALE_FACTOR];
            for (size_t i = 0; i < size_; i++) {
                temp[(front_ + i) % (capacity_/SCALE_FACTOR)] = data_[(front_ + i)%capacity_];
            }
            delete[] data_;
            data_ = temp;
            capacity_ /= SCALE_FACTOR;
            front_ %= capacity_;
            back_ = (front_ + size_) % capacity_;
        }
    }

    void PrintForward() {
        for (size_t i = 0; i < size_; i++) {
            std::cout << data_[(front_ + i) % capacity_] << "\n";
        }
    }

    void PrintReverse() {
        for (size_t i = 0; i < size_; i--) {
            std::cout << data_[(capacity_ + back_ - 1 - i) % capacity_] << "\n";
        }
    }

};
