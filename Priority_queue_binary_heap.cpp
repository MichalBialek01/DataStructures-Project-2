#include <iostream>
#include <stdexcept>

template<typename T>
class PriorityQueue {
private:
    std::pair<T, int>* heap;
    int capacity;
    int size;

    void expandHeap() {
        int newCapacity = capacity * 2;
        std::pair<T, int>* newHeap = new std::pair<T, int>[newCapacity];
        for (int i = 0; i < size; i++) {
            newHeap[i] = heap[i];
        }
        delete[] heap;
        heap = newHeap;
        capacity = newCapacity;
    }

    void heapifyDown(int index) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left].second > heap[largest].second) {
            largest = left;
        }
        if (right < size && heap[right].second > heap[largest].second) {
            largest = right;
        }
        if (largest != index) {
            std::swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

    void heapifyUp(int index) {
        while (index != 0 && heap[(index - 1) / 2].second < heap[index].second) {
            std::swap(heap[(index - 1) / 2], heap[index]);
            index = (index - 1) / 2;
        }
    }

public:
    PriorityQueue() : capacity(10), size(0) {
        heap = new std::pair<T, int>[capacity];
    }

    ~PriorityQueue() {
        delete[] heap;
    }

    void insert(T item, int priority) {
        if (size == capacity) {
            expandHeap();
        }
        heap[size] = {item, priority};
        heapifyUp(size);
        size++;
    }

    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Heap is empty");
        }
        T item = heap[0].first;
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return item;
    }

    T peek() {
        if (isEmpty()) {
            throw std::runtime_error("Heap is empty");
        }
        return heap[0].first;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void deleteElement(T item, int priority) {
        for (int i = 0; i < size; i++) {
            if (heap[i].first == item && heap[i].second == priority) {
                heap[i] = heap[size - 1];
                size--;
                heapifyUp(i);
                heapifyDown(i);
                return;
            }
        }
    }

    void deleteElement() {
        if (!isEmpty()) {
            pop();
        }
    }
};

int main() {
    PriorityQueue<std::string> queue;
    queue.insert("task1", 3);
    queue.insert("task2", 2);
    queue.insert("task3", 1);
    queue.insert("task4", 4);

    std::cout << "Peek: " << queue.peek() << std::endl;
    std::cout << "Pop: " << queue.pop() << std::endl;
    std::cout << "After pop, Peek: " << queue.peek() << std::endl;

    queue.deleteElement("task2", 2);
    std::cout << "After deleting task2, Peek: " << queue.peek() << std::endl;

    return 0;
}