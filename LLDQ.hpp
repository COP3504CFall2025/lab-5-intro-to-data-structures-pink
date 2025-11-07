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
    LLDQ() : list(){}

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.addHead(item);
    }
    void pushBack(const T& item) override {
        list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        temp = list.getHead()->data;
        list.removeTail();
        return temp;
    }
    T popBack() override {
        temp = list.getTail()->data;
        list.removeTail();
        return temp;
    }

    // Element Accessors
    const T& front() const override {
        return list.getHead()->data;
    }
    const T& back() const override {
        return list.getTail()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};






