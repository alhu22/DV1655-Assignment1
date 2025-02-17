#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <iostream>
#include <map>
#include "Node.h"

using namespace std;

class VariableEntry {
public:
    string name, type;
    VariableEntry(string n, string t) : name(n), type(t) {}
    void print(int indent) { cout << string(indent, ' ') << "Var: " << name << " : " << type << endl; }
};

class MethodEntry {
public:
    string name, returnType;
    map<string, VariableEntry*> variables;

    MethodEntry(string n, string r) : name(n), returnType(r) {}

    void print(int indent) {
        cout << string(indent, ' ') << "Method: " << name << " : " << returnType << endl;
        for (auto &v : variables) v.second->print(indent + 2);
    }
};

class ClassEntry {
public:
    string name;
    map<string, MethodEntry*> methods;

    ClassEntry(string n) : name(n) {}

    void print(int indent) {
        cout << string(indent, ' ') << "Class: " << name << endl;
        for (auto &m : methods) m.second->print(indent + 2);
    }
};

class SymbolTable {
public:
    map<string, ClassEntry*> classes;
    ClassEntry *currentClass = nullptr;
    MethodEntry *currentMethod = nullptr;

    void enterClass(string className);
    void enterMethod(string methodName, string returnType);
    void addVariable(string varName, string varType);
    void exitMethod();
    void exitClass();
    void print();
};

void traverseAST(Node* node, SymbolTable &symTable);

#endif
