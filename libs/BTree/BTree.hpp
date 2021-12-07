#ifndef B_TREE_H
#define B_TREE_H

#include <vector>

class BTree {
    struct Node {
        bool isLeaf;
        std::vector<size_t> keys;
        std::vector<Node*> children;
        Node(bool leaf);
    };
    size_t minDegree;
    Node* root;
    void splitChild(Node* x, size_t i);
    void insertNonFull(Node* x, size_t k);
public:
    BTree(size_t t);
    void insert(size_t key);
    bool search(size_t key, Node* x = nullptr) const;
    bool binarySearch(size_t key, Node* x = nullptr) const;
    void print() const;
};

#endif
