#ifndef HOW_TO_GET_THERE_LIST_H
#define HOW_TO_GET_THERE_LIST_H

#include <iostream>
#include <initializer_list>

#include "ListNode.h"

template<typename T>
class List {

private:
    size_t size = 0;
    ListNode<T>* head;
    ListNode<T>* tail;


    void sort(ListNode<T>** headRef, ListNode<T>** tailRef) {
        ListNode<T>* a;
        ListNode<T>* b;

        if (!*headRef || !(*headRef)->next) {
            return;
        }

        split(*headRef, &a, &b);
        sort(&a, tailRef);
        sort(&b, tailRef);
        *headRef = mergeSorted(a, b);

        *tailRef = *headRef;
        while ((*tailRef)->next) {
            *tailRef = (*tailRef)->next;
        }
    }


    void split(ListNode<T>* source, ListNode<T>** front, ListNode<T>** back) {
        ListNode<T>* fast = source->next;
        ListNode<T>* slow = source;

        while (fast) {
            fast = fast->next;
            if (fast) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *front = source;
        *back = slow->next;
        slow->next = nullptr;
    }


    ListNode<T>* mergeSorted(ListNode<T>* a, ListNode<T>* b) {
        ListNode<T>* result;

        if (!a) {
            return b;
        }
        if (!b) {
            return a;
        }

        if (a->data <= b->data) {
            result = a;
            result->next = mergeSorted(a->next, b);
        }
        else {
            result = b;
            result->next = mergeSorted(a, b->next);
        }
        return result;
    }


    void checkIndexInBound(size_t index) const {
        if (index >= size) {
            throw std::runtime_error("Error: Index out of bound!");
        }
    }


    void checkListEmpty() const {
        if (empty()) {
            throw std::runtime_error("Error: List empty!");
        }
    }


public:
    List() : head(nullptr), tail(nullptr) {}


    List(const List<T>& other) {
        head = tail = nullptr;
        size = 0;

        ListNode<T>* current = other.head;
        while (current) {
            pushBack(current->data);
            current = current->next;
        }
    }


    List(List<T>&& other) noexcept {
        head = other.head;
        tail = other.tail;
        size = other.size;

        other.head = other.tail = nullptr;
        other.size = 0;
    }


    List(std::initializer_list<T> ilist) {
        head = tail = nullptr;
        size = 0;

        for (const auto& element : ilist) {
            pushBack(element);
        }
    }


    List<T>& operator=(const List<T>& other) {
        if (this == &other) {
            return *this;
        }

        clear();
        auto* current = other.head;

        while (current) {
            pushBack(current->data);
            current = current->next;
        }
        return *this;
    }


    List<T>& operator=(List<T>&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        head = other.head;
        tail = other.tail;
        size = other.size;

        other.head = other.tail = nullptr;
        other.size = 0;

        return *this;
    }


    List<T>& operator=(std::initializer_list<T> ilist) {
        clear();

        for (const auto& element : ilist) {
            pushBack(element);
        }
        return *this;
    }


    void sort() {
        sort(&head, &tail);
    }


    void reverse() {
        auto* current = head;
        ListNode<T>* prev = nullptr;
        ListNode<T>* next;

        while (current) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;

        tail = head;
        while (tail && tail->next) {
            tail = tail->next;
        }
    }


    void clear() {
        auto* current = head;
        ListNode<T>* prev;

        while (current) {
            prev = current;
            current = current->next;
            delete prev;
        }

        head = nullptr;
    }


    size_t find(const T& data) const {
        auto* current = head;
        size_t index = 0;

        while (current) {
            if (current->data == data) {
                return index;
            }
            current = current->next;
            index++;
        }
        return size + 1;
    }


    T& front() const {
        checkListEmpty();
        return head->data;
    }


    T& back() const {
        checkListEmpty();
        return tail->data;
    }


    [[nodiscard]] bool empty() const {
        return head == nullptr;
    }


    [[nodiscard]] size_t getSize() const {
        return size;
    }


    void pushFront(const T& data) {
        auto* newNode = new ListNode<T>(data);

        newNode->next = head;
        head = newNode;

        if (!tail) {
            tail = head;
        }

        size++;
    }


    void pushBack(const T& data) {
        auto* newNode = new ListNode<T>(data);

        if (empty()) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = tail->next;
        }
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

        auto* newNode = new ListNode<T>(data);
        auto* current = head;

        for (size_t i = 0; i < index - 1; i++) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;

        size++;
    }


    void popFront() {
        checkListEmpty();

        auto* temp = head;
        head = head->next;

        delete temp;
        size--;
    }


    void popBack() {
        checkListEmpty();

        auto* current = head;
        auto* prev = head;

        while (current->next) {
            prev = current;
            current = current->next;
        }
        prev->next = nullptr;

        delete current;
        size--;
    }


    void pop(size_t index) {
        checkListEmpty();
        checkIndexInBound(index);

        if (index == 0) {
            popFront();
            return;
        }
        if (index == size - 1) {
            popBack();
            return;
        }

        auto* current = head;
        auto* prev = head;

        for (size_t i = 0; i < index - 1; i++) {
            prev = current;
            current = current->next;
        }

        prev->next = current->next;
        delete current;
        size--;
    }


    ListNode<T>* operator[](size_t index) const {
        checkIndexInBound(index);

        auto* current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        return current;
    }


    friend std::ostream& operator<<(std::ostream& os, const List<T>& list) {
        auto* current = list.head;

        os << "[";

        while (current) {
            os << current->data;
            current = current->next;
            if (current) {
                os << ", ";
            }
        }

        os << "]";
        return os;
    }
};

#endif //HOW_TO_GET_THERE_LIST_H
