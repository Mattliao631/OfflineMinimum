#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

struct Node {
    Node* parent;
    int rank;
    int data;
    Node(): data(0), parent(this), rank(0) {}
    Node(int data): data(data), parent(this), rank(0) {}
};

class DisjointSets {
public:
    DisjointSets() {
        size = 0;
        map = unordered_map<int, Node*>();
    }
    ~DisjointSets() {
        for (auto it = map.begin(); it != map.end(); it++) {
            delete it->second;
        }
    }

    void MakeSet(int data) {
        size++;
        Node* node = new Node();
        node->parent = node;
        node->rank = 0;
        node->data = data;
        map[data] = node;
    }
    void Union(int d1, int d2) {
        Node* n1 = findSet(map[d1]);
        Node* n2 = findSet(map[d2]);
        
        if (n1 == n2) return;

        Node* large = n1;
        Node* small = n2;

        size--;
        if (small->rank > large->rank) {
            swap(small, large);
        }
        if (small->rank == large->rank) {
            large->rank++;
        }
        small->parent = large;
        if (large != n1) {
            swap(large->data, small->data);
            swap(map[large->data], map[small->data]);
        }
    }
    int FindSet(int data) {
        return findSet(map[data])->data;
    }
    int Size() {
        return size;
    }
    friend ostream& operator<<(ostream& os, const DisjointSets& ds) {
        for (auto it = ds.map.begin(); it != ds.map.end(); it++) {
            os << it->first << " ";
        }
        return os;
    }
private:
    int size;
    unordered_map<int, Node*> map;
    Node* findSet(Node* node) {
        if (node != node->parent) {
            node->parent = findSet(node->parent);
        }
        return node->parent;
    }
};