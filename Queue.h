#ifndef NEWMAPPER_QUEUE_H
#define NEWMAPPER_QUEUE_H

#include <iostream>
#include <cstdlib>
#include <cmath>

template <typename T> class Queue {
private:
    T* array;
    int size; //number of used cells
    int capacity; //number of cells to use before reallocating
    int front;
    int rear;
public:
    Queue(int capacity) {
        size = 0;
        this->capacity = capacity;
        array = new T[capacity];
        front = 0;
        rear = -1;
    
}


    ~Queue() {
        delete[] array;
    
}


    void Enqueue(T& data) {
        size++;
        rear++;
        array[rear] = data;
    
}


    void Dequeue() {
        front++;
        size--;
    
}


    T& Peek() {
        return array[front];
    
}


    int Size() {
        return size;
    
}
};

#endif //NEWMAPPER_QUEUE_H
