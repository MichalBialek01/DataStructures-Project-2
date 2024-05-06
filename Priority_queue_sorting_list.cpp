#include <iostream>

template <typename T>
class PriorityQueue {
    struct Node {
        T item;
        int priority;
        Node* next;

        Node(const T& item, int priority, Node* next = nullptr)
                : item(item), priority(priority), next(next) {}
    };

    Node* head;

public:
    PriorityQueue() : head(nullptr) {}

    ~PriorityQueue() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert(const T& item, int priority) {
        Node* newNode = new Node(item, priority);
        if (head == nullptr || head->priority < priority) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr && current->next->priority >= priority) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Attempt to pop from empty priority queue");
        }
        Node* temp = head;
        T item = head->item;
        head = head->next;
        delete temp;
        return item;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Attempt to peek in empty priority queue");
        }
        return head->item;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void deleteItem(const T& item, int priority) {
        Node* current = head;
        Node* previous = nullptr;

        while (current != nullptr && !(current->item == item && current->priority == priority)) {
            previous = current;
            current = current->next;
        }

        if (current != nullptr) {
            if (previous == nullptr) { // First element
                head = current->next;
            } else {
                previous->next = current->next;
            }
            delete current;
        }
    }

    void deleteItem() {
        if (!isEmpty()) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    PriorityQueue<std::string> pq;

    pq.insert("low", 1);
    pq.insert("medium", 5);
    pq.insert("high", 10);

    std::cout << "Peek: " << pq.peek() << std::endl; // Should output 'high'
    pq.deleteItem();
    std::cout << "New Peek: " << pq.peek() << std::endl; // Should output 'medium'

    pq.deleteItem("medium", 5);
    std::cout << "Peek after deleting 'medium': " << pq.peek() << std::endl; // Should output 'low'

    while (!pq.isEmpty()) {
        std::cout << "Pop: " << pq.pop() << std::endl;
    }

    return 0;
}
