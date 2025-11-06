#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() : list(LinkedList()){}

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.AddHead(item);
    }
    void pushBack(const T& item) override {
        list.AddTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        temp = list.head->data;
        list.removeHead();
        return temp;
    }
    T popBack() override {
        temp = list.tail->data;
        list.removeTail();
        return temp;
    }

    // Element Accessors
    const T& front() const override {
        return list.head->data;
    }
    const T& back() const override {
        return list.tail->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};






