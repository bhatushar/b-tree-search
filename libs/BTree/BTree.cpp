#include "BTree.hpp"
#include <iostream>
#include <queue>
#include <utility>

BTree::Node::Node(bool leaf) : isLeaf(leaf) {}

BTree::BTree(int t) : minDegree(t), root(new Node(true)) {}

void BTree::splitChild(Node* x, int i) {
    Node* y = x->children[i];
    Node* z = new Node(y->isLeaf);
    z->keys = std::vector<int>(y->keys.begin() + minDegree, y->keys.end());
    if (!y->isLeaf)
        for (int j = minDegree; j < y->children.size(); j++)
            z->children.emplace_back(y->children[j]);
    x->children.insert(x->children.begin() + i + 1, z);
    x->keys.insert(x->keys.begin() + i, y->keys[minDegree - 1]);
    y->keys.resize(minDegree - 1);
    if (!y->isLeaf)
        y->children.resize(minDegree);
}

void BTree::insertNonFull(Node* x, int k) {
    int i = x->keys.size() - 1;
    if (x->isLeaf) {
        x->keys.resize(i + 2);
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i+1] = x->keys[i];
            i--;
        }
        x->keys[i+1] = k;
    }
    else {
        while (i >= 0 && k < x->keys[i]) i--;
        i++;
        if (x->children[i]->keys.size() == 2 * minDegree - 1) {
            splitChild(x, i);
            if (k > x->keys[i]) i++;
        }
        insertNonFull(x->children[i], k);
    }
}

void BTree::insert(int key) {
    if (root->keys.size() == 2*minDegree - 1) {
        Node* temp = root;
        root = new Node(false);
        root->children.push_back(temp);
        splitChild(root, 0);
    }
    insertNonFull(root, key);
}

bool BTree::search(int key, Node* x) {
    if (!x) x = root;
    int i = 0;
    while (i < x->keys.size() && key > x->keys[i]) i++;
    if (i < x->keys.size() && key == x->keys[i]) return true;
    if (x->isLeaf) return false;
    return search(key, x->children[i]);
}

void BTree::print() {
    typedef std::pair<Node*, int> pair;
    std::queue<pair> q;
    q.push(std::make_pair(root, 0));
    while (q.size()) {
        auto p = q.front();
        q.pop();
        std::cout << "Level: " << p.second << std::endl;
        for (auto key: p.first->keys)
            std::cout << key << " ";
        std::cout << std::endl;
        if (!p.first->isLeaf)
            for (auto& child: p.first->children)
                q.push(std::make_pair(child, p.second + 1));
    }
}
