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

    // Inicjalizacja generatora liczb losowych
    default_random_engine generator;
    uniform_int_distribution<int> distribution(1, 1000000);

    // Pomiar czasu dla operacji insert
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < numberOfElements; i++) {
        pq.insert(static_cast<T>(distribution(generator)), distribution(generator));
    }
    auto stop = chrono::high_resolution_clock::now();
    auto durationInsert = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Time for " << numberOfElements << " inserts: " << durationInsert.count() << " ms" << endl;

    // Pomiar czasu dla operacji peek
    start = chrono::high_resolution_clock::now();
    pq.peek();
    stop = chrono::high_resolution_clock::now();
    auto durationPeek = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Time for peek: " << durationPeek.count() << " ms" << endl;

    // Pomiar czasu dla operacji pop
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < numberOfElements; i++) {
        pq.pop();
    }
    stop = chrono::high_resolution_clock::now();
    auto durationPop = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Time for " << numberOfElements << " pops: " << durationPop.count() << " ms" << endl;
}

template<typename T>
void performTest(PriorityQueueRBT<T>& pq, int count) {
    default_random_engine generator;
    uniform_int_distribution<int> priorityDistribution(1, 1000000);
    uniform_real_distribution<double> dataDistribution(1.0, 1000000.0);

    cout << "Testing with " << count << " elements:" << endl;

    // Insertion test
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) {
        T data = static_cast<T>(dataDistribution(generator));
        int priority = priorityDistribution(generator);
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
void performTest(PriorityQueueSLL<T>& pq, int count) {
    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> priorityDistribution(1, 1000000);
    uniform_real_distribution<double> dataDistribution(1.0, 1000000.0);

    cout << "Testing with " << count << " elements of type " << typeid(T).name() << ":" << endl;

    // Insertion test
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) {
        T data = static_cast<T>(dataDistribution(generator));
        int priority = priorityDistribution(generator);
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
    for (int size : counts) {
        cout << "Testing int:" << endl;
        testPriorityQueueBH<int>(size);

        cout << "Testing float:" << endl;
        testPriorityQueueBH<float>(size);

        cout << "Testing double:" << endl;
        testPriorityQueueBH<double>(size);
    }

    //RBT
    PriorityQueueRBT<int> pqRBTInt;
    PriorityQueueRBT<float> pqRBTFloat;
    PriorityQueueRBT<double> pqRBTDouble;


    for (int count : counts) {
        cout << "Integers:\n";
        performTest(pqRBTInt, count);
        cout << "Floats:\n";
        performTest(pqRBTFloat, count);
        cout << "Doubles:\n";
        performTest(pqRBTDouble, count);
    }

    ///SLL
    PriorityQueueSLL<int> pqSLLInt;
    PriorityQueueSLL<float> pqSLLFloat;
    PriorityQueueSLL<double> pqSLLDouble;

    for (int count : counts) {
        cout << "Integers:\n";
        performTest(pqSLLInt, count);
        cout << "Floats:\n";
        performTest(pqSLLFloat, count);
        cout << "Doubles:\n";
        performTest(pqSLLDouble, count);
    }






    return 0;


}
