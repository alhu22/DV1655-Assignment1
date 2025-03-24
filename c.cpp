#include <iostream>
#include <set>
#include <string>

int main() {
    std::set<std::string> mySet;

    auto result1 = mySet.insert("Hello");
    auto result2 = mySet.insert("Hello"); // Duplicate insertion

    std::cout << "First insert successful? " << result1.second << std::endl; // true
    std::cout << "Second insert successful? " << result2.second << std::endl; // false

    
    if (object->type == "Object_Instantiation")
    right->op = object->children.front()->value + "." + (*method)->value + ",";

    if (object->type == "This"){
        string methodName = classSt->find((*method)->value, "method")->name;
        right->op = classSt->name + "." + methodName + ",";
    }

    if (object->type == "Identifier"){
        string type = classSt->find(object->value, "variable")->type;
        right->op = type + "." + (*method)->value + ",";
    }

    return 0;
}
