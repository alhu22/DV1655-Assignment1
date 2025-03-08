#ifndef CHECK_H
#define CHECK_H

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

    void ArrayAccess(Node* node, string class_name, string method_name) {
        auto j = node->children.begin();
        if ((*j)->type == "MethodCall"){
            string method_type = help_method_call((*j), class_name, method_name);
            if (method_type != "int[]")
                cerr << "@error at line " << (*j)->lineno << ": " << (*j)->value <<  " must be Array" << endl;
        }else if (ast->lookup((*j)->value, class_name, method_name) != "int[]")
            cerr << "@error at line " << (*j)->lineno << ": " << (*j)->value <<  " must be Array" << endl;

        string index_type = (*(++j))->type;
        if (index_type == "Identifier"){
            index_type = ast->lookup((*j)->value, class_name, method_name);
        }else if (index_type == "AddExpression" || index_type == "MultExpression" || index_type == "SubExpression"){
            index_type = expression((*j), class_name, method_name);
        }
        if (index_type != "int")
            cerr << "@error at line " << (*j)->lineno <<   ": Array index must be an integer" << endl;
    }

    void ArrayAssignment(Node* node, string class_name = "", string method_name = "") {
        // if(node==NULL)
        //     node  = root;
        // for (auto i = node->children.begin(); i != node->children.end(); i++) {
        //     if ((*i)->type == "ClassDeclaration")
        //         class_name = (*i)->value;
        //     if ((*i)->type == "MethodDeclaration"){     // check if return type is correct
        //         method_name = (*i)->value;
        //         // check_return((*i), class_name, method_name);
        //     }
        if (node->type == "ArrayAssignment") {
            auto j = node->children.begin();
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
        if (node->type == "ArrayAccess") {
            ArrayAccess(node, class_name, method_name);
        }
        if (node->type == "ArrayLength") {
            auto j = node->children.begin();
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
        
        //     ArrayAssignment((*i), class_name, method_name);
        // }
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
            if(method_type == "not found")
                cerr << "@error at line " << node->lineno << ": Undeclared: " << (*method)->type  << " " << (*method)->value << endl;
            if (ast->lookup(object_type, "", "") == "not found")
                cerr << "@error at line " << node->lineno << ": Undeclared: " << (*method)->type  << " " << (*method)->value << endl;
            if(object_name == "not found")
                cerr << "@error at line " << node->lineno << ": Undeclared: " << object->value << endl;
        } else{
            help_method_call(object, class_name, method_name);
        }
        return method_type;
    }

    string expression(Node* node, string class_name, string method_name) {
        string type = "int";
        for (auto i = node->children.begin(); i != node->children.end(); i++) {
            if ((*i)->type == "AddExpression" || (*i)->type == "MultExpression" || (*i)->type == "SubExpression" || (*i)->type == "LogicalExpression") {
                type = expression(*i, class_name, method_name);
            }else if ((*i)->type == "MethodCall") {
                type = help_method_call((*i), class_name, method_name);
            }else if ((*i)->type == "Identifier") {
                type = ast->lookup((*i)->value, class_name, method_name);
                if (type == "not found")
                    cerr << "@error a   t line " << (*i)->lineno << ": Undeclared: " << (*i)->type << " " << (*i)->value << endl;
            }
        }
        if (node->type == "AddExpression" || node->type == "MultExpression" || node->type == "SubExpression") {
            if (type == "boolean" || type == "int[]")
                type = "miss match";
        }
        if (node->type == "RelationalExpression"){
            if (type == "boolean" || type == "int[]"){
                type = "miss match";
            }else{
                type = "boolean";
            }
        }
        if (node->type == "LogicalExpression" || node->type == "LogicalNot")
            if (type != "boolean")
                type = "miss match";
        return type;
    }

    void help_verify_identifiers(Node* node, string class_name = "", string method_name = "") {    
        if (node->type == "Assignment") { 
            auto it = node->children.begin();
            string left_type = ast->lookup((*it)->value, class_name, method_name);
            string right_type;
            if(left_type == "not found")
                cerr << "@error at line " << (*it)->lineno << ": Undeclared: " << (*it)->type << " " << (*it)->value << endl;
            
            if ((*(++it))->type == "MethodCall") {
                right_type = help_method_call((*it), class_name, method_name);
                if (right_type != "not found" && left_type != right_type)
                    cerr << "@error at line " << node->lineno << ": Type mismatch in assignment: " << endl;
            }else if ((*it)->type == "Identifier") {
                right_type = ast->lookup((*it)->value, class_name, method_name);
                if(right_type == "not found"){
                    cerr << "@error at line " << (*it)->lineno << ": Undeclared: " << (*it)->type << " " << (*it)->value << endl;
                }else {
                    if (left_type != "not found" && left_type != right_type)
                        cerr << "@error at line " << node->lineno << ": Type mismatch in assignment: " << endl;
                }
            }
            else if ((*it)->type == "AddExpression" || (*it)->type == "MultExpression" || (*it)->type == "SubExpression" || (*it)->type == "LogicalExpression" || (*it)->type == "RelationalExpression" || (*it)->type == "LogicalNot") {
                right_type = expression((*it), class_name, method_name);
                if (right_type != "not found" && left_type != right_type)
                    cerr << "@error at line " << node->lineno << ": Type mismatch in assignment: " << endl;
            }else if ((*it)->type == "Object_Instantiation") {
                auto class_n = (*it)->children.begin();
                if (right_type == "not found" || left_type != (*class_n)->value)
                    cerr << "@error at line " << node->lineno << ": Type mismatch in assignment: " << endl;
            }
            // else if ((*it)->type == "ArrayLength") {
            //     if (left_type != "int")
            //         cerr << "@error at line " << node->lineno << ": Type mismatch in assignment: " << endl;
            // }
            // else if ((*it)->type.substr(0,5) == "Array") {
            //     ArrayAssignment((*it), class_name, method_name);
            // }
        }
    }

    void check_return(Node* node, string class_name, string method_name) {
        auto j = node->children.begin();
        string method_type = (*j)->value;
        if(method_type != "void"){
            auto k = --node->children.end();
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
            if (retun_type == "ArrayAccess"){
                ArrayAccess((*k), class_name, method_name);
                auto l = (*k)->children.begin();
                if ((*l)->type == "Identifier")
                    retun_type = ast->lookup((*l)->value, class_name, method_name); 
                if (retun_type == "int[]")
                    retun_type = "int";
            }
            if (retun_type == "MethodCall"){
                retun_type = help_method_call((*k), class_name, method_name);
            }
            
            if (retun_type == "AddExpression" || retun_type == "MultExpression" || retun_type == "SubExpression")
                retun_type = "int";
            
            if (!type && retun_type != method_type){
                cerr << "@error at line " << node->lineno << ": mismatch" << endl;
            }
        }
    }

    void check(){
        std::multimap<std::string, int> classes;
        std::multimap<std::string, int> errors;
        int class_index = 0;
        for (auto cls = root->children.begin(); cls != root->children.end(); cls++) {   // each element class
            bool declare = false;            // check for class duplicate
            for (auto& id : classes) {
                if(id.first == (*cls)->value){
                    declare = true;
                    cerr << "@error at line " << (*cls)->lineno << ": Duplicate class: " << (*cls)->value << endl;
                }
            }
            if (!declare)
            classes.insert({(*cls)->value, (*cls)->lineno});
        
            auto it = ast->children.begin();                                              // store the symboltalbe for class
            advance(it, class_index);
            AST* classAst = *it;
        
            class_index++;
            std::multimap<std::string, int> methods;            // check for method duplicate
            int method_index = 0;
            AST* methodAst;
            for (auto clsInstance = (*cls)->children.begin(); clsInstance !=(*cls)->children.end(); clsInstance++) {  // each element clsInstance or variable
                if ((*clsInstance)->type == "MethodDeclaration"){ 
                    bool declare = false;           // ceck for method duplicate       
                    for (auto& id : methods) {
                        if(id.first == (*clsInstance)->value){
                            declare = true;
                            cerr << "@error at line " << (*clsInstance)->lineno << ": Duplicate method: " << (*clsInstance)->value << endl;
                        }
                    }
                    if (!declare)
                        methods.insert({(*clsInstance)->value, (*clsInstance)->lineno});
                    
                    auto it = classAst->children.begin();                                              // store the symboltalbe for method
                    advance(it, method_index);
                    methodAst = *it;
                    method_index++;
                }
                
                if ((*clsInstance)->type == "VarDeclaration") {      // check for variable duplicate in class
                    auto it = (*clsInstance)->children.begin();
                    string var_type = ast->lookup((*it)->type, "", "");
                    if (var_type == "not found" && (*it)->type != "int" && (*it)->type != "boolean" && (*it)->type != "int[]" && (*it)->type != "String[]")
                        cerr << "@error at line " << (*clsInstance)->lineno << ": Undeclared: " << (*it)->type << " " << (*it)->value << endl;
                    if (classAst->find((*it)->value, "variable") != "not found"){
                        cerr << "@error at line " << (*clsInstance)->lineno << ": Duplicate variable: " << (*it)->value << endl;
                    }else{
                        AST*newVar = new AST((*clsInstance)->lineno, (*it)->type, (*it)->value, "variable", "child", (*it));
                        classAst->children.push_back(newVar);
                    }
                }
                for (auto methodInstance = (*clsInstance)->children.begin(); methodInstance != (*clsInstance)->children.end(); methodInstance++) {   //children of methods
                    if ((*methodInstance)->type == "VarDeclaration" || (*methodInstance)->type == "Parameter") {   // check for variable duplicate in methods
                        auto it = (*methodInstance)->children.begin();
                        string var_type = ast->lookup((*it)->type, "", "");
                        if (var_type == "not found" && (*it)->type != "int" && (*it)->type != "boolean" && (*it)->type != "int[]" && (*it)->type != "String[]")
                            cerr << "@error at line " << (*methodInstance)->lineno << ": Undeclared: " << (*it)->type << " " << (*it)->value << endl;
                    
                        if (methodAst->find((*it)->value, "variable") != "not found"){
                            cerr << "@error at line " << (*methodInstance)->lineno << ": Duplicate variable: " << (*it)->value << endl;
                        }else{
                            AST*newVar = new AST((*methodInstance)->lineno, (*it)->type, (*it)->value, "variable", "child", (*it));
                            methodAst->children.push_back(newVar);
                        }
                    }else{
                        string class_name = (*cls)->value;
                        string method_name = (*clsInstance)->value;
                        help_verify_identifiers(*methodInstance, class_name, method_name); // check for undeclared Identifier
                        if ((*methodInstance)->type.substr(0,5) == "Array") {
                            ArrayAssignment(*methodInstance, class_name, method_name);
                        }
                        
                    }
                }
                if ((*clsInstance)->type == "MethodDeclaration"){
                    check_return(*clsInstance, (*cls)->value, (*clsInstance)->value);
                }
            }
        }
    }

};

#endif // CHECK_H
