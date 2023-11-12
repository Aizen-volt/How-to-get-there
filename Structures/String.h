#ifndef HOW_TO_GET_THERE_STRING_H
#define HOW_TO_GET_THERE_STRING_H

#include <iostream>
#include <cstring>
#include <stdexcept>

class String {

private:
    char* array;
    size_t size;


    void checkStringEmpty() const {
        if (size == 1) {
            throw std::runtime_error("Error: String empty!");
        }
    }


    void checkIndexInBound(size_t index) const {
        if (index >= size) {
            throw std::runtime_error("Error: Index out of bound!");
        }
    }

public:
    String() : size(1) {
        array = new char[size];
        array[0] = '\0';
    }


    ~String() {
        delete[] array;
    }


    String(const char* str) {
        if (!str) {
            size = 1;
            array = new char[size];
            array[0] = '\0';
            return;
        }

        size = strlen(str) + 1;
        array = new char[size];

        strcpy(array, str);
        array[size - 1] = '\0';
    }


    String(const String& other) {
        size = other.size;
        array = new char[size];

        strcpy(array, other.array);
        array[size - 1] = '\0';
    }


    String(String&& other) noexcept {
        size = other.size;
        array = other.array;

        other.size = 0;
        other.array = nullptr;
    }


    String& operator=(const char* str) {
        if (!str) {
            size = 1;
            array = new char[size];
            array[0] = '\0';

            return *this;
        }

        size = strlen(str) + 1;
        array = new char[size];

        strcpy(array, str);
        array[size - 1] = '\0';

        return *this;
    }


    String& operator=(const String& other) {
        if (this == &other) {
            return *this;
        }

        delete[] array;

        size = other.size;
        array = new char[size];

        strcpy(array, other.array);
        array[size - 1] = '\0';
        return *this;
    }


    String& operator=(String&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        delete[] array;

        size = other.size;
        array = other.array;

        other.size = 0;
        other.array = nullptr;

        return *this;
    }


    void clear() {
        delete[] array;

        size = 1;
        array = new char[size];
        array[0] = '\0';
    }


    [[nodiscard]] bool empty() const {
        return size == 1;
    }


    [[nodiscard]] size_t getSize() const {
        return size;
    }


    void pushBack(char c) {
        char* newArray = new char[size + 1];
        strcpy(newArray, array);
        newArray[size - 1] = c;
        newArray[size] = '\0';

        delete[] array;
        array = newArray;
        size++;
    }


    void pushFront(char c) {
        char* newArray = new char[size + 1];
        newArray[0] = c;
        strcpy(newArray + 1, array);
        newArray[size] = '\0';

        delete[] array;
        array = newArray;
        size++;
    }


    void push(size_t index, char c) {
        checkIndexInBound(index);

        char* newArray = new char[size + 1];
        strncpy(newArray, array, index);
        newArray[index] = c;
        strcpy(newArray + index + 1, array + index);
        newArray[size + 1] = '\0';

        delete[] array;
        array = newArray;
        size++;
    }



    void popBack() {
        checkStringEmpty();

        char* newArray = new char[size - 1];
        strncpy(newArray, array, size - 1);
        newArray[size - 2] = '\0';

        delete[] array;
        array = newArray;
        size--;
    }


    void popFront() {
        checkStringEmpty();

        char* newArray = new char[size - 1];
        strcpy(newArray, array + 1);
        newArray[size - 2] = '\0';

        delete[] array;
        array = newArray;
        size--;
    }



    void pop(size_t index) {
        checkStringEmpty();
        checkIndexInBound(index);

        char* newArray = new char[size - 1];
        strncpy(newArray, array, index);
        strcpy(newArray + index, array + index + 1);
        newArray[size - 2] = '\0';

        delete[] array;
        array = newArray;
        size--;
    }


    bool operator==(const char* str) const {
        return !strcmp(array, str);
    }


    bool operator==(const String& other) const {
        return !strcmp(array, other.array);
    }


    bool operator==(String&& other) const {
        return !strcmp(array, other.array);
    }


    char operator[](size_t index) const {
        checkIndexInBound(index);
        return array[index];
    }



    String operator+(const String& other) const {
        String result;

        result.size = size + other.size - 1;
        result.array = new char[result.size];

        strcpy(result.array, array);
        strcat(result.array, other.array);

        return result;
    }

    String& operator+=(const String& other) {
        size_t newSize = size + other.size - 1;
        char* newArray = new char[newSize];

        strcpy(newArray, array);
        strcat(newArray, other.array);

        delete[] array;
        array = newArray;
        size = newSize;

        return *this;
    }


    friend std::ostream& operator<<(std::ostream& os, const String& string) {
        os << string.array;
        return os;
    }


    friend std::istream& operator>>(std::istream& is, String& str) {
        char buffer[3000];
        is >> buffer;
        str = String(buffer);
        return is;
    }
};

#endif //HOW_TO_GET_THERE_STRING_H
