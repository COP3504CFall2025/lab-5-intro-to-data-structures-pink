#pragma once

#include <cstddef>
#include <stdexcept>


template <typename T>
class StackInterface {
    virtual void push(const T& item) = 0;
    virtual T pop();
    virtual T peek() const;
    virtual std::size_t getSize() const noexcept;
    virtual ~StackInterface();
};


template <typename T>
class QueueInterface {
    virtual void enqueue(const T& item) = 0;
    virtual T dequeue();
    virtual T peek() const;
    virtual std::size_t getSize() const noexcept;
    virtual ~QueueInterface();
};


template <typename T>
class DequeInterface {
    virtual void pushFront(const T& item) = 0;
    virtual void pushBack(const T& item);
    virtual T popFront();
    virtual T popBack();
    virtual const T& front() const;
    virtual const T& back() const;
    virtual std::size_t getSize() const noexcept;
    virtual ~DequeInterface();
};

