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

    cout << "Testing with " << numberOfElements << " elements:" << endl;


    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < numberOfElements; i++) {
        pq.insert(static_cast<T>(i), i);
    }
    auto stop = chrono::high_resolution_clock::now();
    auto durationInsert = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    logger.log("BH,Insert," + to_string(numberOfElements) + "," + to_string(durationInsert.count()));
//    cout << "Insert time: " << elapsed.count() << " ns";

    start = chrono::high_resolution_clock::now();
    pq.peek();
    stop = chrono::high_resolution_clock::now();
    auto durationPeek = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    logger.log("BH,Peek," + to_string(numberOfElements) + "," + to_string(durationPeek.count()));
//    cout << "Peek time: " << elapsed.count() << " ms\n";

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < numberOfElements; i++) {
        pq.pop();
    }
    stop = chrono::high_resolution_clock::now();
    auto durationPop = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    logger.log("BH,Pop," + to_string(numberOfElements) + "," + to_string(durationPop.count()));
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
    auto durationInsert = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    logger.log("RBT,Insert," + to_string(numberOfElements) + "," + to_string(durationInsert.count()));
//    cout << "Insert time: " << durationInsert.count() << " ms\n";

    // Peek test
    start = chrono::high_resolution_clock::now();
    pq.peek();
    stop = chrono::high_resolution_clock::now();
    auto durationPeek = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    logger.log("RBT,Peek," + to_string(numberOfElements) + "," + to_string(durationPeek.count()));
//    cout << "Peek time: " << durationPeek.count() << " ms\n";

    // Pop test
    start = chrono::high_resolution_clock::now();
    while (!pq.isEmpty()) {
        pq.pop();
    }
    stop = chrono::high_resolution_clock::now();
    auto durationPop = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    logger.log("RBT,Pop," + to_string(numberOfElements) + "," + to_string(durationPop.count()));
    //    cout << "Pop time: " << durationPop.count() << " ms\n";
}

//SLL
template<typename T>
void performTestSLL(PriorityQueueSLL<T>& pq, int count,Logger&  logger) {
    logger.log("Testing with " + to_string(count) + " elements of type " + typeid(T).name() + ":");

    // Insertion test
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) {
        T data = static_cast<T>(1 + i * 0.1);  // Simple data generation
        int priority = i + 1;                 // Sequential priorities
        pq.insert(data, priority);
    }
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = stop - start;
    logger.log("Insert time: " + to_string(elapsed.count()) + " ms");

    // Peek test
    start = chrono::high_resolution_clock::now();
    try {
        auto item = pq.peek();  // Just for time measurement
    } catch (const runtime_error& e) {
        logger.log("Peek error: " + string(e.what()));
    }
    stop = chrono::high_resolution_clock::now();
    elapsed = stop - start;
    logger.log("Peek time: " + to_string(elapsed.count()) + " ms");

    // Pop test
    start = chrono::high_resolution_clock::now();
    while (!pq.isEmpty()) {
        try {
            auto item = pq.pop();
        } catch (const runtime_error& e) {
            logger.log("Pop error: " + string(e.what()));
            break;
        }
    }
    stop = chrono::high_resolution_clock::now();
    elapsed = stop - start;
    logger.log("Pop time: " + to_string(elapsed.count()) + " ms");
}


int main() {
    Logger logger("performance_log.csv");
    vector<int> counts = {1000, 10000, 100000};
//      Działa poprawnie
//    //BH
//    cout<<"Testing BinaryHeap priorityQueue"<<endl;
//    for (int size : counts) {
//        testPriorityQueueBH<int>(logger,size);
//        testPriorityQueueBH<float>(logger,size);
//        testPriorityQueueBH<double>(logger,size);
//    }
//    cout<<"Testing BinaryHeap priorityQueue finished"<<endl;


    //RBT
    cout<<"Testing RedBlackTree priorityQueue"<<endl;
    PriorityQueueRBT<int> pqRBTInt;
    PriorityQueueRBT<float> pqRBTFloat;
    PriorityQueueRBT<double> pqRBTDouble;



    for (int count : counts) {
        performTestRBT(pqRBTInt, count, logger);
        performTestRBT(pqRBTFloat, count,logger);
        performTestRBT(pqRBTDouble, count,logger);
    }
    cout<<"Testing RedBlackTree priorityQueue finished"<<endl;

//    ///SLL
//    cout<<"Testing SingleLinkedList SingleLinkedList"<<endl;
//    PriorityQueueSLL<int> pqSLLInt;
//    PriorityQueueSLL<float> pqSLLFloat;
//    PriorityQueueSLL<double> pqSLLDouble;
//
//    for (int count : counts) {
//        performTestSLL(pqSLLInt, count,logger);
//        performTestSLL(pqSLLFloat, count,logger);
//        performTestSLL(pqSLLDouble, count,logger);
//    }
//    cout<<"Testing SingleLinkedList SingleLinkedList finished"<<endl;
//    return 0;
}
