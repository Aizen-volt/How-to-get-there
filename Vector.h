#ifndef NEWMAPPER_VECTOR_H
#define NEWMAPPER_VECTOR_H


#include <iostream>
#include <cmath>

#define CELLS_EXCESS_WHEN_REALLOCATING 40000

template <typename T> class Vector {
private:
    T* array;
    int size; //number of used cells
    int capacity; //number of cells to use before reallocating


    void CheckCapacity() {
        if (size == capacity)
            ChangeCapacity(size + CELLS_EXCESS_WHEN_REALLOCATING);
    
}


    void ChangeCapacity(int target_capacity) {
        T* temp = new T[target_capacity];
        for (int i = 0; i < capacity; i++) {
            temp[i] = array[i];
        
}
        capacity = target_capacity;
        delete[] array;
        array = temp;
    
}
public:
    Vector() {
        size = 1;
        capacity = CELLS_EXCESS_WHEN_REALLOCATING;
        array = new T[capacity];
    
}


    Vector(const Vector<T>& other) {
        size = other.size;
        capacity = other.capacity;
        array = other.array;
    
}


    ~Vector() {
        delete[] array;
    
}


    T& operator[](int index) {
        return array[index];
    
}


    void Push_back(T& data) {
        size++;
        CheckCapacity();
        array[size - 2] = data;
    
}


    void Push_back() {
        size++;
        CheckCapacity();
    
}


    void Pop_back() {
        size--;
        CheckCapacity();
    
}


    [[nodiscard]] int Size() const {
        return size - 1;
    
}

    T* GetArray() const {
        return array;
    
}
};

#endif //NEWMAPPER_VECTOR_H
