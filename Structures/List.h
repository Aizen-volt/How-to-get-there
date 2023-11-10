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
    int size;
public:
    Node<T>* head;
    Node<T>* tail;

    List() : head(nullptr), tail(nullptr), size(0) {}


    [[nodiscard]] bool isEmpty() const {
        return head == nullptr;
    }


    [[nodiscard]] int GetSize() const {
        return size + 1;
    }


    void PushBack(T& data) {
        size++;
        Node<T>* newNode = new Node<T>(data);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = tail->next;
        }
    }


    Node<T>* Find(T& data) const {
        Node<T>* current = head;
        while (current) {
            if (current.
        }
    }


    Node<T>* operator[](int index) const {
        Node<T>* current = head;
        for (int i = 0; i < index; i++)
            current = current->next;
        return current;
    }
};

#endif //NEWMAPPER_LIST_H