#include <iostream>
#include <stdexcept>
#include <chrono>
#include <random>
#include "BinaryHeap.cpp"
#include "RedBlackTree.cpp"
#include "SortingList.cpp"
#include "Logger.cpp"

using namespace std;

void printTime(long durationInsert){
    cout<<"Time"<<durationInsert<<"nano"<<endl;
}


template<typename T>
void testPriorityQueueBH(Logger& logger, int numberOfElements) {
    PriorityQueueBH<T> pq;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numberOfElements; i++) {
        pq.insert(static_cast<T>(i), i);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto durationInsert = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    logger.log("BH,Insert," + std::to_string(numberOfElements) + "," + std::to_string(durationInsert.count()));
//    cout << "Insert time: " << elapsed.count() << " ns";

    start = std::chrono::high_resolution_clock::now();
    pq.peek();
    stop = std::chrono::high_resolution_clock::now();
    auto durationPeek = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    logger.log("BH,Peek," + std::to_string(numberOfElements) + "," + std::to_string(durationPeek.count()));
//    cout << "Peek time: " << elapsed.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numberOfElements; i++) {
        pq.pop();
    }
    stop = std::chrono::high_resolution_clock::now();
    auto durationPop = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    logger.log("BH,Pop," + std::to_string(numberOfElements) + "," + std::to_string(durationPop.count()));
    //    cout << "Pop time: " << elapsed.count() << " ms\n";

}


template<typename T>
void performTestRBT(PriorityQueueRBT<T>& pq, int numberOfElements,Logger& logger) {
    cout << "Testing with " << numberOfElements << " elements:" << endl;

    // Insertion test
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < numberOfElements; i++) {
        T data = static_cast<T>(i + 1);
        int priority = i + 1;
        pq.insert(data, priority);
    }
    auto stop = chrono::high_resolution_clock::now();
    auto durationInsert = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    logger.log("RBT,Insert," + std::to_string(numberOfElements) + "," + std::to_string(durationInsert.count()));
//    cout << "Insert time: " << durationInsert.count() << " ms\n";

    // Peek test
    start = chrono::high_resolution_clock::now();
    pq.peek();
    stop = chrono::high_resolution_clock::now();
    auto durationPeek = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    logger.log("RBT,Peek," + std::to_string(numberOfElements) + "," + std::to_string(durationPeek.count()));
//    cout << "Peek time: " << durationPeek.count() << " ms\n";

    // Pop test
    start = chrono::high_resolution_clock::now();
    while (!pq.isEmpty()) {
        pq.pop();
    }
    stop = chrono::high_resolution_clock::now();
    auto durationPop = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    logger.log("RBT,Pop," + std::to_string(numberOfElements) + "," + std::to_string(durationPop.count()));
    //    cout << "Pop time: " << durationPop.count() << " ms\n";
}

//SLL
template<typename T>
void performTestSLL(PriorityQueueSLL<T>& pq, int count,Logger&  logger) {
    logger.log("Testing with " + std::to_string(count) + " elements of type " + typeid(T).name() + ":");

    // Insertion test
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) {
        T data = static_cast<T>(1 + i * 0.1);  // Simple data generation
        int priority = i + 1;                 // Sequential priorities
        pq.insert(data, priority);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = stop - start;
    logger.log("Insert time: " + std::to_string(elapsed.count()) + " ms");

    // Peek test
    start = std::chrono::high_resolution_clock::now();
    try {
        auto item = pq.peek();  // Just for time measurement
    } catch (const std::runtime_error& e) {
        logger.log("Peek error: " + std::string(e.what()));
    }
    stop = std::chrono::high_resolution_clock::now();
    elapsed = stop - start;
    logger.log("Peek time: " + std::to_string(elapsed.count()) + " ms");

    // Pop test
    start = std::chrono::high_resolution_clock::now();
    while (!pq.isEmpty()) {
        try {
            auto item = pq.pop();
        } catch (const std::runtime_error& e) {
            logger.log("Pop error: " + std::string(e.what()));
            break;
        }
    }
    stop = std::chrono::high_resolution_clock::now();
    elapsed = stop - start;
    logger.log("Pop time: " + std::to_string(elapsed.count()) + " ms");
}


int main() {
    Logger logger("performance_log.csv");
    vector<int> counts = {1000, 10000, 100000};

    //BH
    cout<<"Testing BinaryHeap priorityQueue"<<endl;
    for (int size : counts) {
        testPriorityQueueBH<int>(logger,size);
        testPriorityQueueBH<float>(logger,size);
        testPriorityQueueBH<double>(logger,size);
    }
    cout<<"Testing BinaryHeap priorityQueue finished"<<endl;


    //RBT
    cout<<"Testing RedBlackTree priorityQueue"<<endl;
    cout<<"Testing BinaryHeap"<<endl;
    PriorityQueueRBT<int> pqRBTInt;
    PriorityQueueRBT<float> pqRBTFloat;
    PriorityQueueRBT<double> pqRBTDouble;


    for (int count : counts) {
        cout << "Integers:\n";
        performTestRBT(pqRBTInt, count, logger);
        cout << "Floats:\n";
        performTestRBT(pqRBTFloat, count,logger);
        cout << "Doubles:\n";
        performTestRBT(pqRBTDouble, count,logger);
    }

    ///SLL
    cout<<"Testing SingleLinkedList priorityQueue"<<endl;
    PriorityQueueSLL<int> pqSLLInt;
    PriorityQueueSLL<float> pqSLLFloat;
    PriorityQueueSLL<double> pqSLLDouble;

    for (int count : counts) {
        cout << "Integers:\n";
        performTestSLL(pqSLLInt, count,logger);
        cout << "Floats:\n";
        performTestSLL(pqSLLFloat, count,logger);
        cout << "Doubles:\n";
        performTestSLL(pqSLLDouble, count,logger);
    }
    return 0;
}
