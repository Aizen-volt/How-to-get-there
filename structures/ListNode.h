#ifndef HOW_TO_GET_THERE_LISTNODE_H
#define HOW_TO_GET_THERE_LISTNODE_H

template<typename T>
class ListNode {
public:
    T data;
    ListNode* next;

    explicit ListNode(const T& data) : data(data), next(nullptr) {}
};

#endif //HOW_TO_GET_THERE_LISTNODE_H
