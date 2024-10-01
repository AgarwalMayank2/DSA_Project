#include<bits/stdc++.h>
using namespace std;

//--------First we will do Fibonacci Heap implementation--------
 
class Node { //Class Node which we will be using for making the nodes of our fibonacci heap
public:
    int key; //Value of the node
    string event; //Event which is to happen
    Node* parent; //pointer for the parent node
    Node* child; //pointer for the child node
    Node* left; //left node pointer
    Node* right; //right node pointer
    int degree; //Degree of the node
    bool mark;

    Node(int key, string event) {
        key = key;
        event = event;
        degree = 0;
        parent = child = nullptr;
        left = right = nullptr;
        mark = false;
    }
};

class FibonacciHeap() {
private:
    
public:
    Node* min_node;
    int NodeCount;

    FibonacciHeap() {
        min_node = nullptr;
        NodeCount = 0;
    }

    void insert(Node* node) {
        if (!min_node) {
            min_node = node;
        }
        else {
            (min_node->left)->right = node;
            node->right = min_node;
            node->left = min_node->left;
            min_node->left = node;
            if (min_node->key > node->key) min_node = node;
        }
        NodeCount++;
        return;
    }


};

int main() {

}