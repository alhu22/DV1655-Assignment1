#ifndef SEMANTIC_H
#define SEMANTIC_H

//#include "symbolTable.h"
//#include "Node.h"
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <string>

using namespace std;

class Check {
private:
    std::string firstvar;
    AST* ast;
    Node* root;

public:
    Check(std::string v, AST* a, Node* r): firstvar(v), ast(a), root(r)  {}
    
    Check() {
        firstvar = "uninitialised";
        ast = NULL;
        root = NULL;
    }

    bool check_dublicate_var(AST* ast = NULL) {

        if (ast == NULL)
            ast = this->ast;
        

        if (ast->scope == "global"){
            std::multimap<std::string, int> classes;
            for (auto i = ast->children.begin(); i != ast->children.end(); i++) {
                if ((*i)->scope == "class") {
                    bool declare = false;
                    for (auto& id : classes) {
                        if(id.first == (*i)->name){
                            declare = true;
                            cerr << "@error at line " << (*i)->lineno << ": Duplicate class: " << (*i)->name << endl;
                        }
                    }
                    if (!declare)
                        classes.insert({(*i)->name, (*i)->lineno});
                    
                }
            }
        }

        if (ast->scope == "class"){
            std::multimap<std::string, int> variables;
            std::multimap<std::string, int> methods;
            for (auto i = ast->children.begin(); i != ast->children.end(); i++) {
                if ((*i)->scope == "variable") {
                    bool declare = false;
                    for (auto& id : variables) {
                        if(id.first == (*i)->name){
                            declare = true;
                            cerr << "@error at line " << (*i)->lineno << ": Duplicate variable: " << (*i)->name << endl;
                        }
                    }
                    if (!declare)
                        variables.insert({(*i)->name, (*i)->lineno});
                }
                std::multimap<std::string, int> parameters;
                std::multimap<std::string, int> methodVars;
                if ((*i)->scope == "method") {
                    bool declare = false;
                    for (auto& id : methods) {
                        if(id.first == (*i)->name){
                            declare = true;
                            cerr << "@error at line " << (*i)->lineno << ": Duplicate method: " << (*i)->name << endl;
                        }
                    }
                    if (!declare)
                        methods.insert({(*i)->name, (*i)->lineno});
                    

                    for (auto j = (*i)->children.begin(); j != (*i)->children.end(); j++) {
                        if ((*j)->scope == "Parameter") {
                            bool declare = false;
                            for (auto& id : parameters) {
                                if(id.first == (*j)->name){
                                    declare = true;
                                    cerr << "@error at line " << (*j)->lineno << ": Duplicate parameter: " << (*j)->name << endl;
                                }
                            }
                            if (!declare) {
                                parameters.insert({(*j)->name, (*j)->lineno});
                                methodVars.insert({(*j)->name, (*j)->lineno});
                            }
                        }
                        if ((*j)->scope == "variable") {
                            bool declare = false;
                            for (auto& id : variables) {
                                if(id.first == (*j)->name){
                                    declare = true;
                                    cerr << "@error at line " << (*j)->lineno << ": Duplicate variable: " << (*j)->name << endl;
                                }
                            }
                            for (auto& id : methodVars) {
                                if(id.first == (*j)->name){
                                    declare = true;
                                    cerr << "@error at line " << (*j)->lineno << ": Duplicate variable: " << (*j)->name << endl;
                                }
                            }
                            if (!declare)
                                variables.insert({(*j)->name, (*j)->lineno});
                            
                        }
                    }
                }
            }
             
        }

        for (auto i = ast->children.begin(); i != ast->children.end(); i++) {
            check_dublicate_var(*i);
        }
        return true;
    }

    void recursive_node(Node* node, AST* ast, string class_name = "", string method_name = "") {
        string type;
        if (node->type == "Identifier") {
            type = ast->lookup(node->value, class_name, method_name);
            if (type == "not found") {
                cerr << "@error at line " << node->lineno << ": Undeclared Identifier: " << node->value << endl;
            }
        }else if (node->type == "MethodCall" || node->type == "Object_Instantiation") {
            for (auto i = node->children.begin(); i != node->children.end(); i++) {
                recursive_node(*i, ast, "", "");
            }
        }
        else {
            for (auto i = node->children.begin(); i != node->children.end(); i++) {
                recursive_node(*i, ast, class_name, method_name);
            }
        }
    }

    void verify_identifiers(string class_name = "", string method_name = "") {
        for (auto i = root->children.begin(); i != root->children.end(); i++) {
            for (auto j = (*i)->children.begin(); j != (*i)->children.end(); j++) {
                for (auto k = (*j)->children.begin(); k != (*j)->children.end(); k++) {
                    if ((*k)->type != "VarDeclaration" && (*k)->type != "MethodDeclaration" && (*k)->type != "ClassDeclaration" && (*k)->type != "Parameter") {
                        class_name = (*i)->value;
                        method_name = (*j)->value;
                        recursive_node(*k, ast, class_name, method_name); // check for undeclared Identifier
                    }
                }
            
            }
        }
    }

    string help_assignment(Node* node, AST* ast, string class_name, string method_name, Node* left, Node* right) {
        string lefttype, righttype;
        if (right->type != "Int" )
            righttype = ast->lookup(right->value, class_name, method_name);
        if (left->type != "Int")
            lefttype = ast->lookup(left->value, class_name, method_name);
        if (left->type == "AddExpression" || left->type == "MultExpression" || left->type == "SubExpression" || left->type == "LogicalExpression") {
            auto it = left->children.begin();
            lefttype = help_assignment(left, ast, class_name, method_name, (*it), (*(++it)));
        }
        if (right->type == "AddExpression", right->type == "MultExpression", right->type == "SubExpression", right->type == "LogicalExpression") {
            auto it = right->children.begin();
            righttype = help_assignment(right, ast, class_name, method_name, (*it), (*(++it)));
        }
        if(right->type == "MethodCall") {
            for (auto i = right->children.begin(); i != right->children.end(); i++) {
                if ((*i)->type == "Identifier") {
                    righttype = ast->lookup((*i)->value, class_name, "");
                }
            }
        }
        if (righttype != lefttype) {
            cerr << "@error at line " << node->lineno << ": Type mismatch in assignment: " << left->value << " and " << right->value << endl;
            return "error";
        }
        return lefttype;
    }

    void type_cheking(){
        for (auto i = root->children.begin(); i != root->children.end(); i++) {
            for (auto j = (*i)->children.begin(); j != (*i)->children.end(); j++) {
                arraycheking((*j), (*i)->value, (*j)->value);
                for (auto k = (*j)->children.begin(); k != (*j)->children.end(); k++) {
                    if ((*k)->type == "Assignment") {
                        auto it = (*k)->children.begin();
                        Node* left = *it;
                        Node* right = *(++it);
                        cout << left->value << " " << right->value << endl;
                        help_assignment(*k, ast, (*i)->value, (*j)->value, left, right);
                    }
                }
            }
        }
    }

    void arraycheking(Node* node, string class_name, string method_name) {
        if (node->type == "MethodDeclaration"){
            auto j = node->children.begin();
            if((*j)->value == "int[]"){
                cerr << "@error at line " << node->lineno <<   ": Method cannot return an array" << endl;
            }
        }
        for (auto i = node->children.begin(); i != node->children.end(); i++) {
            if ((*i)->type == "MethodDeclaration"){
                auto j = (*i)->children.begin();
                if((*j)->value == "int[]"){
                    cerr << "@error at line " << (*i)->lineno <<   ": Method cannot return an array" << endl;
                }
            }
            if ((*i)->type == "ArrayAssignment") {
                auto j = (*i)->children.begin();
                Node* left = *j;
                Node* right = *(++j);
                Node* right2 = *(++j);
                if (right->type != "Int")
                    cerr << "@error at line " << right->lineno <<   ": Array size must be an integer" << endl;
                if (right2->type != "Int")
                    cerr << "@error at line " << right2->lineno <<   ": Array index must be an integer" << endl;
                string type = ast->lookup(left->value, class_name, method_name);
                if(type != "int[]" && type != "not found")
                    cerr << "@error at line " << left->lineno << ": " << left->value <<  " must be Array" << endl;
            }
            if ((*i)->type == "ArrayAccess") {
                auto j = (*i)->children.begin();
                if ((*(++j))->type != "Int")
                    cerr << "@error at line " << (*j)->lineno <<   ": Array index must be an integer" << endl;
            }

            arraycheking((*i), class_name, method_name);
        }
    }
};

#endif // SEMANTIC_H
