#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

class Tac {
    public:
        string op, lhs, rhs, result;
    
        Tac() : op(""), lhs(""), rhs(""), result("") {}
        Tac(string _op, string _lhs, string _rhs, string _result)
            : op(_op), lhs(_lhs), rhs(_rhs), result(_result) {}
    
        void dump() {
            printf("%s := %s %s %s\n", result.c_str(), lhs.c_str(), op.c_str(), rhs.c_str());
        }
    };
    

class Copy : public Tac {
public:
    Copy(string _y, string _result)
        : Tac("", _y, "", _result) {}
};

class BBlock {
    public:
        string name;
        list<Tac> instructions;
        Tac condition;
        BBlock *trueExit = nullptr;
        BBlock *falseExit = nullptr;
        BBlock() : trueExit(nullptr), falseExit(nullptr) {}
    
        void dump() {
            printf("%s:\n", name.c_str());
            for (auto &i : instructions) {
                i.dump();
            }
        }
};

int tempVarCount = 0;
string genName() {
    return "_t" + to_string(tempVarCount++);
}
int blockCount = 0;
string genBlockName() {
    return "block_" + to_string(blockCount++);
}


class CFG {
private:
    list<BBlock *> methodBlocks;

public:

    string expression(Node* node, BBlock* block, ST* classSt){
        string op = node->value;
        string rhs;
        string lhs;
        auto it = node->children.begin();
        if ((*it)->type.find("Expression") != string::npos){
            lhs = expression(*it, block, classSt);
        
        }else if ((*it)->type == "MethodCall"){
            method_call(*it, block, classSt);
            block->instructions.back().result = "result";
            lhs = "result";

        }else{
            lhs = (*it)->value;
        }

        if ((*(++it))->type.find("Expression") != string::npos){
            rhs = expression(*it, block, classSt);
        }else if ((*it)->type == "MethodCall"){
            method_call(*it, block, classSt);
            block->instructions.back().result = "result";
            rhs = "result";

        }else{
            rhs = (*it)->value;
        }

        string result = genName();
        block->instructions.push_back(Tac(op, lhs, rhs, result));   

        return result;
    }
 
    void assignmentBlock(Node* node, BBlock* block, ST* classSt){
        string lhs, rhs;
        auto it = node->children.begin();

        lhs = (*it)->value;  
        it++;

        if (node->children.size()==2){
            if ((*it)->type == "Identifier" || (*it)->type == "int" || (*it)->type == "boolean")
                block->instructions.push_back(Copy((*it)->value, lhs));

            if ((*it)->type == "LogicalNot")
                block->instructions.push_back(Copy("!" + (*it)->children.front()->value, lhs));
            
        }
        if ((*it)->type == "ArrayAccess"){
            string array = (*it)->children.front()->value;
            string index = (*it)->children.back()->value;
            block->instructions.push_back(Copy(array + "[" + index + "]", lhs));
        }
        if (node->type == "ArrayAssignment"){
            auto it = node->children.begin();
            string array = (*it)->value;
            string index = (*(++it))->value;
            string value;
            if ((*(++it))->type == "ArrayLength")
                value = "length " + (*it)->children.front()->value;
            else
                value = (*it)->value;
            block->instructions.push_back(Copy(value, array + "[" + index + "]"));
        }
        if ((*it)->type == "Object_Instantiation"){
            string type = (*it)->children.front()->value;
            block->instructions.push_back(Copy("new " + type, lhs));
        }
        if ((*it)->type == "    "){
            string size = (*it)->children.back()->value;
            block->instructions.push_back(Copy("new , " + size , lhs));
        }
        if ((*it)->type == "PLUSExpression" || (*it)->type == "SUBExpression" || (*it)->type == "MULExpression" || (*it)->type == "LogicalExpression" || (*it)->type == "RelationalExpression"){
            expression(*it, block, classSt);
        }
        if ((*it)->type == "MethodCall"){
            method_call(*it, block, classSt);
            block->instructions.back().result = lhs;
        }     
    }
    
    Tac* method_call(Node* node, BBlock* block, ST* classSt){
        auto method = node->children.begin();
        Node * object = *(++method);
        method--;
        
        int n_parameters = node->children.size() - 2;
        Tac* right = new Tac();
        right->lhs = "call";
        right->rhs = to_string(n_parameters);    
        
        auto it = node->children.begin();
        advance(it, 2);
        for (int i = 0; i < n_parameters; i++){
            if ((*it)->type == "MethodCall"){
                method_call(*it, block, classSt);
            }
        }

        if (object->type == "Object_Instantiation"){
            right->op = object->children.front()->value + "." + (*method)->value + ",";
            string type = right->op.substr(0, right->op.find("."));
            block->instructions.push_back(Tac("new", "", type, ""));
            block->instructions.push_back(*right);
        }

        else if (object->type == "This"){
            string methodName = classSt->find((*method)->value, "method")->name;
            right->op = classSt->name + "." + methodName + ",";
            block->instructions.push_back(*right);
        }

        else if (object->type == "Identifier"){
            cout << object->value << endl;
            string type = classSt->find(object->value, "variable")->type;
            right->op = type + "." + (*method)->value + ",";
            block->instructions.push_back(*right);
        }

        else {    //(object->type == "MethodCall"){
            right = method_call(object, block, classSt);
            string objectName = right->op.substr(0, right->op.find("."));
            right->op = objectName + "." + (*method)->value + ",";
            right->rhs = to_string(n_parameters);
            block->instructions.push_back(*right);
        }

        return right;
    }

    BBlock* ifStatement(Node* node, BBlock* block1, ST* classSt){
        BBlock* expressionBlock = new BBlock();
        expressionBlock->name = genBlockName();
        block1->trueExit = expressionBlock;
        block1->instructions.push_back(Tac("", "", "goto", expressionBlock->name));

        auto expression = node->children.begin();
        string op = (*expression)->value;
        auto it = (*expression)->children.begin();
        BBlock *tBlock = new BBlock();
        tBlock->name = genBlockName();
        
        Node* trueNode = *(++expression);
        BBlock *fBlock = new BBlock();
        fBlock->name = genBlockName();
        BBlock *joinBlock = new BBlock();
        joinBlock->name = genBlockName();
        
        expressionBlock->instructions.push_back(Tac(op, (*(--it))->value, (*(++it))->value + "  iffalse goto ", fBlock->name));
        expressionBlock->trueExit = tBlock;
        expressionBlock->falseExit = fBlock;
        if (trueNode->type == "Block"){
            for (auto ifInstance = trueNode->children.begin(); ifInstance != trueNode->children.end(); ifInstance++)   //children of methods
                tBlock = runMethodBody(*ifInstance, tBlock, classSt);
        }else
            tBlock = runMethodBody(trueNode, tBlock, classSt);
        tBlock->trueExit = joinBlock;
        tBlock->instructions.push_back(Tac("", "", "goto", joinBlock->name));
        Node* falseNode = *(++expression);
        if (falseNode->type == "Block"){
            for (auto ifInstance = falseNode->children.begin(); ifInstance != falseNode->children.end(); ifInstance++)   //children of methods
                fBlock = runMethodBody(*ifInstance, fBlock, classSt);
        }else
            fBlock = runMethodBody(falseNode, fBlock, classSt);
        fBlock->trueExit = joinBlock; 
        fBlock->instructions.push_back(Tac("", "", "goto", joinBlock->name));
      
        return joinBlock;
    }

    BBlock* whileStm(Node* node, BBlock* block1, ST* classSt){
        BBlock* expressionBlock = new BBlock();
        expressionBlock->name = genBlockName();
        block1->trueExit = expressionBlock;
        block1->instructions.push_back(Tac("", "", "goto", expressionBlock->name));
        auto expression = node->children.begin();
        string op = (*expression)->value;
        auto it = (*expression)->children.begin();
        BBlock *body = new BBlock();
        body->name = genBlockName();
        
        BBlock *joinBlock = new BBlock();
        joinBlock->name = genBlockName();

        expressionBlock->instructions.push_back(Tac(op, (*(--it))->value, (*(++it))->value + "  iffalse goto ", joinBlock->name));
        expressionBlock->trueExit = body;
        expressionBlock->falseExit = joinBlock;

        if ((*(++expression))->type != "Block" )
            body = runMethodBody(*expression, body, classSt);

        for (auto whileInstance = (*expression)->children.begin(); whileInstance != (*expression)->children.end(); whileInstance++) {   //children of methods
            body = runMethodBody(*whileInstance, body, classSt);
        }

        body->trueExit = expressionBlock;

        return joinBlock;
    }


    void printStatment(Node* node, BBlock* block, ST* classSt){
        auto print = node->children.begin();
        if ((*print)->type == "MethodCall"){
            method_call(*print, block, classSt);
            block->instructions.back().result = "result";
            block->instructions.push_back(Tac("print", "", "result", ""));
        }else{
            cout << "no methodcall in print statement" << endl;
        }
    }

    BBlock* runMethodBody(Node* node, BBlock* block, ST* classSt){
        if (node->type == "Parameter"){
            string param = node->children.front()->value;
            block->instructions.push_back(Tac("param", "", param, ""));
        }

        if (node->type == "Assignment" || node->type == "ArrayAssignment"){   // check for variable duplicate in methods
            assignmentBlock(node, block, classSt);
        }

        if (node->type == "Print_Statement")
            printStatment(node, block, classSt);
        
        if (node->type == "IfStatement"){
            block = ifStatement(node, block, classSt);
        }
        if (node->type == "WhileStatement"){
            block = whileStm(node, block, classSt);
        }
        if (node->type == "Return"){
            auto it = node->children.begin();
            if ((*it)->type == "Object_Instantiation"){
                string type = (*it)->children.front()->value;
                block->instructions.push_back(Tac("new", "", type, "return"));
            }
            else if ((*it)->type == "MethodCall"){
                method_call(*it, block, classSt);
                block->instructions.back().result = "result";
            }
            else
                block->instructions.push_back(Tac("", "", (*it)->value, "return"));
        }

        return block;
    }

    // traverse to draw the CFG
    void traverse(Node* node, ST* St){
        int classIndex = 0;
        for (auto cls = node->children.begin(); cls != node->children.end(); cls++) {   // each element class
            auto it = St->children.begin();          // store class symboltalbe
            advance(it, classIndex);
            ST* classSt = *it;
            classIndex++;
            for (auto clsInstance = (*cls)->children.begin(); clsInstance !=(*cls)->children.end(); clsInstance++) {  // each element clsInstance or variable
                if ((*clsInstance)->type == "MethodDeclaration"){ 

                    BBlock *blockmethod = new BBlock();
                    blockmethod->name = genBlockName();
                    methodBlocks.push_back(blockmethod);

                    for (auto methodInstance = (*clsInstance)->children.begin(); methodInstance != (*clsInstance)->children.end(); methodInstance++) {   //children of methods
                        blockmethod = runMethodBody(*methodInstance, blockmethod, classSt);
                        
                    }

                }

            }
        
        }
        writeDotFile();
    }

        
    int help_Write(BBlock* block, ofstream &out, set<string> &duplicateArrows){
        string label = block->name + " [label=\"" + block->name;
        if (duplicateArrows.insert(label).second)
            out << "    " << label << "\\n";
        else
            return -1;


        for (auto &i : block->instructions) {
            out << i.result << " := " << i.lhs << " " << i.op << " " << i.rhs << "\\n";
        }
        out << "\"];\n";

                
        if (block->trueExit){ 
            string edge = block->name + " -> " + block->trueExit->name;
            if (duplicateArrows.insert(edge).second)
                out << "    " << edge << " [xlabel=\"true\"];\n";
            
            help_Write(block->trueExit, out, duplicateArrows);
        }
        if (block->falseExit){
            string edge = block->name + " -> " + block->falseExit->name;
            if (duplicateArrows.insert(edge).second)
                out << "    " << edge << " [xlabel=\"false\"];\n";

            help_Write(block->falseExit, out, duplicateArrows);
        }

        return 0;
    }

    void writeDotFile(){
        ofstream out("cfg.dot");
        out << "digraph {\ngraph [splines=ortho]\nnode [shape=box]\n";
    
        for (auto block : methodBlocks) {
            // Define the block with a rectangular shape and label
            out << "    " << block->name << " [label=\"" << block->name << "\\n";
            for (auto &i : block->instructions) {
                out << i.result << " := " << i.lhs << " " << i.op << " " << i.rhs << "\\n";
            }
            out << "\"];\n";
 
            if (block->trueExit){
                out << "    " << block->name << " -> " << block->trueExit->name << " [xlabel=\"true\"];\n";
                set<string> duplicateArrow;
                help_Write(block->trueExit, out, duplicateArrow);
                
            }
            
        }



        out << "}\n";
        out.close();
    }

};