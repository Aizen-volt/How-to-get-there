#ifndef HOW_TO_GET_THERE_VECTOR_H
#define HOW_TO_GET_THERE_VECTOR_H

#include <iostream>
#include <initializer_list>
#include <cmath>

template<typename T>
class Vector {

private:
    T* array;
    size_t maxCapacity;
    size_t size;


    void sort(size_t a, size_t b) {
        if (a >= b) {
            return;
        }

        size_t mid = a + (b - a) / 2;

        sort(a, mid);
        sort(mid + 1, b);
        mergeSorted(a, mid, b);
    }


    void mergeSorted(size_t a, size_t mid, size_t b) {
        size_t arrayOne = mid - a + 1;
        size_t arrayTwo = b - mid;

        T* left = new T[arrayOne];
        T* right = new T[arrayTwo];

        for (size_t i = 0; i < arrayOne; i++) {
            left[i] = array[a + i];
        }
        for (size_t i = 0; i < arrayTwo; i++) {
            right[i] = array[mid + i + 1];
        }

        int i = 0;
        int j = 0;
        int k = a;

        while (i < arrayOne && j < arrayTwo) {
            if (left[i] <= right[j]) {
                array[k] = left[i];
                i++;
            }
            else {
                array[k] = right[j];
                j++;
            }
            k++;
        }

        while (i < arrayOne) {
            array[k] = left[i];
            i++;
            k++;
        }

        while (j < arrayTwo) {
            array[k] = right[j];
            j++;
            k++;
        }

        delete[] left;
        delete[] right;
    }


    void checkIndexInBound(size_t index) const {
        if (index >= size) {
            throw  std::runtime_error("Error: Index out of bound!");
        }
    }


    void checkVectorEmpty() const {
        if (empty()) {
            throw std::runtime_error("Error: Vector empty!");
        }
    }


    void checkCapacity() {
        if (size == maxCapacity) {
            T* temp = new T[2 * maxCapacity];

            for (size_t i = 0; i < maxCapacity; i++) {
                temp[i] = array[i];
            }

            delete[] array;
            maxCapacity *= 2;
            array = temp;
        }
    }

public:
    Vector() : maxCapacity(1), size(0) {
        array = new T[maxCapacity];
    }


    explicit Vector(size_t size) : size(size), maxCapacity(size) {
        array = new T[maxCapacity];
    }


    ~Vector() {
        delete[] array;
    }


    Vector(const Vector<T>& other) {
        maxCapacity = other.maxCapacity;
        size = other.size;
        array = new T[maxCapacity];

        for (size_t i = 0; i < other.size; i++) {
            array[i] = other.array[i];
        }
    }


    Vector(Vector<T>&& other) noexcept {
        array = other.array;
        maxCapacity = other.maxCapacity;
        size = other.size;

        other.maxCapacity = 1;
        other.size = 0;
        other.array = new T[other.maxCapacity];
    }


    Vector(std::initializer_list<T> ilist) {
        size = ilist.size();
        maxCapacity = pow(2, ceil(log2(size)));
        array = new T[maxCapacity];

        size_t i = 0;
        for (const auto& element : ilist) {
            array[i] = element;
            i++;
        }
    }


    Vector<T>& operator=(const Vector<T>& other) {
        if (this == &other) {
            return *this;
        }

        delete[] array;
        maxCapacity = other.maxCapacity;
        size = other.size;
        array = new T[maxCapacity];

        for (size_t i = 0; i < other.size; i++) {
            array[i] = other.array[i];
        }
        return *this;
    }


    Vector<T>& operator=(Vector<T>&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        delete[] array;
        array = other.array;
        maxCapacity = other.maxCapacity;
        size = other.size;

        other.maxCapacity = 1;
        other.size = 0;
        other.array = new T[other.maxCapacity];

        return *this;
    }


    Vector<T>& operator=(std::initializer_list<T> ilist) {
        delete[] array;
        size = ilist.size();
        maxCapacity = ceil(log2(ilist.size()));
        array = new T[maxCapacity];

        size_t i = 0;
        for (const auto& element : ilist) {
            array[i] = element;
            i++;
        }
        return *this;
    }


    void sort() {
        sort(0, size - 1);
    }


    void reverse() {
        size_t left = 0;
        size_t right = size - 1;

        while (left < right) {
            std::swap(array[left], array[right]);
            left++;
            right--;
        }
    }


    void clear() {
        delete[] array;
        maxCapacity = 1;
        size = 0;
        array = new T[maxCapacity];
    }


    size_t find(const T& data) const {
        for (size_t i = 0; i < size; i++) {
            if (array[i] == data) {
                return i;
            }
        }
        return size + 1;
    }


    T& front() const {
        checkVectorEmpty();
        return array[0];
    }


    T& back() const {
        checkVectorEmpty();
        return array[size - 1];
    }


    [[nodiscard]] bool empty() const {
        return size == 0;
    }


    [[nodiscard]] size_t getSize() const {
        return size;
    }


    [[nodiscard]] size_t getCapacity() const {
        return maxCapacity;
    }


    void pushFront(const T& data) {
        checkCapacity();

        for (size_t i = size; i >= 1; i--) {
            array[i] = array[i - 1];
        }
        array[0] = data;
    }


    void pushBack(const T& data) {
        checkCapacity();

        array[size] = data;
        size++;
    }


    void push(const T& data, size_t index) {
        checkIndexInBound(index);

        if (index == 0) {
            pushFront(data);
            return;
        }
        if (index == size - 1) {
            pushBack(data);
            return;
        }

        checkCapacity();

        for (size_t i = size; i >= index + 1; i--) {
            array[i] = array[i - 1];
        }
        array[index] = data;
        size++;
    }


    void popFront() {
        checkVectorEmpty();

        for (size_t i = 1; i < size; i++) {
            array[i - 1] = array[i];
        }
        size--;
    }


    void popBack() {
        checkVectorEmpty();
        size--;
    }


    void pop(size_t index) {
        checkVectorEmpty();
        checkIndexInBound(index);

        if (index == 0) {
            popFront();
            return;
        }
        if (index == size - 1) {
            popBack();
            return;
        }

        for (size_t i = index + 1; i < size; i++) {
            array[i - 1] = array[i];
        }
        size--;
    }


    T& operator[](size_t index) const {
        checkIndexInBound(index);
        return array[index];
    }


    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vector) {
        os << "[";
        for (size_t i = 0; i < vector.size; i++) {
            os << vector.array[i];
            if (i != vector.size - 1) {
                os << ", ";
            }
        }
        os << "]";

        return os;
    }
};

#endif //HOW_TO_GET_THERE_VECTOR_H
