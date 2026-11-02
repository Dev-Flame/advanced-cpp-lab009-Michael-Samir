#include "project/heap.h"

#include <iostream>

int main() {
    MaxHeap heap({4, 10, 3, 5, 1, 7, 8, 2});
    heap.push(12);
    std::cout << "Maximum: " << heap.top()
              << "\nRemoved: " << heap.pop()
              << "\nSize: " << heap.size() << "\nSorted:";
    for (int value : heap.heapSort()) {
        std::cout << ' ' << value;
    }
    std::cout << '\n';
}
