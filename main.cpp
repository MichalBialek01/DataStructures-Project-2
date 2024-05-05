#include <iostream>
#include <stdexcept>

enum Color { RED, BLACK };

template <typename T>
struct Node {
    T data;
    int priority;
    Color color;
    Node *left, *right, *parent;

    Node(T data, int priority) : data(data), priority(priority), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T>
class RedBlackTree {
private:
    Node<T>* root;

    void rotateLeft(Node<T>*& root, Node<T>*& x) {
        Node<T>* y = x->right;
        x->right = y->left;
        if (x->right != nullptr)
            x->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node<T>*& root, Node<T>*& x) {
        Node<T>* y = x->left;
        x->left = y->right;
        if (x->left != nullptr)
            x->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void fixInsert(Node<T>*& root, Node<T>*& k) {
        Node<T>* u;
        while (k->parent != nullptr && k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u != nullptr && u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rotateRight(root, k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rotateLeft(root, k->parent->parent);
                }
            } else {
                u = k->parent->parent->right;
                if (u != nullptr && u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        rotateLeft(root, k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rotateRight(root, k->parent->parent);
                }
            }
            if (k == root) break;
        }
        root->color = BLACK;
    }

    void rbTransplant(Node<T>* u, Node<T>* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    void fixDelete(Node<T>* x) {
        Node<T>* s;
        while (x != root && (x == nullptr || x->color == BLACK)) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(root, x->parent);
                    s = x->parent->right;
                }
                if ((s->left == nullptr || s->left->color == BLACK) && (s->right == nullptr || s->right->color == BLACK)) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->right == nullptr || s->right->color == BLACK) {
                        s->left->color = BLACK;
                        s->color = RED;
                        rotateRight(root, s);
                        s = x->parent->right;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (s->right != nullptr) s->right->color = BLACK;
                    rotateLeft(root, x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(root, x->parent);
                    s = x->parent->left;
                }
                if ((s->right == nullptr || s->right->color == BLACK) && (s->left == nullptr || s->left->color == BLACK)) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->left == nullptr || s->left->color == BLACK) {
                        s->right->color = BLACK;
                        s->color = RED;
                        rotateLeft(root, s);
                        s = x->parent->left;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (s->left != nullptr) s->left->color = BLACK;
                    rotateRight(root, x->parent);
                    x = root;
                }
            }
        }
        if (x != nullptr) x->color = BLACK;
    }

    Node<T>* minimum(Node<T>* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(const T& data, int priority) {
        Node<T>* node = new Node<T>(data, priority);
        Node<T>* y = nullptr;
        Node<T>* x = this->root;

        while (x != nullptr) {
            y = x;
            if (node->priority < x->priority)
                x = x->left;
            else
                x = x->right;
        }

        node->parent = y;
        if (y == nullptr)
            root = node;
        else if (node->priority < y->priority)
            y->left = node;
        else
            y->right = node;

        if (node->parent == nullptr) {
            node->color = BLACK;
            return;
        }

        if (node->parent->parent == nullptr)
            return;

        fixInsert(root, node);
    }

    void deleteNode(Node<T>* node, int priority) {
        Node<T>* z = root;
        Node<T>* x, *y;

        while (z != nullptr) {
            if (z->priority == priority) {
                break;
            } else if (priority < z->priority) {
                z = z->left;
            } else {
                z = z->right;
            }
        }

        if (z == nullptr) {
            return; // Node to delete not found
        }

        y = z;
        Color yOriginalColor = y->color;
        if (z->left == nullptr) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == nullptr) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z) {
                if (x) x->parent = y;
            } else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (yOriginalColor == BLACK) {
            fixDelete(x);
        }
    }

    Node<T>* getRoot() {
        return root;
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    Node<T>* maximum(Node<T>* node) {
        while (node->right != nullptr)
            node = node->right;
        return node;
    }
};

template <typename T>
class PriorityQueue {
private:
    RedBlackTree<T> tree;

public:
    void insert(const T& item, int priority) {
        tree.insert(item, priority);
    }

    T pop() {
        if (tree.isEmpty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        Node<T>* maxNode = tree.maximum(tree.getRoot());
        T item = maxNode->data;
        tree.deleteNode(maxNode, maxNode->priority);
        return item;
    }

    T peek() {
        if (tree.isEmpty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        Node<T>* maxNode = tree.maximum(tree.getRoot());
        return maxNode->data;
    }

    bool isEmpty() {
        return tree.isEmpty();
    }

    void remove(const T& item, int priority) {
        // Search and remove item with specific priority (to be implemented fully)
    }

    void remove() {
        if (tree.isEmpty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        Node<T>* maxNode = tree.maximum(tree.getRoot());
        tree.deleteNode(maxNode, maxNode->priority);
    }
};

int main() {
    PriorityQueue<std::string> pq;
    pq.insert("hello", 5);
    pq.insert("world", 2);
    pq.insert("!", 10);

    std::cout << "Peek: " << pq.peek() << std::endl; // Outputs: !
    std::cout << "Pop: " << pq.pop() << std::endl;  // Outputs: !
    std::cout << "Peek now: " << pq.peek() << std::endl;  // Outputs: hello

    return 0;
}