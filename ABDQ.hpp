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
    ABDQ(const ABDQ& other) {
        for (size_t i = other.front_; i < other.back_; i++) {
            data_[i] = other.data_[i];
        }
    }
    ABDQ(ABDQ&& other) noexcept : data_(other.data_), capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_){
        other.data_ = nullptr;
    }
    ABDQ& operator=(const ABDQ& other) {
        if (&other == this) return *this;
        T* temp = new T[other.capacity_];
        for (size_t i = other.front_; i < other.back_; i++) {
            temp[i] = other.data_[i];
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
        if (front_ <= 0) {
            for (size_t i = back_; i > 0; i--) {
                data_[i] = data_[i-1];
            }
            back_++;
            data_[front_] = item;
        }
        else {
            data_[--front_] = item;
        }
        size_++;
    }
    void pushBack(const T& item) override {
        ensureCapacity();
        if (back_ == capacity_) {
            for (size_t i = front_-1; i < back_ - 1; i++) {
                data_[i] = data_[i+1];
            }
            front_--;
            data_[back_-1] = item;
        }
        else {
            data_[back_++] = item;
        }
        size_++;
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) throw(std::runtime_error("no"));
        T ret = data_[front_++];
        size_--;
        shrinkIfNeeded();
        return ret;
    }
    T popBack() override {
        if (size_ == 0) throw(std::runtime_error("no"));
        T ret = data_[(back_--) - 1];
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
        return data_[back_-1];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

    void ensureCapacity() {
        if (size_ == capacity_) {
            T* temp = new T[capacity_ * SCALE_FACTOR];
            for (size_t i = 0; i < capacity_; i++) {
                temp[i] = data_[i];
            }
            data_ = temp;
            temp = nullptr;
            capacity_ *= SCALE_FACTOR;
        }
    }

    void shrinkIfNeeded() {
        while (size_ <= capacity_ / SCALE_FACTOR && capacity_ > 7) {
            T* temp = new T[capacity_/SCALE_FACTOR];
            for (size_t i = 0; i < size_; i++) {
                temp[i] = data_[front_ + i];
            }
            data_ = temp;
            front_ = 0;
            back_ = size_;
            capacity_ /= SCALE_FACTOR;
        }
    }

    void PrintForward() {
        for (size_t i = front_; i < back_; i++) {
            std::cout << data_[i] << "\n";
        }
    }

    void PrintReverse() {
        for (size_t i = back_ - 1; i <= front_; i--) {
            std::cout << data_[i] << "\n";
        }
    }

};
