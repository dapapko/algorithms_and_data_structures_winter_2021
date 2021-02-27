//
// Created by drford on 14.02.2021.
//

#ifndef TIGER_LAB2_STACK_H
#define TIGER_LAB2_STACK_H

#include <stdexcept>

template <typename T>
class Node {
public:
    T value;
    Node* ptr;
    Node(T data) {
        this->value = data;
        this->ptr = nullptr;
    }

};

template <typename T>
class Stack {
    Node<T>* head;
public:
    Stack() : head(nullptr) {}

    bool empty() {
        return this->head == nullptr;
    }

    T peek() {
        if (empty()) throw std::length_error("Getting head of empty stack");
        return this->head->value;
    }

    void push(T value) {
        auto* item = new Node<T>(value);
        item->value = value;
        item->ptr = head;
        head = item;
    }



    T pop() {
        if (empty()) {
            throw std::length_error("Pop from empty stack");
        }
        T temp = head->value;
        Node<T>* pv = head;
        head = head->ptr;
        delete pv;
        return temp;
    }

    ~Stack() {
        while (head) {
            Node<T>* node = head;
            head = head->ptr;
            delete node;
        }
    }
};
#endif //TIGER_LAB2_STACK_H