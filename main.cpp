#include <iostream>
#include <stdexcept>
#include <chrono>
#include <random>
#include "BinaryHeap.cpp"

using namespace std;


template<typename T>
void testPriorityQueue(int numberOfElements) {
    PriorityQueue<T> pq;

    // Inicjalizacja generatora liczb losowych
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 1000000);

    // Pomiar czasu dla operacji insert
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numberOfElements; i++) {
        pq.insert(static_cast<T>(distribution(generator)), distribution(generator));
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

int main() {
    std::cout << "Testing int:" << std::endl;
    testPriorityQueue<int>(1000);
    testPriorityQueue<int>(10000);
    testPriorityQueue<int>(100000);

    std::cout << "Testing float:" << std::endl;
    testPriorityQueue<float>(1000);
    testPriorityQueue<float>(10000);
    testPriorityQueue<float>(100000);

    std::cout << "Testing double:" << std::endl;
    testPriorityQueue<double>(1000);
    testPriorityQueue<double>(10000);
    testPriorityQueue<double>(100000);






    return 0;





}



//
//
//    // Define array sizes
//
//    // Create a random device
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<> dis(1, 1000000);
//
//    for (int size : sizes) {
//        PriorityQueue<int> pq;
//        std::cout << "Testing with " << size << " elements:" << std::endl;
//
//        // Timing insert operation
//        auto start = std::chrono::high_resolution_clock::now();
//        for (int i = 0; i < size; ++i) {
//            int random_priority = dis(gen);
//            pq.insert(i, random_priority); // Insert elements with random priorities
//        }
//        auto end = std::chrono::high_resolution_clock::now();
//        std::chrono::duration<double, std::milli> elapsed = end - start;
//        std::cout << "Total time for " << size << " insert operations: " << elapsed.count() << " ms" << std::endl;
//
//        // Timing peek operation
//        start = std::chrono::high_resolution_clock::now();
//        try {
//            int max = pq.peek();
//            std::cout << "Maximum element: " << max << std::endl;
//        } catch (std::runtime_error& e) {
//            std::cout << "Error: " << e.what() << std::endl;
//        }
//        end = std::chrono::high_resolution_clock::now();
//        elapsed = end - start;
//        std::cout << "Time for peek operation: " << elapsed.count() << " ms" << std::endl;
//
//        // Timing pop operations until empty
//        start = std::chrono::high_resolution_clock::now();
//        try {
//            while (!pq.isEmpty()) {
//                pq.pop(); // Continuously remove elements
//            }
//        } catch (std::runtime_error& e) {
//            std::cout << "Error: " << e.what() << std::endl;
//        }
//        end = std::chrono::high_resolution_clock::now();
//        elapsed = end - start;
//        std::cout << "Total time for popping all elements: " << elapsed.count() << " ms" << std::endl;
//
//        std::cout << std::endl;
////    }
//
//    return 0;
//}
