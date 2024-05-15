#include <iostream>
#include <stdexcept>
#include <chrono>
#include <random>
#include "BinaryHeap.cpp"
#include "RedBlackTree.cpp"
#include "SortingList.cpp"

using namespace std;


template<typename T>
void testPriorityQueueBH(int numberOfElements) {
    PriorityQueueBH<T> pq;

    // Pomiar czasu dla operacji insert
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numberOfElements; i++) {
        pq.insert(static_cast<T>(i), i);  // Używanie sekwencyjnych wartości zamiast losowych
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto durationInsert = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time for " << numberOfElements << " inserts: " << durationInsert.count() << " ms" << std::endl;

    // Pomiar czasu dla operacji peek
    start = std::chrono::high_resolution_clock::now();
    pq.peek();
    stop = std::chrono::high_resolution_clock::now();
    auto durationPeek = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time for peek: " << durationPeek.count() << " ms" << std::endl;

    // Pomiar czasu dla operacji pop
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numberOfElements; i++) {
        pq.pop();
    }
    stop = std::chrono::high_resolution_clock::now();
    auto durationPop = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time for " << numberOfElements << " pops: " << durationPop.count() << " ms" << std::endl;
}


template<typename T>
void performTestRBT(PriorityQueueRBT<T>& pq, int count) {
    cout << "Testing with " << count << " elements:" << endl;

    // Insertion test
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) {
        T data = static_cast<T>(i + 1);  // Sekwencyjne wartości zamiast losowych
        int priority = i + 1;           // Sekwencyjne priorytety
        pq.insert(data, priority);
    }
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = stop - start;
    cout << "Insert time: " << elapsed.count() << " ms\n";

    // Peek test
    start = chrono::high_resolution_clock::now();
    pq.peek();
    stop = chrono::high_resolution_clock::now();
    elapsed = stop - start;
    cout << "Peek time: " << elapsed.count() << " ms\n";

    // Pop test
    start = chrono::high_resolution_clock::now();
    while (!pq.isEmpty()) {
        pq.pop();
    }
    stop = chrono::high_resolution_clock::now();
    elapsed = stop - start;
    cout << "Pop time: " << elapsed.count() << " ms\n";
}

//SLL
template<typename T>
void performTestSLL(PriorityQueueSLL<T>& pq, int count) {
    cout << "Testing with " << count << " elements of type " << typeid(T).name() << ":" << endl;

    // Insertion test
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) {
        T data = static_cast<T>(1 + i * 0.1);  // Proste generowanie danych
        int priority = i + 1;                 // Sekwencyjne priorytety
        pq.insert(data, priority);
    }
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = stop - start;
    cout << "Insert time: " << elapsed.count() << " ms\n";

    // Peek test
    start = chrono::high_resolution_clock::now();
    try {
        auto item = pq.peek();  // Tylko dla pomiaru czasu
    } catch (const runtime_error& e) {
        cout << "Peek error: " << e.what() << endl;
    }
    stop = chrono::high_resolution_clock::now();
    elapsed = stop - start;
    cout << "Peek time: " << elapsed.count() << " ms\n";

    // Pop test
    start = chrono::high_resolution_clock::now();
    while (!pq.isEmpty()) {
        try {
            auto item = pq.pop();
        } catch (const runtime_error& e) {
            cout << "Pop error: " << e.what() << endl;
            break;
        }
    }
    stop = chrono::high_resolution_clock::now();
    elapsed = stop - start;
    cout << "Pop time: " << elapsed.count() << " ms\n";
}

int main() {
    vector<int> counts = {1000, 10000, 100000};

    //BH
    cout<<"Testing BinaryHeap priorityQueue"<<endl;
    for (int size : counts) {
        cout << "Integers:\n";
        testPriorityQueueBH<int>(size);

        cout << "Floats:\n";
        testPriorityQueueBH<float>(size);

        cout << "Doubles:\n";
        testPriorityQueueBH<double>(size);
    }

    //RBT
    cout<<"Testing RedBlackTree priorityQueue"<<endl;
    cout<<"Testing BinaryHeap"<<endl;
    PriorityQueueRBT<int> pqRBTInt;
    PriorityQueueRBT<float> pqRBTFloat;
    PriorityQueueRBT<double> pqRBTDouble;


    for (int count : counts) {
        cout << "Integers:\n";
        performTestRBT(pqRBTInt, count);
        cout << "Floats:\n";
        performTestRBT(pqRBTFloat, count);
        cout << "Doubles:\n";
        performTestRBT(pqRBTDouble, count);
    }

    ///SLL
    cout<<"Testing SingleLinkedList priorityQueue"<<endl;
    PriorityQueueSLL<int> pqSLLInt;
    PriorityQueueSLL<float> pqSLLFloat;
    PriorityQueueSLL<double> pqSLLDouble;

    for (int count : counts) {
        cout << "Integers:\n";
        performTestSLL(pqSLLInt, count);
        cout << "Floats:\n";
        performTestSLL(pqSLLFloat, count);
        cout << "Doubles:\n";
        performTestSLL(pqSLLDouble, count);
    }






    return 0;


}
