#ifndef HOW_TO_GET_THERE_QUEUE_H
#define HOW_TO_GET_THERE_QUEUE_H

#include "List.h"

template<typename T>
class Queue {

private:
    List<T> list;

public:
    Queue() = default;


    Queue(const Queue<T>& other) {
        list = other.list;
    }


    Queue(Queue<T>&& other) noexcept {
        list = std::move(other.list);
    }


    Queue(std::initializer_list<T> ilist) {
        list = ilist;
    }


    Queue<T>& operator=(const Queue<T>& other) {
        if (this == &other) {
            return *this;
        }

        list = other.list;
        return *this;
    }


    Queue<T>& operator=(Queue<T>&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        list = std::move(other.list);
        return *this;
    }


    Queue<T>& operator=(std::initializer_list<T> ilist) {
        list = ilist;
        return *this;
    }


    void clear() {
        list.clear();
    }


    T& peek() const {
        return list.front();
    }


    [[nodiscard]] bool empty() const {
        return list.empty();
    }


    [[nodiscard]] size_t getSize() const {
        return list.getSize();
    }


    void push(const T& data) {
        list.pushBack(data);
    }


    void pop() {
        list.popFront();
    }


    friend std::ostream& operator<<(std::ostream& os, const Queue<T>& queue) {
        os << queue.list;
        return os;
    }
};

#endif //HOW_TO_GET_THERE_QUEUE_H
