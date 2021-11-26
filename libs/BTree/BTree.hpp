#ifndef B_TREE_H
#define B_TREE_H

#include <vector>

class BTree {
    struct Node {
        bool isLeaf;
        std::vector<int> keys;
        std::vector<Node*> children;
        Node(bool leaf);
    };
    int minDegree;
    Node* root;
    void splitChild(Node* x, int i);
    void insertNonFull(Node* x, int k);
public:
    BTree(int t);
    void insert(int key);
    bool search(int key, Node* x = nullptr);
    void print();
};

#endif
