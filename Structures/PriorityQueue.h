#ifndef HOW_TO_GET_THERE_PRIORITYQUEUE_H
#define HOW_TO_GET_THERE_PRIORITYQUEUE_H

#include "Vector.h"

template <typename T>
class PriorityQueue {

private:
    Vector<T> heap;


    [[nodiscard]] size_t parent(size_t i) const {
        return (i - 1) / 2;
    }


    [[nodiscard]] size_t leftChild(size_t i) const {
        return 2 * i + 1;
    }


    [[nodiscard]] size_t rightChild(size_t i) const {
        return 2 * i + 2;
    }


    void shiftUp(size_t i) {
        if (i > 0 && heap[parent(i)] > heap[i]) {
            std::swap(heap[parent(i)], heap[i]);
            shiftUp(parent(i));
        }
    }


    void shiftDown(size_t i) {
        size_t min = i;

        if (heap.getSize() == 0) {
            return;
        }

        if (leftChild(i) < heap.getSize() - 1 && heap[leftChild(i)] < heap[min]) {
            min = leftChild(i);
        }
        if (rightChild(i) < heap.getSize() - 1 && heap[rightChild(i)] < heap[min]) {
            min = rightChild(i);
        }

        if (i != min) {
            std::swap(heap[i], heap[min]);
            shiftDown(min);
        }
    }


public:
    PriorityQueue() = default;


    PriorityQueue(const PriorityQueue<T>& other) {
        heap = other.heap;
    }


    PriorityQueue(PriorityQueue<T>&& other) noexcept {
        heap = std::move(other.heap);
    }


    PriorityQueue(std::initializer_list<T> ilist) {
        for (const auto& element : ilist) {
            push(element);
        }
    }


    PriorityQueue<T>& operator=(const PriorityQueue<T>& other) {
        if (this == &other) {
            return *this;
        }

        heap = other.heap;
        return *this;
    }


    PriorityQueue<T>& operator=(PriorityQueue<T>&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        heap = std::move(other.heap);
        return *this;
    }


    PriorityQueue<T>& operator=(std::initializer_list<T> ilist) {
        for (const auto& element : ilist) {
            push(element);
        }
        return *this;
    }


    void clear() {
        heap.clear();
    }


    T& peek() const {
        return heap.front();
    }


    [[nodiscard]] bool empty() const {
        return heap.empty();
    }


    [[nodiscard]] size_t getSize() const {
        return heap.getSize();
    }


    void push(const T& data) {
        heap.pushBack(data);
        shiftUp(heap.getSize() - 1);
    }


    void pop() {
        heap[0] = heap.back();
        heap.popBack();
        shiftDown(0);
    }


    friend std::ostream& operator<<(std::ostream& os, const PriorityQueue<T>& queue) {
        os << queue.heap;
        return os;
    }
};

#endif //HOW_TO_GET_THERE_PRIORITYQUEUE_H
