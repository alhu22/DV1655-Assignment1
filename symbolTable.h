#ifndef SYMBOL_H
#define SYMBOL_H

#include "Node.h"
#include <iostream>
#include <list>

using namespace std;


class AST {
    string type,name,scope, child;
    list<AST*> children;

public:
	AST(string t, string n, string s, string c) : type(t), name(n), scope(s), child(c) {}
	AST(){
		type = "uninitialised";
		name = "uninitialised";
		scope = "uninitialised";
	}

   
    void traverseAST(Node* root, AST* parent = NULL) {
		
        if (root->type == "Goal") {
			type = "Goal";
			name = "root";
			scope = "global";
			child = "classes: ";
			for (auto i = root->children.begin(); i != root->children.end(); i++)
				child += (*i)->value + " ";
        }
		else if (root->type == "ClassDeclaration") {
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
			for (auto i = root->children.begin(); i != root->children.end(); i++) {
				if ((*i)->type == "Type") {
					type = (*i)->value;
				}
				else if ((*i)->type == "Identifier") {
					name = (*i)->value;
				}
			}
			scope = "variable";
			child = "";	
		}
		if (scope == "global" || scope == "class" || scope == "method") {
			for (auto i = root->children.begin(); i != root->children.end(); i++) {
				if ((*i)->type == "VarDeclaration" || (*i)->type == "MethodDeclaration" || (*i)->type == "ClassDeclaration") {
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
		
		cout << "Graphviz DOT file generated: " << filename << endl;
	}
	

};

#endif
