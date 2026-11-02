#include "project/heap.h"

#include <algorithm>
#include <stdexcept>

MaxHeap::MaxHeap() = default;

MaxHeap::MaxHeap(const std::vector<int>& values) {
    buildHeap(values);
}

bool MaxHeap::empty() const noexcept {
    return data_.empty();
}

std::size_t MaxHeap::size() const noexcept {
    return data_.size();
}

int MaxHeap::top() const {
    if (empty()) {
        throw std::logic_error("Heap is empty");
    }
    return data_.front();
}

bool MaxHeap::contains(int value) const {
    for (int item : data_) {
        if (item == value) {
            return true;
        }
    }
    return false;
}

void MaxHeap::push(int value) {
    data_.push_back(value);
    heapifyUp(data_.size() - 1);
}

int MaxHeap::pop() {
    if (empty()) {
        throw std::logic_error("Heap is empty");
    }
    const int maximum = data_.front();
    data_.front() = data_.back();
    data_.pop_back();
    if (!empty()) {
        heapifyDown(0);
    }
    return maximum;
}

void MaxHeap::buildHeap(const std::vector<int>& values) {
    data_ = values;
    // Leaves already satisfy heap order. Sift internal nodes bottom-up in O(n).
    for (std::size_t index = data_.size() / 2; index > 0; --index) {
        heapifyDown(index - 1);
    }
}

std::vector<int> MaxHeap::heapSort() {
    // Work on a copy so sorting does not consume or invalidate this heap.
    MaxHeap copy = *this;
    std::vector<int> sorted(size());
    for (std::size_t index = sorted.size(); index > 0; --index) {
        sorted[index - 1] = copy.pop();
    }
    return sorted;
}

std::vector<int> MaxHeap::toVector() const {
    return data_;
}

std::size_t MaxHeap::parentIndex(std::size_t index) {
    if (index == 0) {
        return 0;
    }
    return (index - 1) / 2;
}

std::size_t MaxHeap::leftChildIndex(std::size_t index) {
    return (2 * index) + 1;
}

std::size_t MaxHeap::rightChildIndex(std::size_t index) {
    return (2 * index) + 2;
}

void MaxHeap::heapifyUp(std::size_t index) {
    while (index > 0) {
        const std::size_t parent = parentIndex(index);
        if (data_[parent] >= data_[index]) {
            break;
        }
        swap(data_[parent], data_[index]);
        index = parent;
    }
}

void MaxHeap::heapifyDown(std::size_t index) {
    // Indices before size()/2 are exactly the nodes with at least one child.
    while (index < data_.size() / 2) {
        std::size_t largerChild = leftChildIndex(index);
        const std::size_t right = rightChildIndex(index);
        if (right < data_.size() && data_[right] > data_[largerChild]) {
            largerChild = right;
        }
        if (data_[index] >= data_[largerChild]) {
            break;
        }
        swap(data_[index], data_[largerChild]);
        index = largerChild;
    }
}

void MaxHeap::swap(int& a, int& b) {
    std::swap(a, b);
}

bool MaxHeap::isValidHeap() const {
    for (std::size_t i = 1; i < data_.size(); ++i) {
        if (data_[parentIndex(i)] < data_[i]) {
            return false;
        }
    }
    return true;
}
