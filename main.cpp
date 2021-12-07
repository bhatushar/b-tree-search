#include <iostream>
#include <unordered_set>
#include <random>
#include <chrono>
#include "BTree.hpp"

using namespace std;
typedef unordered_set<size_t> KeySet;

void generateKeys(size_t n, KeySet& keys) {
    static random_device rd;
    static mt19937_64 eng(rd());
    static uniform_int_distribution<size_t> dist;
    for (size_t i = keys.size() + 1; i <= n; i++) {
        size_t key;
        do {
            key = dist(eng);
        } while (keys.find(key) != keys.end());
        keys.insert(key);
    }
}

long long insertKeys(const KeySet& keys, BTree& tree) {
    using namespace chrono;
    auto start = high_resolution_clock::now();
    for (KeySet::const_iterator iter = keys.begin(); iter != keys.end(); iter++)
        tree.insert(*iter);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    return duration.count();
}

long long linearSearch(const KeySet& keys, const BTree& tree) {
    using namespace chrono;
    vector<size_t> unfoundKeys;
    auto start = high_resolution_clock::now();
    for (KeySet::const_iterator iter = keys.begin(); iter != keys.end(); iter++)
        if (!tree.search(*iter)) unfoundKeys.push_back(*iter);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    if (unfoundKeys.size() > 0) {
        cout << "FAILED TO FIND KEY: ";
        for (auto k: unfoundKeys) cout << k << " ";
        cout << endl;
    }
    return duration.count();
}

long long binarySearch(const KeySet& keys, const BTree& tree) {
    using namespace chrono;
    vector<size_t> unfoundKeys;
    auto start = high_resolution_clock::now();
    for (KeySet::const_iterator iter = keys.begin(); iter != keys.end(); iter++)
        if (!tree.binarySearch(*iter)) unfoundKeys.push_back(*iter);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    if (unfoundKeys.size() > 0) {
        cout << "FAILED TO FIND KEY: ";
        for (auto k: unfoundKeys) cout << k << " ";
        cout << endl;
    }
    return duration.count();
}

int main() {
    size_t n, t = 100;
    long long executionTime;
    KeySet keys;
    
    cout << "Keeping t = " << t << " constant" << endl << endl;
    for (n = 10e3; n <= 10e6; n *= 10) {
        BTree tree(t);

        cout << "n = " << n << endl;
        generateKeys(n, keys);

        executionTime = insertKeys(keys, tree);
        cout << "Inserting unique keys took " << executionTime << " microseconds" << endl;
        
        executionTime = linearSearch(keys, tree);
        cout << "Using linear search took " << executionTime << " microseconds" << endl;
        
        executionTime = binarySearch(keys, tree);
        cout << "Using binary search took " << executionTime << " microseconds" << endl << endl;
    }

    n = 10e5;
    keys.clear();
    generateKeys(n, keys);
    
    cout << "Keeping n = " << n << " constant" << endl << endl;
    for (size_t t = 100; t <= 1000; t += 200) {
        BTree tree(t);

        cout << "t = " << t << endl;

        executionTime = insertKeys(keys, tree);
        cout << "Inserting unique keys took " << executionTime << " microseconds" << endl;
        
        executionTime = linearSearch(keys, tree);
        cout << "Using linear search took " << executionTime << " microseconds" << endl;
        
        executionTime = binarySearch(keys, tree);
        cout << "Using binary search took " << executionTime << " microseconds" << endl << endl;
    }
    return 0;
}
