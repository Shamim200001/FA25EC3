//
// Created by Manju Muralidharan on 11/22/25.
//

#ifndef FA25EC3_TREE_H
#define FA25EC3_TREE_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

/*
   TEMPLATE TREE CLASS
   Multiple parents may point to the same child.
   Students must manage storage, pointers, and dynamic allocation.

   Requirements:
   1. Templated Tree class.
   2. Nodes stored dynamically.
   3. Each node has:
      - id
      - data
      - vector of children pointers
   4. Students must prevent memory leaks.
   5. Students must create createRoot, addNode, findNode, print functions, etc.

   DO NOT IMPLEMENT ANYTHING HERE.
   Only placeholders and TODO comments.
*/


template <typename U>
class Node {
public:
    string id;
    U data;
    vector<Node<U>*> children;
    vector<Node<U>*> parents;

    // TODO: Write constructor
    // Node(const string &nodeID, const U &value);

    Node(const string &nodeID, const U &value) : id(nodeID), data(value) {}
    ~Node() {

    }
};

template <typename T>
class Tree {
private:
    //Starting point of the tree is here

    Node<T>* root;
    map<string, Node<T>*> nodeMap;
    void deleteTree(Node<T>* node) {
        if (!node) return;

        // Remove this node from nodeMap
        nodeMap.erase(node->id);

        // auto delete chile only
        for (auto child : node->children) {
            // Remove this node from child's parents
            auto it = find(child->parents.begin(), child->parents.end(), node);
            if (it != child->parents.end()) {
                child->parents.erase(it);
            }

            // If child has no more parents, delete it recursively
            //that's how recursively works
            if (child->parents.empty()) {
                deleteTree(child);
            }
        }

        delete node;
    }
    // This is my DFS
    Node<T>* findNodeHelper(Node<T>* current, const string &id) {
        if (!current) return nullptr;

        if (current->id == id)
            return current;

        for (auto child : current->children) {
            Node<T>* found = findNodeHelper(child, id);
            if (found) return found;
        }

        return nullptr;
    }
//printHelper function will recursively print a node and it's children
    void printHelper(Node<T>* current) {
        if (!current) return;

        cout << "Node" << current->id << ":" << current->data << endl;
// The display will print the children or none exist
        if (current->children.empty()) {
            cout << " Child -> (none)" << endl;
        }else {
            for (auto child : current->children) {
                cout << " Child -> " <<child->id << endl;
            }
        }
        cout << endl;
        }

    //the function collectAllNodes will
    void collectAllNodes(Node<T>* start, vector<Node<T>*>& collected) {
        if (!start) return;

        // Avoid infinite loops in case of cycles
        if (find(collected.begin(), collected.end(), start) != collected.end()) {
            return;
        }

        collected.push_back(start);

        for (auto child : start->children) {
            collectAllNodes(child, collected);
        }
    }

    // TODO: Initialize root pointer to nullptr
public:
    //here is the constructor
    //the reason we create a constructor is to initialize empty tree
    Tree(): root(nullptr) {}
// tree pointer
    ~Tree() {
    }

    void createRoot(const string &id, const T &value) {
    // TODO: Allocate memory, assign id, assign data, set as root

        //checking if root already exist
    if (root){
        cerr << "Root already exist!" << endl;
        return;
    }
        //here we check for duplicate node ID

    if (nodeMap.find(id) != nodeMap.end()) {
        cerr << "Node with ID" << id << "already exists!" << endl;
        return;
    }
//create new node with dynamic allocation
        //lookup map
        root = new Node<T>(id, value);
        nodeMap[id] = root;

    }
    // TODO: Find parent, create child, link parent to child
    // TODO: Support repeated children under multiple parents
// addNode function will add a node to the tree and establish the relationship of parent and child
    void addNode(const string &parentID, const string &childID, const T &value) {

        //check if parent node exist and find it
        Node<T>* parent = findNode(parentID);
        if (!parent) {
            cerr << "Parent node" << parentID << "not found!" << endl;
            return;
        }
//try to find child node or create a new child node
        Node<T>* child = nullptr;
        if (nodeMap.find(childID) != nodeMap.end()) {
            child = nodeMap [childID];
//here the code will make sure the old data is matching the new data
            if (child->data != value) {
                cerr << "Child node" << childID << "exists with different data!" << endl;
                return;
            }
//if child doesn't exist then creat a new node
        }else {
            child = new Node<T>(childID, value);
            nodeMap[childID] = child;
        }
//this part of the code the relationship between the parent and child gets created
        // child gets added to parents but before it will check for duplicate
        if (find(parent->children.begin(), parent->children.end(), child) == parent->children.end()) {
            parent->children.push_back(child);
            child->parents.push_back(parent);
        }
    }
    //FindNode will find the node by its ID
    //The pointer will get returned to node or nullptr if not found
    Node<T>* findNode(const string &id) {
        auto it = nodeMap.find(id);
        if (it != nodeMap.end()) {
            return it->second;
        }
        return nullptr;
    }

//This for display to print all the structure
    void printAll() {
        cout <<"==== Story Tree ====" << endl;
        vector<Node<T>*> allNodes;
        for (auto& pair : nodeMap) {
            allNodes.push_back(pair.second);
        }
        sort(allNodes.begin(), allNodes.end(), [](Node<T>* a, Node<T>* b) {
            return stoi(a->id) < stoi(b->id);
});

        for (auto node : allNodes) {
            printHelper(node);
        }
        cout << "===========" << endl;
    }
    // TODO: Print entire structure in readable form

    // TODO: Free all allocated memory
//THe playGame will interactive story traversal
    //this will start from root
    //get the numbers and output the result
    void playGame() {
        if (!root) {
            cout << "No story loaded!" << endl;
            return;
        }
        cout << "\n==== Begin Adventure =====\n" << endl;

        Node<T>* current = root;

        while (current) {

            cout << current ->data << endl;

            if (current->children.empty()) {
                cout << "\nThere are no futher paths." << endl;
                cout << "Your journey ends here." << endl;
                break;
            }

            cout << "Choose your next action:" << endl;
            for (size_t i = 0; i < current->children.size(); ++i) {

                string childText = current->children[i]->data;
                string optionText;
                if (childText. length() > 50) {
                    optionText = childText.substr(0, 47) + "...";
                }else {
                    optionText = childText;
                }

                cout << i + 1 << "." << optionText << endl;

            }

            int choice = 0;
            while (true) {
                cout << "Selection: ";
                cin >> choice;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "invalid input, please enter a number." << endl;
                    continue;
                }

                if (choice >= 1 && choice <= static_cast<int>(current->children.size())) {
                    break;

                }else {
                    cout << "Invalid choice. please select between 1 and" << current->children.size() << "." << endl;
                }
            }

            current = current->children[choice - 1];
            cout << endl;
        }
        cout << "\n==== End Adventure =====" << endl;
    }


};

#endif //FA25EC3_TREE_H
