#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;

class Node {
public:
    string type;
    string value;
    vector<Node*> children;

    Node(string t, string v) : type(t), value(v) {}

    void addChild(Node* child) {
        children.push_back(child);
    }

    void printNode() {
        cout << "Type: " << type << ", Value: " << value << endl;
    }
};

unordered_map<int, Node*> parseDotFile(const string& fileName) {
    ifstream file(fileName);
    string line;
    unordered_map<int, Node*> nodes;
    int nodeCount = 0;

    while (getline(file, line)) {
        // Debugging print
        cout << "Processing line: " << line << endl;

        if (line.find("[label=") != string::npos) {
            // Extract node ID and label
            size_t startPos = line.find("n") + 1;
            size_t endPos = line.find(" [label=");
            
            // Check if we can safely extract node ID
            if (startPos != string::npos && endPos != string::npos) {
                string nodeIdStr = line.substr(startPos, endPos - startPos);
                try {
                    int nodeId = stoi(nodeIdStr);  // Convert to integer
                    size_t labelStart = line.find("\"") + 1;
                    size_t labelEnd = line.find("\"", labelStart);
                    string label = line.substr(labelStart, labelEnd - labelStart);

                    // Split label by ":" to separate type and value
                    size_t colonPos = label.find(":");
                    string nodeType = label.substr(0, colonPos);
                    string nodeValue = label.substr(colonPos + 1);

                    // Create node and add it to the map
                    Node* newNode = new Node(nodeType, nodeValue);
                    nodes[nodeId] = newNode;
                } catch (const invalid_argument& e) {
                    cerr << "Error: Failed to convert to integer: " << nodeIdStr << endl;
                }
            }
        }

        if (line.find("->") != string::npos) {
            // Parse edge relationships (nX -> nY)
            size_t arrowPos = line.find("->");
            int parentId = 0;
            int childId = 0;

            try {
                parentId = stoi(line.substr(1, arrowPos - 2));
                childId = stoi(line.substr(arrowPos + 2, line.find(";") - (arrowPos + 2)));
            } catch (const invalid_argument& e) {
                cerr << "Error: Failed to convert to integer during edge processing" << endl;
                continue;  // Skip this line
            }

            // Create the relationship by adding the child node to the parent's children list
            if (nodes.find(parentId) != nodes.end() && nodes.find(childId) != nodes.end()) {
                nodes[parentId]->addChild(nodes[childId]);
            }
        }
    }

    return nodes;
}

void printSymbolTable(const unordered_map<int, Node*>& nodes) {
    for (const auto& entry : nodes) {
        cout << "Node ID: " << entry.first << endl;
        entry.second->printNode();
        cout << "Children: ";
        for (Node* child : entry.second->children) {
            cout << child->type << ":" << child->value << " ";
        }
        cout << endl;
    }
}

int main() {
    string filename = "tree.dot"; // Specify the file name for the input tree.dot

    // Parse the dot file and build nodes map
    unordered_map<int, Node*> nodes = parseDotFile(filename);

    // Print the symbol table for debugging
    printSymbolTable(nodes);

    // Clean up dynamically allocated memory
    for (auto& entry : nodes) {
        delete entry.second;
    }

    return 0;
}
