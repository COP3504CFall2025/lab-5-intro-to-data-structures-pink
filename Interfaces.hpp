#pragma once

#include <cstddef>
#include <stdexcept>
#include <iostream>


template <typename T>
class StackInterface {
    public:
    virtual void push(const T& item) = 0;
    virtual T pop();
    virtual T peek() const;
    virtual std::size_t getSize() const noexcept;
    virtual ~StackInterface() = default;
};


template <typename T>
class QueueInterface {
    public:
    virtual void enqueue(const T& item) = 0;
    virtual T dequeue();
    virtual T peek() const;
    virtual std::size_t getSize() const noexcept;
    virtual ~QueueInterface() = default;
};


template <typename T>
class DequeInterface {
    public:
    virtual void pushFront(const T& item) = 0;
    virtual void pushBack(const T& item);
    virtual T popFront();
    virtual T popBack();
    virtual const T& front() const;
    virtual const T& back() const;
    virtual std::size_t getSize() const noexcept;
    virtual ~DequeInterface() = default;
};

