#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node {
public:
    string type;     // Node type (e.g., ClassDecl, MethodDecl, VarDecl)
    string value;    // Node value (e.g., class name, method name, variable name)
    vector<Node*> children; // Children nodes

    // Constructor
    Node(string t, string v) : type(t), value(v) {}

    // Add child node
    void addChild(Node* child) {
        children.push_back(child);
    }

    // Print tree structure
    void printTree(int depth = 0) {
        for (int i = 0; i < depth; i++) cout << "  ";
        cout << type << ": " << value << endl;
        for (Node* child : children) {
            child->printTree(depth + 1);
        }
    }
};


int main(int argc, char **argv)
{
    // Create root node
    Node* root = new Node("Program", "Program");

    // Create class node
    Node* classNode = new Node("ClassDecl", "Main");

    // Create method node
    Node* methodNode = new Node("MethodDecl", "main");

    // Create variable node
    Node* varNode = new Node("VarDecl", "x");

    // Add variable node to method node
     ->addChild(varNode);

    // Add method node to class node
    classNode->addChild(methodNode);

    // Add class node to root node
    root->addChild(classNode);

    // Print tree structure
    root->printTree();

    return 0;
}

#endif
