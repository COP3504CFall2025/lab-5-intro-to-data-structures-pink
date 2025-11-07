#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() : capacity_(1), curr_size_(0), array_(new T[1]) {}
    explicit ABS(const size_t capacity) : capacity_(capacity), curr_size_(0), array_(new T[capacity]) {}
    ABS(const ABS& other) : curr_size_(other.curr_size_), capacity_(other.capacity_){
        array_ = new T[other.capacity_];
        for (size_t i = 0; i < curr_size_; i++) {
            array_[i] = other.array_[i];
        }
    }
    ABS& operator=(const ABS& rhs) {
        if (&rhs == this) return this;
        T* temp = new T[rhs.capacity_];
        for (size_t i = 0; i < rhs.curr_size_; i++) {
            temp[i] = rhs.array_[i];
        }
        delete[] array_;
        array_ = temp;
        curr_size_ = rhs.curr_size_;
        capacity_ = rhs.capacity_;
        return *this;
    }
    ABS(ABS&& other) noexcept : array_(other.array_), capacity_(other.capacity_), curr_size_(other.curr_size_) {
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
    }
    ABS& operator=(ABS&& rhs) noexcept {
        if (&rhs == this) return *this;
        delete[] array_;
        array_ = rhs.array_;
        rhs.array_ = nullptr;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        return *this;
    }
    ~ABS() noexcept override {
        delete[] array_;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    // Push item onto the stack
    void push(const T& data) override {
        if (curr_size_ == capacity_) {
            capacity_ *= scale_factor_;
            T* temp = new T[capacity_];
            for (size_t i = 0; i < curr_size_; i++) {
                temp[i] = array_[i];
            }
            delete[] array_;
            array_ = temp;
        }
        array_[curr_size_++] = data;
    }

    T peek() const override {
        if (curr_size_ == 0) throw(std::runtime_error("no"));
        return array_[curr_size_-1];
    }

    T pop() override {
        if (curr_size_ == 0) throw(std::runtime_error("no"));
        return array_[(curr_size_--) - 1];
        shrinkIfNeeded();
    }

    void printForward() {
        for (size_t i = 0; i < curr_size_; i++) {
            std::cout << array_[i] << "\n";
        }
    }

    void printReverse() {
        for (size_t i = curr_size_ - 1; i <= 0; i--) {
            std::cout << array_[i] << "\n";
        }
    }

    void shrinkIfNeeded() {
        while (curr_size_ <= capacity_ / scale_factor_ && capacity_ > 1) {
            T* temp = new T[capacity_/scale_factor_];
            for (size_t i = 0; i < curr_size_; i++) {
                temp[i] = array_[i];
            }
            delete[] array_;
            array_ = temp;
            capacity_ /= scale_factor_;
        }
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
