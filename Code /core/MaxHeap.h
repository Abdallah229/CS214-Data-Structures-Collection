#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <utility>
#include <stdexcept>
#include <iostream>

/**
 * @file MaxHeap.h
 * @brief Generic Max Heap data structure
 * 
 * Reusable template-based Max Heap implementation. Replaces the hardcoded
 * Patient-based heap found in PatientPriorityQueue.cpp.
 * Relies on operator< or a custom comparator for ordering.
 */

template <typename T>
class MaxHeap {
private:
    T* arr;
    int size;
    int capacity;

    void max_heapify(int i, int n) {
        int left = 2 * i + 1;
        int right = left + 1;
        int largest = i;

        if (left < n && arr[largest] < arr[left]) {
            largest = left;
        }
        if (right < n && arr[largest] < arr[right]) {
            largest = right;
        }

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            max_heapify(largest, n);
        }
    }

    void build_max_heap(int n) {
        for (int i = (n / 2) - 1; i >= 0; i--) {
            max_heapify(i, n);
        }
    }

    void resize(int newCapacity) {
        T* newArr = new T[newCapacity];
        for (int i = 0; i < this->size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
    }

public:
    MaxHeap() : size(0), capacity(4) {
        arr = new T[capacity];
    }

    // Disable copy for simplicity, or implement Rule of Three
    MaxHeap(const MaxHeap&) = delete;
    MaxHeap& operator=(const MaxHeap&) = delete;

    void insert(const T& item) {
        if (size == capacity) {
            resize(2 * capacity);
        }
        arr[size] = item;
        size++;
        
        // Re-heapify upwards
        int current = size - 1;
        while (current > 0) {
            int parent = (current - 1) / 2;
            if (arr[parent] < arr[current]) {
                std::swap(arr[parent], arr[current]);
                current = parent;
            } else {
                break;
            }
        }
    }

    T extract_max() {
        if (size == 0) {
            throw std::out_of_range("Heap is empty");
        }
        T max_val = arr[0];
        arr[0] = arr[size - 1];
        size--;
        max_heapify(0, size);
        return max_val;
    }

    T peek() const {
        if (size == 0) {
            throw std::out_of_range("Heap is empty");
        }
        return arr[0];
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

    // Allows running in-place heap sort logic (modifies the internal array)
    void heap_sort() {
        build_max_heap(size);
        for (int i = size - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);
            max_heapify(0, i);
        }
        // Reverse to descending if needed based on original logic
        for (int i = 0; i < size / 2; i++) {
            std::swap(arr[i], arr[size - i - 1]);
        }
    }

    const T* getArray() const {
        return arr;
    }

    ~MaxHeap() {
        delete[] arr;
    }
};

#endif // MAX_HEAP_H
