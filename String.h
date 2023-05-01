#ifndef NEWMAPPER_STRING_H
#define NEWMAPPER_STRING_H

#include <iostream>
#include <cstring>

class String {
private:
    char* array;
    int size;
public:
    String() {
        size = 1;
        array = new char[size];
        array[0] = '\0';
    
}


    explicit String(char* source) {
        if (source == nullptr) {
            size = 1;
            array = new char[1];
            array[0] = '\0';
        
}
        else {
            size = strlen(source) + 1;
            array = new char[size];
            strcpy(array, source);
            array[size - 1] = '\0';
        
}
    
}


    String(const String& source) {
        size = source.size;
        array = new char[size];
        memcpy(array, source.array, size);
    
}


    String(String&& source) noexcept {
        size = source.size;
        array = source.array;
        source.array = nullptr;
    
}


    ~String() {
        delete[] array;
    
}


    [[nodiscard]] int GetLength() const {
        return size;
    
}


    void PushBack(char c) {
        char* temp = new char[size + 1];
        memcpy(temp, array, size);
        temp[size - 1] = c;
        temp[size] = '\0';
        delete[] array;
        array = temp;
        size++;
    
}


    String& operator=(const String& rightString) {
        if (this == &rightString)
            return *this;
        if (size != rightString.size)
            delete[] array;
        size = rightString.size;
        array = new char[size];
        memcpy(array, rightString.array, size);
        return *this;
    
}


    String& operator=(String&& rightString) noexcept {
        if (this == &rightString)
            return *this;
        delete[] array;
        size = rightString.size;
        array = rightString.array;
        rightString.array = nullptr;
        rightString.size = 0;
        return *this;
    
}


    bool operator==(const char* text) const {
        return !strcmp(array, text);
    
}


    bool operator==(String& right) const {
        return !strcmp(array, right.array);
    
}

    bool operator==(const String& right) const {
        return !strcmp(array, right.array);
    
}


    char operator[](int index) const {
        return array[index];
    
}


    [[nodiscard]] char* GetArray() const {
        return array;
    
}


    friend std::ostream& operator<<(std::ostream& os, const String& string) {
        os << string.array;
        return os;
    
}


    friend String operator+(char left, const String& right) {
        int length = right.size + 1;
        char* buffer = new char[length];
        buffer[0] = left;
        memcpy(buffer + 1, right.array, right.size);
        String temp(buffer);
        temp.size = length;
        delete[] buffer;
        return temp;
    
}
};

#endif //NEWMAPPER_STRING_H
