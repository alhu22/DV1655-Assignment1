#ifndef SYMBOLTABEL_H
#define SYMBOLTABLE_H

//#include "Node.h"
#include <iostream>
#include <list>

using namespace std;

class ST {
	public:
	int id, lineno;
    string type,name,scope, child;
	Node* root;
    list<ST*> children;
	ST(int l, string t, string n, string s, string c, Node* r) : lineno(l), type(t), name(n), scope(s), child(c),root(r) {}
	ST(){
		lineno = -1;
		type = "uninitialised";
		name = "uninitialised";
		scope = "uninitialised";
		child = "uninitialised";
		root = NULL;
	}


    void traverse(Node* node=NULL){
        if (node == NULL) {
			node = root;
		}

        if (node->type == "Goal") {
			lineno = node->lineno;
			type = "Goal";
			name = "root";
			scope = "global";
			child = "classes: ";
			for (auto i = node->children.begin(); i != node->children.end(); i++)
			child += (*i)->value + " ";
		}
		else if (node->type == "ClassDeclaration") {
			lineno = node->lineno;
			name = node->value;
			scope = "class";
			type = "";
			child = "methods: ";
			for (auto i = node->children.begin(); i != node->children.end(); i++) {
				if ((*i)->type == "MethodDeclaration") {
					child += (*i)->value + " ";
				}
			}
            child += "\n";


        }else if (node->type == "MethodDeclaration") {
            lineno = node->lineno;
            name = node->value;
            scope = "method";
            child = "variables: ";
			auto i = node->children.begin();
			type = (*i)->value;

        }else if (node->type == "Parameter") {
			lineno = node->lineno;
			auto i = node->children.begin();
			name = (*i)->value;
			scope = "Parameter";
			type = (*i)->type;
			child = "";
		}


        if (scope == "global" || scope == "class" || scope == "method") {
			for (auto i = node->children.begin(); i != node->children.end(); i++) {
				if ((*i)->type == "MethodDeclaration" || (*i)->type == "ClassDeclaration" || (*i)->type == "Parameter") {
					ST* child = new ST();
					children.push_back(child);
					child->traverse(*i);
				}
			}
		}
    }
    
	void generateDOT(ST* node, ofstream &out, const string& inputFilename) {
		if (!node) return;
	
		// Generate label with parent name and children inside it (for non-variable nodes)
		string label = "";
		if (node->type == "Goal") {
			label = "File name: " + inputFilename;
		}else{
			label = "name: " + node->name + "\\n";
			label +=  "type: " + node->type + "\\n";
			label += "scope: " + node->scope;
		}
		label += "\\n\\n" + node->child;
	
		out << "\"" << node << "\" [label=\"" << label << "\", shape=box];\n";
	
		// Only create child edges if the node is NOT a variable declaration
		if (node->type != "VarDeclaration") {
			for (auto child : node->children) {
				out << "\"" << node << "\" -> \"" << child << "\";\n";
				generateDOT(child, out, inputFilename);
			}
		}
	}
	
		
	void exportToDot(const string& filename, const string& inputFilename) {
		ofstream out(filename);
		if (!out) {
			cerr << "Error: Could not open file " << filename << " for writing.\n";
			return;
		}
		
		out << "digraph AST {\n";
		out << "  rankdir=TB;\n"; // Top to Bottom layout
	
		int nodeCount = 0;
		generateDOT(this, out, inputFilename);
	
		out << "}\n";
		out.close();
	}

	ST* find(string name, string scope) {
		for (auto i = children.begin(); i != children.end(); i++) {
			if ((*i)->name == name && (*i)->scope == scope) {
				return *i; 
			}
			ST* node = (*i)->find(name, scope);
			if (node) {
				return node;
			}
		}
		return nullptr;  // Return nullptr if not found
	}
	




};
#endif // SYMBOLTABLE_H