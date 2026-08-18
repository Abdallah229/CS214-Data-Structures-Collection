#ifndef STACK_H
#define STACK_H

#include <stdexcept>

/**
 * @file Stack.h
 * @brief Generic Stack data structure
 * 
 * Reusable template-based Stack implementation. Replaces the hardcoded
 * string-based stack found in BrowserHistoryManager.cpp.
 */

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* top_node;

public:
    Stack() : top_node(nullptr) {}

    // Copy constructor
    Stack(const Stack& other) : top_node(nullptr) {
        if (other.isEmpty()) return;

        Node* otherCurrent = other.top_node;
        this->top_node = new Node(otherCurrent->data);
        Node* current = this->top_node;
        otherCurrent = otherCurrent->next;

        while (otherCurrent != nullptr) {
            current->next = new Node(otherCurrent->data);
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
    }

    // Assignment operator to follow Rule of Three
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            clear();
            if (!other.isEmpty()) {
                Node* otherCurrent = other.top_node;
                this->top_node = new Node(otherCurrent->data);
                Node* current = this->top_node;
                otherCurrent = otherCurrent->next;

                while (otherCurrent != nullptr) {
                    current->next = new Node(otherCurrent->data);
                    current = current->next;
                    otherCurrent = otherCurrent->next;
                }
            }
        }
        return *this;
    }

    void push(const T& item) {
        Node* newElement = new Node(item);
        newElement->next = top_node;
        top_node = newElement;
    }

    T pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        T item = top_node->data;
        Node* temp = top_node;
        top_node = top_node->next;
        delete temp;
        return item;
    }
    
    T peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return top_node->data;
    }

    bool isEmpty() const {
        return top_node == nullptr;
    }

    void clear() {
        while (top_node != nullptr) {
            Node* temp = top_node;
            top_node = top_node->next;
            delete temp;
        }
    }

    ~Stack() {
        clear();
    }
};

#endif // STACK_H
