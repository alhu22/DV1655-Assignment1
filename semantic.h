#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <string>

#include <typeinfo>

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

    void check_dublicate_var() {
        std::multimap<std::string, int> classes;
        for (auto i = ast->children.begin(); i != ast->children.end(); i++) {  // each element a class
            bool declare = false;
            for (auto& id : classes) {
                if(id.first == (*i)->name){
                    declare = true;
                    cerr << "@error at line " << (*i)->lineno << ": Duplicate class: " << (*i)->name << endl;
                }
            }
            if (!declare)
                classes.insert({(*i)->name, (*i)->lineno});

            std::multimap<std::string, int> global_variables;
            std::multimap<std::string, int> methods;
            for (auto j = (*i)->children.begin(); j != (*i)->children.end(); j++) {   // each element a method or variable
                if ((*j)->scope == "method") {
                    bool declare = false;
                    for (auto& id : methods) {
                        if(id.first == (*j)->name){
                            declare = true;
                            cerr << "@error at line " << (*j)->lineno << ": Duplicate method: " << (*j)->name << endl;
                        }
                    }
                    if (!declare)
                        methods.insert({(*j)->name, (*j)->lineno});

                    std::multimap<std::string, int> methodVars;
                    std::multimap<std::string, int> parameters;
                    for (auto k = (*j)->children.begin(); k != (*j)->children.end(); k++) {  // each element a parameter or variable
                        if ((*k)->scope == "Parameter") {
                            bool declare = false;
                            for (auto& id : parameters) {
                                if(id.first == (*k)->name){
                                    declare = true;
                                    cerr << "@error at line " << (*k)->lineno << ": Duplicate parameter: " << (*k)->name << endl;
                                }
                            }
                            if (!declare) {
                                parameters.insert({(*k)->name, (*k)->lineno});
                                methodVars.insert({(*k)->name, (*k)->lineno});
                            }
                        }
                        if ((*k)->scope == "variable") {
                            bool declare = false;
                            for (auto& id : methodVars) {
                                bool param = false;
                                for (auto& id : parameters) {
                                    if(id.first == (*k)->name){
                                        declare = true;
                                        param = true;
                                        cerr << "@error at line " << (*k)->lineno << ": Duplicate variable with parameter: " << (*k)->name << endl;
                                    }
                                }
                                if(id.first == (*k)->name && !param){
                                    declare = true;
                                    cerr << "@error at line " << (*k)->lineno << ": Duplicate variable: " << (*k)->name << endl;
                                }
                            }

                            if (!declare)
                                
                                methodVars.insert({(*k)->name, (*k)->lineno});
                            
                        }
                    
                    }
                    
                }
                if ((*j)->scope == "variable") {
                    bool declare = false;
                    for (auto& id : global_variables) {
                        if(id.first == (*j)->name){
                            declare = true;
                            cerr << "@error at line " << (*j)->lineno << ": Duplicate variable: " << (*j)->name << endl;
                        }
                    }
                    if (!declare)
                        global_variables.insert({(*j)->name, (*j)->lineno});
                }
            }
        }
    }

    void ArrayAssignment(Node* node = NULL, string class_name = "", string method_name = "") {
        if(node==NULL)
            node  = root;
        for (auto i = node->children.begin(); i != node->children.end(); i++) {

            if ((*i)->type == "ClassDeclaration")
                class_name = (*i)->value;
            
            if ((*i)->type == "MethodDeclaration"){     // check if return type is correct
                method_name = (*i)->value;
                
                auto j = (*i)->children.begin();
                string method_type = (*j)->value;
                if(method_type != "void"){
                    auto k = --(*i)->children.end();
                    string retun_type = (*k)->type;
                    bool type = false;
                    if (retun_type == "Identifier") {
                        retun_type = ast->lookup((*k)->value, class_name, method_name);
                        if (retun_type == "")
                            type = true;
                    }
                    if (retun_type == "This"){
                        retun_type = ast->lookup(class_name, "", "");
                        if (retun_type == "")
                            type = true;
                    }
                    if (retun_type == "Object_Instantiation"){
                        auto l = (*k)->children.begin();
                        retun_type = ast->lookup((*l)->value, "", "");
                        if (retun_type == "")
                            type = true;
                    }
                    
                    if (retun_type == "AddExpression" || retun_type == "MultExpression" || retun_type == "SubExpression")
                        retun_type = "int";

                    if (!type && retun_type != method_type){
                        cerr << "@error at line " << (*i)->lineno << ": mismatch" << endl;
                    }
                }
            
                
            }
        
            if ((*i)->type == "ArrayAssignment") {
                auto j = (*i)->children.begin();
                Node* listName = *j;
                Node* index = *(++j);
                Node* listValue = *(++j);
                if (ast->lookup(listName->value, class_name, method_name) != "int[]")
                    cerr << "@error at line " << listName->lineno << ": " << listName->value <<  " must be Array" << endl;
                string index_type = index->type;
                if (index_type == "Identifier")
                    index_type = ast->lookup(index->value, class_name, method_name);
                if (index_type != "int")
                    cerr << "@error at line " << index->lineno <<   ": Array size must be an integer" << endl;
            }
            if ((*i)->type == "ArrayAccess") {
                auto j = (*i)->children.begin();
                if (ast->lookup((*j)->value, class_name, method_name) != "int[]")
                    cerr << "@error at line " << (*j)->lineno << ": " << (*j)->value <<  " must be Array" << endl;

                string index_type = (*(++j))->type;
                if (index_type == "Identifier")
                    index_type = ast->lookup((*j)->value, class_name, method_name);
                if (index_type == "MethodCall"){
                    auto k = (*j)->children.begin();
                    if (ast->lookup((*k)->value, "", "") != "int")
                        cerr << "@error at line " << (*j)->lineno << ": " << (*k)->value <<  " must be Array" << endl;
                }else{
                    if (index_type != "int")
                        cerr << "@error at line " << (*j)->lineno <<   ": Array index must be an integer" << endl;
                }
            }
            if ((*i)->type == "ArrayLength") {
                auto j = (*i)->children.begin();
                if ((*j)->type == "MethodCall"){
                    auto k = (*j)->children.begin();
                    if (ast->lookup((*k)->value, "", "") != "int[]")
                        cerr << "@error at line " << (*j)->lineno << ": " << (*k)->value <<  " must be Array" << endl;
                }else{
                    if (ast->lookup((*j)->value, class_name, method_name) != "int[]"){
                        cerr << "@error at line " << (*j)->lineno << ": " << (*j)->value <<  " must be Array" << endl;
                    }
                }
            }
            ArrayAssignment((*i), class_name, method_name);
        }
    }

    string help_method_call(Node* node, string class_name, string method_name) {
        auto method = node->children.begin();
        Node * object = *(++method);
        method--;
        string method_type = ast->lookup((*method)->value, class_name, method_name);
        if (object->type == "Object_Instantiation") {
            auto class_n = object->children.begin();
            method_type = ast->lookup((*method)->value, (*class_n)->value, "");
            if (method_type == "not found") 
                cerr << "@error at line " << node->lineno << ": Undeclared: " << (*method)->type   << " "<<  (*method)->value << endl;
            if(ast->lookup((*class_n)->value, "", "") == "not found")
                cerr << "@error at line " << node->lineno << ": Undeclared: " << (*class_n)->type   << " "<< (*class_n)->value << endl;
        }else if (object->type == "This") {
            method_type = ast->lookup((*method)->value, class_name, "");
            if (method_type == "not found") 
                cerr << "@error at line " << node->lineno << ": Undeclared: " << (*method)->type   << " "<< (*method)->value << endl;
            
        }else if (object->type == "Identifier") {
            string object_name = object->value;
            string object_type = ast->lookup(object_name, class_name, method_name);
            method_type = ast->lookup((*method)->value, object_type, "");
            if (ast->lookup(object_type, "", "") == "not found")
                cerr << "@error at line " << node->lineno << ": Undeclared: " << (*method)->type  << " " << (*method)->value << endl;
            if(object_name == "not found")
                cerr << "@error at line " << node->lineno << ": Undeclared: " << object->value << endl;
        } else{
            help_method_call(object, class_name, method_name);
        }
        return method_type;
    }
    void help_verify_identifiers(Node* node, string class_name = "", string method_name = "") {    
        if (node->type == "Assignment") { 
            auto it = node->children.begin();
            string left_type = ast->lookup((*it)->value, class_name, method_name);
            cout << left_type << " " << (*it)->value << " " << (*it)->lineno << " " << class_name << " " << method_name << endl;
            if(left_type == "not found")
                cerr << "@error at line " << (*it)->lineno << ": Undeclared: " << (*it)->type << " " << (*it)->value << endl;
            
            if ((*(++it))->type == "MethodCall") {
                string method_type = help_method_call((*it), class_name, method_name);
                if (left_type != method_type)
                    cerr << "@error at line " << node->lineno << ": Type mismatch in assignment: " << endl;
            }else if ((*it)->type == "Identifier") {
                if(left_type == "not found")
                    cerr << "@error at line " << (*it)->lineno << ": Undeclared: " << (*it)->type << " " << (*it)->value << endl;
                if (left_type != ast->lookup((*it)->value, class_name, method_name))
                    cerr << "@error at line " << node->lineno << ": Type mismatch in assignment: " << endl;
            }
        }
    }  

    void verify_identifiers() {
        for (auto i = root->children.begin(); i != root->children.end(); i++) {   // each element class
            for (auto j = (*i)->children.begin(); j != (*i)->children.end(); j++) {  // each element method or variable
                for (auto k = (*j)->children.begin(); k != (*j)->children.end(); k++) {   //children of methods
                    if ((*k)->type != "VarDeclaration" && (*k)->type != "MethodDeclaration" && (*k)->type != "ClassDeclaration" && (*k)->type != "Parameter") {
                        string class_name = (*i)->value;
                        string method_name = (*j)->value;
                        help_verify_identifiers(*k, class_name, method_name); // check for undeclared Identifier
                    }
                    // else if ((*k)->type == "VarDeclaration") {
                    //     auto it = (*k)->children.begin();
                    //     string var_type = ast->lookup((*it)->type, "", "");
                    //     cout << (*it)->type << " " << (*it)->value << " " << (*k)->lineno <<  endl;
                    //     // if (var_type == "not found" && (*it)->type != "int" && (*it)->type != "boolean" && (*it)->type != "int[]")
                    //     //     cerr << "@error at line " << (*k)->lineno << ": Undeclared: " << (*k)->type << " " << (*k)->value << endl;
                    // }
                }
                if ((*j)->type == "VarDeclaration") {
                    auto n = (*j)->children.begin();
                    string var_type = ast->lookup((*n)->type, "", "");
                    if (var_type == "not found" && (*n)->type != "int" && (*n)->type != "boolean" && (*n)->type != "int[]")
                        cerr << "@error at line " << (*j)->lineno << ": Undeclared: " << (*n)->type << " " << (*n)->value << endl;
                }
            }
        }
    }


    string help_assignment(Node* node, AST* ast, string class_name, string method_name, Node* left, Node* right) {
        string lefttype, righttype;
        if (right->type != "Int")
            righttype = ast->lookup(right->value, class_name, method_name);
        if (right->type == "Boolean" || right->type == "String"){
            left->value = right->value;    // need to fix left should be AST taking ne value
        }else{
            righttype = ast->lookup(right->value, class_name, method_name);
        } 
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
        for (auto i = root->children.begin(); i != root->children.end(); i++) {   // each element class
            AST* classAst;
            for (auto a = ast->children.begin(); a != ast->children.end(); a++){
                if ((*a)->name == (*i)->value)
                    classAst = *a;
            }
            for (auto j = (*i)->children.begin(); j != (*i)->children.end(); j++) {  // each element method or variable
                AST* methodAst;
                for (auto a = classAst->children.begin(); a != classAst->children.end(); a++){
                    if ((*a)->name == (*i)->value)
                        methodAst = *a;
                }
                if ((*j)->type == "MethodDeclaration"){
                    auto n = (*j)->children.begin();
                    if((*n)->value == "int[]")
                        cerr << "@error at line " << (*j)->lineno <<   ": Method cannot return an array" << endl;
                }
                for (auto k = (*j)->children.begin(); k != (*j)->children.end(); k++) {  // each elements are Assignment, ArrayAssignment, ArrayAccess, IfStatment 
                    if ((*k)->type == "Assignment") {
                        auto it = (*k)->children.begin();
                        Node* left = *it;
                        Node* right = *(++it);
                        help_assignment(*k, ast, (*i)->value, (*j)->value, left, right);
                    }
                    if ((*k)->type == "ArrayAssignment") {
                        auto j = (*i)->children.begin();
                        Node* left = *j;
                        Node* index = *(++j);
                        Node* right = *(++j);
                        string type = ast->lookup(left->value, (*i)->value, (*j)->value);
                        if(type != "int[]")
                            cerr << "@error at line " << left->lineno << ": " << left->value <<  " must be Array" << endl;
                        
                        if (index->type != "Int")
                            if (ast->lookup(index->value, (*i)->value, (*j)->value) != "int")
                                cerr << "@error at line " << index->lineno <<   ": Array size must be an integer" << endl;
                        
                        if (right->type != "Int")
                            cerr << "@error at line " << right->lineno <<   ": Array index must be an integer" << endl;
                    }
                }
            }
        }
    }

};

#endif // SEMANTIC_H
