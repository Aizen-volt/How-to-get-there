#ifndef CITY_MAPPER_VECTOR_H
#define CITY_MAPPER_VECTOR_H

#include <iostream>
#include <cstdlib>
#include <windows.h>

#define CELLS_EXCESS_WHEN_REALLOCATING 8

template <typename T> class Vector {
private:
    T* array;
    int size; //number of used cells
    int capacity; //number of cells to use before reallocating


    void CheckCapacity() {
        if (size == capacity)
            ChangeCapacity(size + CELLS_EXCESS_WHEN_REALLOCATING);
        else if (size == capacity - CELLS_EXCESS_WHEN_REALLOCATING)
            ChangeCapacity(size);
    }


    void ChangeCapacity(int target_capacity) {
        T* temp = new T[target_capacity];
        for (int i = 0; i < (target_capacity > capacity ? capacity : target_capacity); i++) {
            temp[i] = array[i];
        }
        capacity = target_capacity;
        delete[] array;
        array = temp;
    }


    void IndexValid(int index) {
        if (index < 0 || index >= size) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 0x04);
            std::cerr << "Could not get access to restricted memory!";
            exit(1);
        }
    }
public:
    Vector() {
        size = 1;
        capacity = CELLS_EXCESS_WHEN_REALLOCATING;
        array = new T[capacity];
    }


    Vector(int size) {
        this->size = size;
        capacity = int(size / CELLS_EXCESS_WHEN_REALLOCATING) * CELLS_EXCESS_WHEN_REALLOCATING;
        array = new T[capacity];
    }


    ~Vector() {
        delete[] array;
    }


    T& operator[](int index) {
        IndexValid(index);
        return array[index];
    }


    void Push_back(T data) {
        size++;
        CheckCapacity();
        array[size - 2] = data;
    }


    void Push(T data, int index) {
        IndexValid(index);

        if (index == size - 1) {
            Push_back(data);
            return;
        }

        size++;
        CheckCapacity();
        for (int i = size - 1; i > index; i--) {
            T temp = array[i - 1];
            array[i - 1] = array[i];
            array[i] = temp;
        }
        array[index] = data;
    }


    void Pop_back() {
        size--;
        CheckCapacity();
    }


    [[nodiscard]] int Size() const {
        return size;
    }


    friend std::ostream& operator<<(std::ostream& os, const Vector& vector) {
        os << "Capacity: " << vector.capacity << '\n';
        for (int i = 0; i < vector.size - 1; i++) {
            os << vector.array[i] << ' ';
        }
        os << '\n';
        return os;
    }
};

#endif //CITY_MAPPER_VECTOR_H
