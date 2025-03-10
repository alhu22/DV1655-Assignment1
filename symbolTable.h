#ifndef SYMBOL_H
#define SYMBOL_H

//#include "Node.h"
#include <iostream>
#include <list>

using namespace std;

class AST {
	public:
	int id, lineno;
    string type,name,scope, child, value;
	Node* root;
    list<AST*> children;
	AST(int l, string t, string n, string s, string c, string v, Node* r) : lineno(l), type(t), name(n), scope(s), child(c), value(v), root(r) {}
	AST(){
		lineno = -1;
		type = "uninitialised";
		name = "uninitialised";
		scope = "uninitialised";
		child = "uninitialised";
		value = "uninitialised";
		root = NULL;
	}

   
    void traverseAST(Node* root = NULL, AST* parent = NULL) {

		if (root == NULL) {
			root = this->root;
		}
		
        if (root->type == "Goal") {
			lineno = root->lineno;
			type = "Goal";
			name = "root";
			scope = "global";
			child = "classes: ";
			for (auto i = root->children.begin(); i != root->children.end(); i++)
			child += (*i)->value + " ";
		}
		else if (root->type == "ClassDeclaration") {
			lineno = root->lineno;
			name = root->value;
			scope = "class";
			type = "";
			child = "methods: ";
			for (auto i = root->children.begin(); i != root->children.end(); i++) {
				if ((*i)->type == "MethodDeclaration") {
					child += (*i)->value + " ";
				}
			}
			child += "\n";
			child += "variables: ";
			for (auto i = root->children.begin(); i != root->children.end(); i++) {
				if ((*i)->type == "VarDeclaration") {
					for (auto j = (*i)->children.begin(); j != (*i)->children.end(); j++){
						if ((*j)->type == "Identifier") {
							child += (*j)->value + " ";
						}
					}
				}
			}
		}

		else if (root->type == "MethodDeclaration") {
			lineno = root->lineno;
			name = root->value;
			scope = "method";
			child = "variables: ";
			for (auto i = root->children.begin(); i != root->children.end(); i++) {
				if ((*i)->type == "Type") {
					type = (*i)->value;
				}
				if ((*i)->type == "VarDeclaration") {
					for (auto j = (*i)->children.begin(); j != (*i)->children.end(); j++){
						if ((*j)->type == "Identifier") {
							child += (*j)->value + " ";
						}
					}
				}
			}
		}

		else if (root->type == "VarDeclaration") {
			lineno = root->lineno;
			auto i = root->children.begin();
			name = (*i)->value;
			type = (*i)->type;
			scope = "variable";
			child = "";	
		}

		else if (root->type == "Parameter") {
			lineno = root->lineno;
			auto i = root->children.begin();
			name = (*i)->value;
			type = (*i)->type;
			scope = "Parameter";
			child = "";
		}
		if (scope == "global" || scope == "class" || scope == "method") {
			for (auto i = root->children.begin(); i != root->children.end(); i++) {
				if ((*i)->type == "VarDeclaration" || (*i)->type == "MethodDeclaration" || (*i)->type == "ClassDeclaration" || (*i)->type == "Parameter") {
					AST* child = new AST();
					children.push_back(child);
					child->traverseAST(*i, this);
				}
			}
		}
    }

	void generateDOT(AST* node, ofstream &out, const string& inputFilename) {
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

	// a function returning An AST node adress



	// type of name
	string lookup(string name, string class_name = "", string method_name = "") {
		string type = "not found";
		// cout << name << " " << class_name << " " << method_name << endl;
		for (auto i = children.begin(); i != children.end(); i++) {
			if((*i)->name == class_name){
				for (auto j = (*i)->children.begin(); j != (*i)->children.end(); j++) {  // each element method or variable
					if ((*j)->name == method_name) {
						for (auto k = (*j)->children.begin(); k != (*j)->children.end(); k++) {
							if ((*k)->name == name) {
								type = (*k)->type;
								return type;
							}
						}
					}					
					if ((*j)->name == name) {
						type = (*j)->type;
						return type;
					}
				}
			}
			if (class_name == "" && method_name == "") {
				if ((*i)->name == name) {
					type = (*i)->type;
					return type;
				}
				for (auto j = (*i)->children.begin(); j != (*i)->children.end(); j++) {
					for (auto k = (*j)->children.begin(); k != (*j)->children.end(); k++) {
						if ((*k)->name == name) {
							type = (*k)->type;
							return type;
						}
					}
					if ((*j)->name == name) {
						type = (*j)->type;
						return type;
					}
				}
			}
		}
		return type;
	}

};

#endif
