#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ() : capacity_(1), curr_size_(0), array_(new T[1]) {}
    explicit ABQ(const size_t capacity) : capacity_(capacity), curr_size_(0), array_(new T[capacity]) {}
    ABQ(const ABQ& other) : curr_size_(other.curr_size_), capacity_(other.capacity_){
        array_ = new T[other.capacity_];
        for (size_t i = 0; i < curr_size_; i++) {
            array_[i] = other.array_[i];
        }
    }
    ABQ& operator=(const ABQ& rhs) {
        if (&rhs == this) return *this;
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
    ABQ(ABQ&& other) noexcept : array_(other.array_), capacity_(other.capacity_), curr_size_(other.curr_size_) {
        other.array_ = nullptr;
    }
    ABQ& operator=(ABQ&& rhs) noexcept {
        if (&other == this) return *this;
        delete[] array_;
        array_ = rhs.array_;
        rhs.array_ = nullptr;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        return *this;
    }
    ~ABQ() noexcept override {
        delete[] array_;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    // Insertion
    void enqueue(const T& data) override {
        if (curr_size_ == capacity_) {
            capacity_ *= scale_factor_;
            T* temp = new T[capacity_];
            for (size_t i = 0; i < curr_size_; i++) {
                temp[i] = array_[i];
            }
        }
        temp[curr_size_++] = data;
        delete[] array_;
        array_ = temp;
    }

    // Access
    T peek() const override {
        return array_[0];
    }

    // Deletion
    T dequeue() override {
        T temp = array_[0];
        for (int i = 1; i < curr_size_) {
            array_[i-1] = array_[i];
        }
        curr_size_--;
        return temp;
    }

    void PrintForward() {
        for (size_t i = 0; i < curr_size_; i++) {
            std::cout << array_[i] << "\n";
        }
    }

    void PrintReverse() {
        for (size_t i = curr_size_ - 1; i <= 0; i--) {
            std::cout << array_[i] << "\n";
        }
    }

};
