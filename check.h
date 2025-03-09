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
    std::map<int, std::string> errors; // Dictionary to store errors

public:
    Check(std::string v, AST* a, Node* r): firstvar(v), ast(a), root(r)  {}
    
    Check() {
        firstvar = "uninitialised";
        ast = NULL;
        root = NULL;
    }

    void ArrayAccess(Node* node, string class_name, string method_name, AST* classAst) {
        auto j = node->children.begin();
        if ((*j)->type == "MethodCall"){
            string method_type = help_method_call((*j), class_name, method_name,classAst);
            if (method_type != "int[]")
                errors[(*j)->lineno] = (*j)->value + " must be Array";
        }else if (ast->lookup((*j)->value, class_name, method_name) != "int[]")
            errors[(*j)->lineno] = (*j)->value + " must be Array";

        string index_type = (*(++j))->type;
        if (index_type == "Identifier"){
            index_type = ast->lookup((*j)->value, class_name, method_name);
        }else if (index_type == "AddExpression" || index_type == "MultExpression" || index_type == "SubExpression"){
            index_type = expression((*j), class_name, method_name, classAst);
        }
        if (index_type != "int")
            errors[(*j)->lineno] = "Array index must be an integer";
    }

    void ArrayAssignment(Node* node, string class_name, string method_name, AST* classAst) {
        if (node->type == "ArrayAssignment") {
            auto j = node->children.begin();
            Node* listName = *j;
            Node* index = *(++j);
            Node* listValue = *(++j);
            if (ast->lookup(listName->value, class_name, method_name) != "int[]")
                errors[listName->lineno] = listName->value + " must be Array";
            string index_type = index->type;
            if (index_type == "Identifier")
                index_type = ast->lookup(index->value, class_name, method_name);
            if (index_type != "int")
                errors[index->lineno] = "Array size must be an integer";
            
            if (listValue->type == "ArrayLength"){
                ArrayLength(listValue, class_name, method_name, classAst);
            }
        }
        if (node->type == "ArrayAccess") {
            ArrayAccess(node, class_name, method_name, classAst);
        }
    }

    string help_method_call(Node* node, string class_name, string method_name, AST* classAst) {
        auto method = node->children.begin();
        Node * object = *(++method);
        method--;
        string method_type = ast->lookup((*method)->value, class_name, method_name);
        if (object->type == "Object_Instantiation") {
            auto class_n = object->children.begin();
            method_type = ast->lookup((*method)->value, (*class_n)->value, "");
            if (method_type == "not found") 
                errors[node->lineno] = "Undeclared: " + (*method)->type + " " + (*method)->value;
            if(ast->lookup((*class_n)->value, "", "") == "not found")
                errors[node->lineno] = "Undeclared: " + (*class_n)->type + " " + (*class_n)->value;
        }else if (object->type == "This") {
            method_type = ast->lookup((*method)->value, class_name, "");
            if (method_type == "not found") 
                errors[node->lineno] = "Undeclared: " + (*method)->type + " " + (*method)->value;
            
        }else if (object->type == "Identifier") {
            string object_name = object->value;
            string object_type = ast->lookup(object_name, class_name, method_name);
            method_type = ast->lookup((*method)->value, object_type, "");
            if(method_type == "not found")
                errors[node->lineno] = "Undeclared: " + (*method)->type + " " + (*method)->value;
            if (ast->lookup(object_type, "", "") == "not found")
                errors[node->lineno] = "Undeclared: " + (*method)->type + " " + (*method)->value;
            if(object_name == "not found")
                errors[node->lineno] = "Undeclared: " + object->value;

            // handle parameter
            AST* classObject = classAst->find(object_name, "variable");
            classObject = ast->find(classObject->type, "class");
            classObject = ast->find((*method)->value, "method");
            if (classObject){
                int count_argument = 0;
                for (auto parameter = classObject->children.begin(); parameter != classObject->children.end(); parameter++) {
                    if ((*parameter)->scope == "Parameter"){
                        count_argument++;
                    }
                }
                // auto it = ast->children.begin();                                              // store the symboltalbe for class
                // advance(it, class_index);
                int count_parameter = node->children.size() - 2;
                
                if (count_argument != count_parameter){
                    errors[node->lineno] = "Argument mismatch in method call";
                }else{
                    auto param = classObject->children.begin();
                    auto argument = node->children.begin();
                    for (int i = 0; i < count_argument; i++){
                        advance(param, i);
                        advance(argument, i+2);
                        if ((*param)->type == "int" || (*param)->type == "boolean" || (*param)->type == "int[]" || (*param)->type == "String[]"){
                            // string argument_type;
                            // string param_type;
                            // cout << "argument_type: " << argument_type << " " << (*param)->type << endl;
                            // // if ((*param)->type == "Identifier")
                            // // param_type = ast->lookup((*param)->value, class_name, method_name);
                            // cout << "argument_type: " << argument_type << " " << (*param)->type << endl;
                            string argument_type = (*argument)->type;
                            if ((*param)->type != (*argument)->type){
                                if ((*argument)->type == "Identifier")
                                    argument_type = ast->lookup((*argument)->value, object_type, (*method)->value);
                                
                                if ((*param)->type != argument_type)
                                    errors[node->lineno] = "Type mismatch in method call";
                            }
                        }else{
                            string argument_type = ast->lookup((*argument)->value, class_name, method_name);
                            if (argument_type == "not found")
                                errors[(*argument)->lineno] = "Undeclared: " + (*argument)->type + " " + (*argument)->value;
                            if ((*param)->type != argument_type)
                                errors[node->lineno] = "Type mismatch in method call";
                        }
                    }
                }
            }
                    

        } else{
            help_method_call(object, class_name, method_name, classAst);
        }
        return method_type;
    }

    string expression(Node* node, string class_name, string method_name, AST* classAst) {
        string type = "int";
        for (auto i = node->children.begin(); i != node->children.end(); i++) {
            if ((*i)->type == "AddExpression" || (*i)->type == "MultExpression" || (*i)->type == "SubExpression" || (*i)->type == "LogicalExpression" || (*i)->type == "RelationalExpression") {
                type = expression(*i, class_name, method_name, classAst);
            }else if ((*i)->type == "MethodCall") {
                type = help_method_call((*i), class_name, method_name, classAst);
            }else if ((*i)->type == "Identifier") {
                type = ast->lookup((*i)->value, class_name, method_name);
                if (type == "not found")
                    errors[(*i)->lineno] = "Undeclared: " + (*i)->type + " " + (*i)->value;
            }else if ((*i)->type == "ArrayAccess"){
                ArrayAccess((*i), class_name, method_name, classAst);
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

    void ArrayLength(Node* node, string class_name, string method_name, AST* classAst){
        auto k = node->children.begin();
        if ((*k)->type == "ArrayAccess")
            ArrayAccess(*k, class_name, method_name, classAst);
        if (ast->lookup((*k)->value, class_name, method_name) != "int[]")
            errors[node->lineno] = node->value + " must be Array";
    }

    void Assignment(Node* node, string class_name, string method_name, AST* classAst) {    
        auto it = node->children.begin();
        string left_type = ast->lookup((*it)->value, class_name, method_name);
        string right_type;
        if(left_type == "not found")
            errors[(*it)->lineno] = "Undeclared: " + (*it)->type + " " + (*it)->value;
        
        if ((*(++it))->type == "MethodCall") {
            right_type = help_method_call((*it), class_name, method_name, classAst);
            if (right_type != "not found" && left_type != right_type)
                errors[node->lineno] = "Type mismatch in assignment";
        }else if ((*it)->type == "Identifier") {
            right_type = ast->lookup((*it)->value, class_name, method_name);
            if(right_type == "not found"){
                errors[(*it)->lineno] = "Undeclared: " + (*it)->type + " " + (*it)->value;
            }else {
                if (left_type != "not found" && left_type != right_type)
                    errors[node->lineno] = "Type mismatch in assignment";
            }
        }
        else if ((*it)->type == "AddExpression" || (*it)->type == "MultExpression" || (*it)->type == "SubExpression" || (*it)->type == "LogicalExpression" || (*it)->type == "RelationalExpression" || (*it)->type == "LogicalNot") {
            right_type = expression((*it), class_name, method_name, classAst);
            if (right_type != "not found" && left_type != right_type)
                errors[node->lineno] = "Type mismatch in assignment";
        }else if ((*it)->type == "Object_Instantiation") {
            auto class_n = (*it)->children.begin();
            if (left_type != (*class_n)->value)
                errors[node->lineno] = "Type mismatch in assignment";
        }else if ((*it)->type == "ArrayLength"){
            ArrayLength(*it, class_name, method_name, classAst);
            if (left_type != "int")
                errors[node->lineno] = "Type mismatch in assignment";
        
        }else if ((*it)->type == "Array_Instantiation"){
            auto index = ++(*it)->children.begin();
            if ((*index)->type != "int" && ast->lookup((*index)->value, class_name, method_name) != "int")
                errors[node->lineno] = "Type mismatch in assignment";
            if (left_type != "int[]")
                errors[node->lineno] = "Type mismatch in assignment";
        }
    }

    void check_return(Node* node, string class_name, string method_name, AST* classAst) {
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
                ArrayAccess((*k), class_name, method_name, classAst);
                auto l = (*k)->children.begin();
                if ((*l)->type == "Identifier")
                    retun_type = ast->lookup((*l)->value, class_name, method_name); 
                if (retun_type == "int[]")
                    retun_type = "int";
            }
            if (retun_type == "MethodCall"){
                retun_type = help_method_call((*k), class_name, method_name, classAst);
            }
            
            if (retun_type == "AddExpression" || retun_type == "MultExpression" || retun_type == "SubExpression")
                retun_type = "int";
            
            if (!type && retun_type != method_type){
                errors[node->lineno] = "mismatch";
            }
        }
    }

    void ifStatment(Node* node, string class_name, string method_name, AST* classAst){
        auto ifexpression = node->children.begin();
        expression(*ifexpression, class_name, method_name, classAst);
        for (auto instance = node->children.begin(); instance != node->children.end(); instance++){
            if ((*instance)->type == "IfStatement")
                ifStatment(*instance, class_name, method_name, classAst);
            if ((*instance)->type == "Assignment")
                Assignment(*instance, class_name, method_name, classAst);
            if ((*instance)->type.substr(0,5) == "Array")
                ArrayAssignment(*instance, class_name, method_name, classAst);
        }

    }

    void check(){
        std::multimap<std::string, int> classes;
        int class_index = 0;
        for (auto cls = root->children.begin(); cls != root->children.end(); cls++) {   // each element class
            bool declare = false;            // check for class duplicate
            for (auto& id : classes) {
                if(id.first == (*cls)->value){
                    declare = true;
                    errors[(*cls)->lineno] = "Duplicate class: " + (*cls)->value;
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
                            errors[(*clsInstance)->lineno] = "Duplicate method: " + (*clsInstance)->value;
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
                        errors[(*clsInstance)->lineno] = "Undeclared: " + (*it)->type + " " + (*it)->value;
                    
                    if (classAst->find((*it)->value, "variable")){  
                        errors[(*clsInstance)->lineno] = "Duplicate variable: 1 " + (*it)->value;
                    
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
                            errors[(*methodInstance)->lineno] = "Undeclared: " + (*it)->type + " " + (*it)->value;
                    
                        if (methodAst->find((*it)->value, "variable")){
                            errors[(*methodInstance)->lineno] = "Duplicate variable: " + (*it)->value;
                        }else{
                            AST*newVar = new AST((*methodInstance)->lineno, (*it)->type, (*it)->value, "variable", "child", (*it));
                            methodAst->children.push_back(newVar);
                        }
                    }else{
                        string class_name = (*cls)->value;
                        string method_name = (*clsInstance)->value;
                        if ((*methodInstance)->type == "Assignment")
                            Assignment(*methodInstance, class_name, method_name, classAst); // check for undeclared Identifier
                        if ((*methodInstance)->type.substr(0,5) == "Array")
                            ArrayAssignment(*methodInstance, class_name, method_name, classAst);
                        if ((*methodInstance)->type == "IfStatement")
                            ifStatment(*methodInstance, class_name, method_name, classAst);
                    }
                }
                if ((*clsInstance)->type == "MethodDeclaration")
                    check_return(*clsInstance, (*cls)->value, (*clsInstance)->value, classAst);
                
            }
        }

        // Print all errors sorted by line number
        for (const auto& error : errors) {
            cerr << "@error at line " << error.first << ": " << error.second << endl;
        }
    }

};

#endif // CHECK_H