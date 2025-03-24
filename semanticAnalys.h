#ifndef CHECK_H
#define CHECK_H

#include <iostream>
#include <map>
#include <string>

using namespace std;

class Check {
private:
    ST* St;
    Node* root;
    std::map<int, std::string> errors; // Dictionary to store errors

public:
    Check(ST* a, Node* r): St(a), root(r)  {}
    
    Check() {
        St = NULL;
        root = NULL;
    }

    void ArrayAccess(Node* node, ST* classSt) {
        auto j = node->children.begin();
        if ((*j)->type == "MethodCall"){
            string method_type = method_call((*j), classSt);
            if (method_type != "int[]")
                errors[(*j)->lineno] = (*j)->value + " must be Array";
        }else if (classSt->find((*j)->value, "variable")->type != "int[]")
            errors[(*j)->lineno] = (*j)->value + " must be Array";

        string index_type = (*(++j))->type;
        if (index_type == "Identifier"){
            index_type = classSt->find((*j)->value, "variable")->type;
        }else if (index_type == "PLUSExpression" || index_type == "MULExpression" || index_type == "SUBExpression"){
            index_type = expression((*j), classSt);
        }
        if (index_type != "int")
            errors[(*j)->lineno] = "Array index must be an integer";
    }

    void ArrayAssignment(Node* node, ST* classSt) {
        if (node->type == "ArrayAssignment") {
            auto j = node->children.begin();
            Node* listName = *j;
            Node* index = *(++j);
            Node* listValue = *(++j);
            if (classSt->find(listName->value, "variable")->type != "int[]")
                errors[listName->lineno] = listName->value + " must be Array";
            string index_type = index->type;
            if (index_type == "Identifier")
                index_type = classSt->find(index->value, "variable")->type;
            if (index_type != "int")
                errors[index->lineno] = "Array size must be an integer";
            
            if (listValue->type == "ArrayLength"){
                ArrayLength(listValue, classSt);
            }
        }
        if (node->type == "ArrayAccess") {
            ArrayAccess(node, classSt);
        }
    }

    string method_call(Node* node, ST* classSt) {
        auto method = node->children.begin();
        Node * object = *(++method);
        method--;
        string method_type = "initialize";
        string object_type;
        ST* classObject = NULL;
        ST* methodSTObject = NULL;
        if (object->type == "Object_Instantiation") {
            auto class_n = object->children.begin();
            classObject = St->find((*class_n)->value, "class");
            methodSTObject = classObject->find((*method)->value, "method");
            if (methodSTObject)
                method_type = methodSTObject->type;
            if (method_type == "not found") 
                errors[node->lineno] = "Undeclared: " + (*method)->type + " " + (*method)->value;

            ST* st = St->find((*class_n)->value, "class");
            if (st == NULL)
                errors[node->lineno] = "Undeclared: " + (*class_n)->type + " " + (*class_n)->value;

            classObject = St->find((*class_n)->value, "class");
            methodSTObject = classObject->find((*method)->value, "method");
    
        }else if (object->type == "This") {
            methodSTObject = classSt->find((*method)->value, "method");
            if (methodSTObject)
                method_type = methodSTObject->type;
            if (method_type == "not found") 
                errors[node->lineno] = "Undeclared: " + (*method)->type + " " + (*method)->value;

            classObject = classSt;
            methodSTObject = classObject->find((*method)->value, "method");

            
        }else if (object->type == "Identifier") {
            string object_name = object->value;
            object_type = classSt->find(object_name, "variable")->type;
            ST* st = St->find(object_type, "class");
            if (st != NULL)
                st = st->find((*method)->value, "method");
            else
                errors[node->lineno] = "Undeclared: " + (*method)->type + " " + (*method)->value;
            if (st != NULL)
                method_type = st->type;
            if(method_type == "not found")
                errors[node->lineno] = "Undeclared: " + (*method)->type + " " + (*method)->value;
            
            classObject = classSt->find(object_name, "variable");

            classObject = St->find(classObject->type, "class");
            methodSTObject = classObject->find((*method)->value, "method");
        } else{
            method_type = method_call(object, classSt);
            if (method_type != "int" && method_type != "boolean" && method_type != "int[]" && method_type != "String[]")
                method_type = St->find(method_type, "class")->find((*method)->value, "method")->type;   
        }

        // Handle parameters
        if (methodSTObject){
            int count_argument = 0;
            for (auto parameter = methodSTObject->children.begin(); parameter != methodSTObject->children.end(); parameter++) {
                if ((*parameter)->scope == "Parameter"){
                    count_argument++;
                }
            }
            int count_parameter = node->children.size() - 2;
            if (count_argument != count_parameter){
                errors[node->lineno] = "invalid number of parameters";
            }else{
                auto param = methodSTObject->children.begin();
                auto argument = node->children.begin();
                argument++;
                argument++;
                for (int i = 0; i < count_argument; i++){
                    if ((*argument)->type == "MethodCall") {
                        string argument_type = method_call((*argument), classSt);
                        if ((*param)->type != argument_type)
                            errors[node->lineno] = "Type mismatch in method call";
                    }else {
                        string argument_type = (*argument)->type;
                        if (argument_type == "Object_Instantiation"){
                            auto it = (*argument)->children.begin();
                            argument_type = (*it)->value;
                        }
                        if ((*param)->type != argument_type){
                            if (argument_type == "Identifier"){
                                ST* st = classSt->find((*argument)->value, "variable");
                                if (st != NULL)
                                    argument_type = st->type;
                            }
                            
                            if (argument_type=="This")
                                argument_type = classSt->name;
                            if (argument_type=="SUBExpression" || argument_type=="PLUSExpression" || argument_type=="MULExpression")
                            argument_type = "int";
                            if ((*param)->type != argument_type)
                                errors[node->lineno] = "Type mismatch in method call";
                        }
                    }
                    param++;
                    argument++;
                }
            }
        }                    
        return method_type;
    }

    string expression(Node* node, ST* classSt) {
        string type = "int";
        for (auto i = node->children.begin(); i != node->children.end(); i++) {
            if ((*i)->type == "PLUSExpression" || (*i)->type == "MULExpression" || (*i)->type == "SUBExpression" || (*i)->type == "LogicalExpression" || (*i)->type == "RelationalExpression") {
                type = expression(*i, classSt);

            }else if ((*i)->type == "MethodCall") {
                type = method_call((*i), classSt);
            }else if ((*i)->type == "Identifier") {
                ST* varnode = classSt->find((*i)->value, "variable");
                if (varnode != NULL)
                    type = varnode->type;
                if (type == "not found")
                    errors[(*i)->lineno] = "Undeclared: " + (*i)->type + " " + (*i)->value;
            }else if ((*i)->type == "ArrayAccess"){
                ArrayAccess((*i), classSt);
            }
            
            if (node->type == "PLUSExpression" || node->type == "MULExpression" || node->type == "SUBExpression") {
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
        }
        return type;
    }

    void ArrayLength(Node* node, ST* classSt){
        auto k = node->children.begin();
        if ((*k)->type == "ArrayAccess")
            ArrayAccess(*k, classSt);
        ST* varnode = classSt->find((*k)->value, "variable");
        string type;
        if (varnode != NULL)
            type = varnode->type;
        if (type != "int[]")
            errors[node->lineno] = node->value + " must be Array";
    }

    void Assignment(Node* node, ST* classSt) {    
        auto it = node->children.begin();
        ST* varnode = classSt->find((*it)->value, "variable");
        string left_type;
        if (varnode != NULL)
            left_type = varnode->type;
        else
            errors[(*it)->lineno] = "Undeclared: " + (*it)->type + " " + (*it)->value;

        string right_type;        
        if ((*(++it))->type == "MethodCall") {
            right_type = method_call((*it), classSt);
            if (right_type != "not found" && left_type != right_type)
                errors[node->lineno] = "Type mismatch in assignment";
        }else if ((*it)->type == "Identifier") {
            ST* st = classSt->find((*it)->value, "variable");
            if (st != NULL)
                right_type = st->type;

            if (left_type != right_type)
                errors[node->lineno] = "Type mismatch in assignment";
            
        }
        else if ((*it)->type == "PLUSExpression" || (*it)->type == "MULExpression" || (*it)->type == "SUBExpression" || (*it)->type == "LogicalExpression" || (*it)->type == "RelationalExpression" || (*it)->type == "LogicalNot") {
            right_type = expression((*it), classSt);
            if (right_type != "not found" && left_type != right_type)
                errors[node->lineno] = "Type mismatch in assignment";
        }else if ((*it)->type == "Object_Instantiation") {
            auto class_n = (*it)->children.begin();
            if (left_type != (*class_n)->value)
                errors[node->lineno] = "Type mismatch in assignment";
        }else if ((*it)->type == "ArrayLength"){
            ArrayLength(*it, classSt);
            if (left_type != "int")
                errors[node->lineno] = "Type mismatch in assignment";
        
        }else if ((*it)->type == "Array_Instantiation"){
            auto index = ++(*it)->children.begin();
            ST* st = classSt->find((*index)->value, "variable");
            if (st != NULL)
                right_type = st->type;

            if ((*index)->type != "int" && right_type != "int")
                errors[node->lineno] = "Type mismatch in assignment";
            if (left_type != "int[]")
                errors[node->lineno] = "Type mismatch in assignment";
        }
    }

    void check_return(Node* node, ST* classSt) {
        auto j = node->children.begin();
        string method_type = (*j)->value;
        if(method_type != "void"){
            auto l = --node->children.end();
            auto k = (*l)->children.begin();
            string retun_type = (*k)->type;
            bool type = false;
            if (retun_type == "Identifier") {
                ST* st = classSt->find((*k)->value, "variable");
                if (st != NULL)
                    retun_type = st->type;
                if (retun_type == "")
                    type = true;
            }
            if (retun_type == "This"){
                retun_type = classSt->name;
            }
            if (retun_type == "Object_Instantiation"){
                auto l = (*k)->children.begin();
                ST* st = St->find((*l)->value, "class");
                if (st != NULL)
                    retun_type = st->type;
                if (retun_type == "")
                    type = true;
            }
            if (retun_type == "ArrayAccess"){
                ArrayAccess((*k), classSt);
                auto l = (*k)->children.begin();
                if ((*l)->type == "Identifier"){
                    ST* st = classSt->find((*l)->value, "variable");
                    if (st != NULL)
                        retun_type = st->type;
                }
                if (retun_type == "int[]")
                    retun_type = "int";
            }
            if (retun_type == "MethodCall"){
                retun_type = method_call((*k), classSt);
            }
            
            if (retun_type == "PLUSExpression" || retun_type == "MULExpression" || retun_type == "SUBExpression")
                retun_type = "int";
            
            if (!type && retun_type != method_type){
                errors[node->lineno] = "mismatch";
            }
        }
    }

    void ifStatment(Node* node, ST* classSt){
        auto ifexpression = node->children.begin();
        // if ((*ifexpression)->type == "MethodCall"){
        //     string method_type = method_call((*ifexpression), classSt);
        //     if (method_type != "boolean")
        //         errors[(*ifexpression)->lineno] = "Type mismatch in if statement";
        // }else if ((*ifexpression)->type == "Identifier") {
        //     ST* st = classSt->find((*ifexpression)->value, "variable");
        //     if (st != NULL){
        //         if (st->type != "boolean")
        //             errors[(*ifexpression)->lineno] = "Type mismatch in if statement";
        //     }else
        //         errors[(*ifexpression)->lineno] = "Undeclared: " + (*ifexpression)->type + " " + (*ifexpression)->value;
        // }
        // else if ((*ifexpression)->type == "PLUSExpression" || (*ifexpression)->type == "MULExpression" || (*ifexpression)->type == "SUBExpression" || (*ifexpression)->type == "LogicalExpression" || (*ifexpression)->type == "RelationalExpression") {
        //     string type = expression((*ifexpression), classSt);
        //     cout << type << endl;
        //     if (type != "boolean")
        //         errors[(*ifexpression)->lineno] = "Type mismatch in if statement";
        // }

        string type = expression(*ifexpression, classSt);
        for (auto instance = node->children.begin(); instance != node->children.end(); instance++){
            if ((*instance)->type == "IfStatement")
                ifStatment(*instance, classSt);
            if ((*instance)->type == "Assignment")
                Assignment(*instance, classSt);
            if ((*instance)->type.substr(0,5) == "Array")
                ArrayAssignment(*instance, classSt);
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
        
            auto it = St->children.begin();          // store class symboltalbe
            advance(it, class_index);
            ST* classSt = *it;
            class_index++;

            std::multimap<std::string, int> methods;            // check for method duplicate
            int method_index = 0;
            ST* methodSt;
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
                    
                    auto it = classSt->children.begin();                                              // store the symboltalbe for method
                    advance(it, method_index);
                    methodSt = *it;
                    method_index++;
                }
                
                if ((*clsInstance)->type == "VarDeclaration") {      // check for variable duplicate in class
                    auto it = (*clsInstance)->children.begin();
                    string var_type = "not found";
                    ST* st = St->find((*it)->type, "class");
                    if (st != NULL)
                        var_type = st->type;
                    else if (var_type == "not found" && (*it)->type != "int" && (*it)->type != "boolean" && (*it)->type != "int[]" && (*it)->type != "String[]")
                        errors[(*clsInstance)->lineno] = "Undeclared: " + (*it)->type + " " + (*it)->value;
                    
                    if (classSt->find((*it)->value, "variable")){  
                        errors[(*clsInstance)->lineno] = "Duplicate variable: 1 " + (*it)->value;
                    
                    }else{
                        ST*newVar = new ST((*clsInstance)->lineno, (*it)->type, (*it)->value, "variable", "", (*it));
                        methodSt->child += (*it)->value + " ";
                        classSt->children.push_back(newVar);
                    }
                }
                for (auto methodInstance = (*clsInstance)->children.begin(); methodInstance != (*clsInstance)->children.end(); methodInstance++) {   //children of methods
                    if ((*methodInstance)->type == "VarDeclaration" || (*methodInstance)->type == "Parameter") {   // check for variable duplicate in methods
                        auto it = (*methodInstance)->children.begin();
                        string var_type = "not found";
                        ST* st = St->find((*it)->type, "class");
                        if (st != NULL)
                            var_type = st->type;
                        else if (var_type == "not found" && (*it)->type != "int" && (*it)->type != "boolean" && (*it)->type != "int[]" && (*it)->type != "String[]")
                            errors[(*methodInstance)->lineno] = "Undeclared: " + (*it)->type + " " + (*it)->value;
                    
                        if (methodSt->find((*it)->value, "variable")){
                            errors[(*methodInstance)->lineno] = "Duplicate variable: " + (*it)->value;
                        }else{
                            ST*newVar = new ST((*methodInstance)->lineno, (*it)->type, (*it)->value, "variable", "", (*it));
                            methodSt->child += (*it)->value + " ";
                            methodSt->children.push_back(newVar);
                        }
                    }else{
                        string class_name = (*cls)->value;
                        string method_name = (*clsInstance)->value;
                        if ((*methodInstance)->type == "Assignment")
                            Assignment(*methodInstance, classSt);
                        if ((*methodInstance)->type.substr(0,5) == "Array")
                            ArrayAssignment(*methodInstance, classSt);
                        if ((*methodInstance)->type == "IfStatement")
                            ifStatment(*methodInstance, classSt);
                    }
                }
                if ((*clsInstance)->type == "MethodDeclaration")
                    check_return(*clsInstance, classSt);
                
            }
        }

        // Print all errors sorted by line number
        for (const auto& error : errors) {
            cerr << "@error at line " << error.first << ": " << error.second << endl;
        }
    }

};

#endif // CHECK_H