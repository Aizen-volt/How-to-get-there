#ifndef NEWMAPPER_PRIORITYQUEUE_H
#define NEWMAPPER_PRIORITYQUEUE_H


typedef struct Pair {
    int distance, index;
    bool operator>(Pair& other) {
        return this->distance > other.distance;
    
}
    bool operator<(Pair& other) {
        return this->distance < other.distance;
    
}
} Pair;


template <typename T>
class PriorityQueue {
private:
    Vector<T> heap;

    int Parent(int i) {
        return (i - 1) / 2;
    
}

    int LeftChild(int i) {
        return 2 * i + 1;
    
}

    int RightChild(int i) {
        return 2 * i + 2;
    
}

    void ShiftUp(int i) {
        if (i > 0 && heap[Parent(i)] > heap[i]) {
            T temp = heap[Parent(i)];
            heap[Parent(i)] = heap[i];
            heap[i] = temp;
            ShiftUp(Parent(i));
        
}
    
}

    void ShiftDown(int i) {
        int min = i;
        if (LeftChild(i) < heap.Size() - 1 && heap[LeftChild(i)] < heap[min])
            min = LeftChild(i);
        if (RightChild(i) < heap.Size() - 1 && heap[RightChild(i)] < heap[min])
            min = RightChild(i);
        if (i != min) {
            T temp = heap[min];
            heap[min] = heap[i];
            heap[i] = temp;
            ShiftDown(min);
        
}
    
}

public:
    void Insert(T& data) {
        heap.Push_back(data);
        ShiftUp(heap.Size() - 1);
    
}

    T& Top() {
        return heap[0];
    
}

    void Remove() {
        heap[0] = heap[heap.Size() - 1];
        heap.Pop_back();
        ShiftDown(0);
    
}

    [[nodiscard]] bool Empty() const {
        return heap.Size() == 0;
    
}
};

#endif //NEWMAPPER_PRIORITYQUEUE_H
