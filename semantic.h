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

    // first call to check_dublicate_var ast = class ast
    void check_dublicate_var(AST* ast = NULL) {

        if (ast == NULL) {
            ast = this->ast;
        }

        if (ast->scope == "class"){
            std::multimap<std::string, int> variables;
            std::multimap<std::string, int> methods;
            for (auto i = ast->children.begin(); i != ast->children.end(); i++) {
                if ((*i)->scope == "variable") {
                    variables.insert({(*i)->name, (*i)->lineno});
                }
                std::multimap<std::string, int> parameters;
                if ((*i)->scope == "method") {
                    methods.insert({(*i)->name, (*i)->lineno});

                    for (auto j = (*i)->children.begin(); j != (*i)->children.end(); j++) {
                        if ((*j)->scope == "Parameter") {
                            parameters.insert({(*j)->name, (*j)->lineno});
                        }
                    }
                    std:multimap<string, int> seen;
                    for (auto& id : parameters) {
                        for (auto& id2 : seen) {
                            if (id.first == id2.first) {
                                cout << "Error: Duplicate parameter: " << id.first << " at line " << id.second << " and " << id2.second << endl;
                            }
                        }
                        seen.insert(id);
                    }
                }
            }
            std::map<string, int> seen1;
            for (auto& id : variables) {
                for (auto& id2 : seen1) {
                    if (id.first == id2.first) {
                        cout << "Error: Duplicate variable: " << id.first << " at line " << id.second << " and " << id2.second << endl;
                    }
                }
                seen1[id.first] = id.second;
            }
            seen1.clear();
            for (auto& id : methods) {
                for (auto& id2 : seen1) {
                    if (id.first == id2.first) {
                        cout << "Error: Duplicate method: " << id.first << " at line " << id.second << " and " << id2.second << endl;
                    }
                }
                seen1[id.first] = id.second;
            }  
        }

        for (auto i = ast->children.begin(); i != ast->children.end(); i++) {
            check_dublicate_var(*i);
        }


    }

    void verify_identifiers(){
        
    }


};

#endif // SEMANTIC_H
