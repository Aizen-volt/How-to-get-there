#ifndef NEWMAPPER_LIST_H
#define NEWMAPPER_LIST_H

#include <iostream>

template<typename T>
class Node {
public:
    T data;
    Node* next;
    explicit Node(T& value) {
        next = nullptr;
        data = value;
    }
};


template<typename T>
class List {
private:
    int linkedListSize;
public:
    Node<T>* head, *tail;

    List() : head(nullptr), tail(nullptr) {
        linkedListSize = 0;
    }


    [[nodiscard]] bool isEmpty() const {
        return head == nullptr;
    }


    [[nodiscard]] int GetSize() const {
        return linkedListSize + 1;
    }


    void PushBack(T& data) {
        linkedListSize++;
        auto* newNode = new Node<T>(data);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = tail->next;
        }
    }


    Node<T>* operator[](int index) const {
        Node<T>* current = head;
        for (int i = 0; i < index; i++)
            current = current->next;
        return current;
    }


    void IncreaseSize() {
        linkedListSize++;
    }
};

#endif //NEWMAPPER_LIST_H