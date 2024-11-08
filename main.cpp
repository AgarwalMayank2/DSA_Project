#include <iostream>
#include <bits/stdc++.h>
#include <thread>
#include <chrono>
#include <direct.h>
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
    bool mark; //This is useful while finding a particular node
    bool cut; //This is for seeing if a child of a node has been cut or not

    Node(int time, string event_type) {
        key = time;
        event = event_type;
        degree = 0;
        parent = child = nullptr;
        left = right = nullptr;
        mark = false;
        cut = false;
    }
};

class FibonacciHeap {
private:

    void consolidate() { //Function that we are using for connecting the nodes which have same degrees
        int d = (int)log2(NodeCount)+1; //Maximum number of degree that can be
        vector<Node*> degree_table(d, nullptr); //Vector to store the nodes of specific degrees

        vector<Node*> nodes;
        Node* x = min_node;

        do{ //Pushing all the nodes to the nodes vector
            nodes.push_back(x);
            x = x->right;
        } while(x != min_node);

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

    void decreaser(Node* node, int newval) {

        if (!min_node) cout << "The Heap is Empty" << endl;
        else if (!node) cout << "There is no such Node in the Heap" << endl;

        node->key = newval;
        Node* temp = node->parent;

        if (temp && node->key < temp->key) {
            Cut(node, temp);
            Cascade_cut(temp);
        }
        if (node->key < min_node->key) {
            min_node = node;
        }
    }

    void Cut(Node* node, Node* temp) {
        if (node == node->right) temp->child = nullptr;

        if (node == temp->child) temp->child = node->right;

        node->left->right = node->right;
        node->right->left = node->left;

        temp->degree--;
        node->left = node->right = node;
        node->parent = nullptr;
        insert(node);
    }

    void Cascade_cut(Node* temp) {
        Node* parent_node = temp->parent;

        if (parent_node) {
            if (!temp->cut) temp->cut = true;
            else {
                Cut(temp, parent_node);
                Cascade_cut(parent_node);
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
            min_node->right = min_node->left = min_node;
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

    void decrease(Node* node, int find, int newval) {
        Node* found = NULL;
        Node* temp = node;
        node->mark = true;
        Node* found_ptr = NULL;
        if (temp->key == find) {
            found_ptr = temp;
            temp->mark = false;
            found = found_ptr;
            decreaser(found, newval);
        }
        if (found_ptr == NULL) {
            if (temp->child) decrease(temp->child, find, newval);
            if (!(temp->right)->mark) decrease(temp->right, find, newval);
        }
        temp->mark = false;
        found = found_ptr;
    }

};

FibonacciHeap pointer;

void node_maker(int time, string event_name) {
    Node* node = new Node(time, event_name);
    pointer.insert(node);
}

class event {
public:
    int time;
    string main_event;

    event(int timestamp, string event_type) {
        time = timestamp;
        main_event = event_type;
    }

    void vehicle_arrives() {
        cout << main_event << " will arrive at " << time <<  endl;
        main_event = main_event+" arrives";
        node_maker(time, main_event);
    }

    void traffic_lights_changer() {
        cout << "Traffic lights will change to " << main_event << " at " << time << endl;
        main_event = "traffic lights to "+main_event;
        node_maker(time, main_event);
    }
};

class vehicle_arrival : public event {
public:
    vehicle_arrival(int timestamp, string vehicle) : event(timestamp, vehicle) {}
};

class traffic_light : public event {
public:
    traffic_light(int timestamp, string light_change) : event(timestamp, light_change) {}
};

class Traffic_simulation{
    Node* event_maker;

public:
};

void min_taker(int time) {
    if (pointer.min_node) {
        Node* min = pointer.findMin();
        if (min->key == time) {
            cout << time << " : " << min->event << endl;
            min = pointer.extract_min();
        }
    }
    return;
}

void event_choice() {
    for (int i = 0; i<75; i++) {
        cout << '-';
    }
    cout << endl;
    cout << "Make a choice:-" << endl;
    cout << "1. Make a event for vehicle arrival" << endl;
    cout << "2. Make a event for traffic lights change" << endl;
    cout << "3. Decrease the time of an event" << endl;
    cout << "4. Start the simulation" << endl;
    cout << "5. Exit the simulation" << endl;
    for (int i = 0; i<75; i++) {
        cout << '-';
    }
    cout << endl;
}

int event_planner() {
    cout << "Give your input :- ";
    int main_choice;
    cin >> main_choice;
    if (main_choice == 1) {
        cout << "Give the vehicle to come :- ";
        string vehicle;
        cin >> vehicle;
        cout << "Give the timestamp at which " << vehicle << " will come :- ";
        int time;
        cin >> time;

        vehicle_arrival veh(time, vehicle);
        veh.vehicle_arrives();
    }
    else if (main_choice == 2) {
        cout << "Give the colour of the lights to change :- ";
        string colour;
        cin >> colour;
        cout << "Give the timestamp at which traffic light will change :- ";
        int time;
        cin >> time;

        traffic_light tr(time, colour);
        tr.traffic_lights_changer();
    }
    else if (main_choice == 3) {
        if (pointer.min_node) {
            int change_time, new_time;
            cout << "Enter the time to decrease it :- ";
            cin >> change_time;
            cout << "Enter the new time for it :- ";
            cin >> new_time;
            pointer.decrease(pointer.min_node, change_time, new_time);
        }
        else cout << "No actions to take place!!!" << endl;
    }
    else if (main_choice == 4) {
        int time = 1;
        while(true) {
            cout << time << '\n';
            min_taker(time);
            //std::this_thread::sleep_for(std::chrono::seconds(1));
            time++;
            if (time == 100) break;
        }
    }
    return main_choice;
}

int main() {

    while(true) {
        event_choice();
        if (event_planner() == 4) {
            cout << "Exiting Simulation";
            return 0;
        }
    }
}