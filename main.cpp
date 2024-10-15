#include <iostream>
#include <bits/stdc++.h>
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

    void consolidate() { //Function that we are using for connecting the nodes which have same degrees
        int d = (int)log2(NodeCount)+1; //Maximum number of degree that can be
        vector<Node*> degree_table(d, nullptr); //Vector to store the nodes of specific degrees

        vector<Node*> nodes;
        Node* x = min_node;

        do{ //Pushing all the nodes to the nodes vector
            nodes.push_back(x);
            x = x->right;
        } while(x != min_node)

        for (Node* w : nodes) {
            Node* x = w;
            d = x->degree;
            while(degree_table[d]) { //Merging all the nodes with same degrees in the degree_table vector
                Node* y = degree_table[d];
                if (x->key > y->key) {
                    Node* temp = x;
                    x = y;
                    y = temp;
                }
                link(y, x);
                degree_table[d] = nullptr;
                d++;
            }
            degree_table[d] = x;
        }

        void link(Node* node_big, Node* node_small) {
            //First we remove the node y(node_big) from its left and right
            (node_big->left)->right = node_big->right;
            (node_big->right)->left = node_big->left;

            //Now we make node_small the parent of node1
            node_big->parent = node_small;
            node_big->left = node_big->right = node_big;

            //Now we properly link node_big to node_small
            if (!node_small->child) node_small = node_big;
            else {
                node_big->right = node_small->child;
                node_big->left = (node_small->child)->left;
                ((node_small->child)->left)->right = node_big;
                (node_small->child)->left = node_big;
            }

            //Now we set the child of node_small according to the key values of node_big and child of node_small
            if (node_big->key < node_small->child->key) node_small->child = node_big;

            //We now increase the degree of node_small by 1
            node_small->degree++;
        }

        //Making a new heap with the merged nodes that is the final step for consolidating the heap
        min_node = nullptr;
        for (auto& w : degree_table) {
            if (w) {
                if (!min_node) min_node = w;
                else {
                    (min_node->left)->right = w;
                    w->right = min_node;
                    w->left = min_node->left;
                    min_node->left = w;
                    if (min_node->key > w->key) min_node = w;
                }
            }
        }
    }

public:
    Node* min_node; //We can also say it as a root of the heap
    int NodeCount; //Number of nodes in the whole heap

    FibonacciHeap() {
        min_node = nullptr;
        NodeCount = 0;
    }

    void insert(Node* node) { // We will use this function to insert a node in the heap
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

    Node* findMin() { //Function for just getting the minimum node
        return min_node;
    }

    Node* extract_min() { //We will use this function to get and remove the minimum node in the heap
        if (!min_node) return nullptr;
        Node* temp = min_node;
        Node* ptr = temp;
        Node* x = NULL;

        if (temp->child) {
            //Here we will be taking each child of the min_node and insert it to the left of the min_node and after that
            //we will just remove the min_node and make a new min_node

            x = temp->child;
            do {
                ptr = x->right;
                (min_node->left)->right = x;
                x->right = min_node;
                x->left = min_node->left;
                min_node->left = x;
                if (x->key <  min_node->key) min_node = x;
                x->parent = NULL;
                x = ptr;
            } while (ptr != temp->child);
        }
        (temp->left)->right = temp->right;
        (temp->right)->left = temp->left;
        if (temp == temp->right && temp->child == NULL) {
            min_node = NULL;
        }
        else {
            min_node = temp->right;
            consolidate();
        }
        NodeCount--;
        return temp;
    }

};

int main() {

}