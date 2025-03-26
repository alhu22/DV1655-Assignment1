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

        
        virtual string generate_code() {
            return "";
        }
    
        void dump() {
            printf("%s := %s %s %s\n", result.c_str(), lhs.c_str(), op.c_str(), rhs.c_str());
        }

        virtual ~Tac() {} // Ensure proper cleanup when deleting derived objects

    };
 
class Expression : public Tac {
    private:
        map<string, string> boolien = {
            {"true", "1"},
            {"false", "0"}
        };

public:
    Expression(string _op, string _lhs, string _rhs, string _result)
        : Tac(_op, _lhs, _rhs, _result) {}

    string generate_code() override {
        string out;

        if (isdigit(lhs[0]))
            out += "   iconst " + lhs + "\n";
        else if (lhs == "true" || lhs == "false")
            out += "   iconst " + boolien[lhs] + "\n";
        else
            out += "   iload " + lhs + "\n";

        if (isdigit(rhs[0]))
            out += "   iconst " + rhs + "\n";
        else if (rhs == "true" || rhs == "false")
            out += "   iconst " + boolien[rhs] + "\n";
        else
            out += "   iload " + rhs + "\n";

            
        if (op == "+")
            out += "   iadd\n";
        if (op == "-")
            out += "   isub\n";
        if (op == "*")
            out += "   imul\n";
        if (op == "<")
            out += "   ilt\n";
        if (op == ">")
            out += "   igt\n";
        if (op == "&&")
            out += "   iand\n";
        if (op == "||")
            out += "   ior\n";
        if (op == "==")
            out += "   ieq\n";
        
        
        out += "   istore " + result + "\n";
        
        return out;

    }
};

class object_instantiation : public Tac {
public:
    object_instantiation(string _op, string _rhs)
        : Tac(_op, "", _rhs, "") {}

    string generate_code() override {
        return "   new " + rhs + "\n";
    }
};

class Print : public Tac {
public:
    Print(string _op, string _result)
        : Tac(_op, "", "", _result) {}  // Use empty strings for _lhs and _rhs

    string generate_code() override {
        string out;
        if (isdigit(result[0]))
            out += "   iconst " + result + "\n";
        else
            out += "   iload " + result + "\n";
        out += "   print\n";
        return out;
    }
};

class Jump : public Tac {
public:
    Jump(string _op, string _rhs)
        : Tac(_op, "", _rhs, "") {}

    string generate_code() override {
        return "   " + op + " " + rhs + "\n";
    }
};

class CondictionalJump : public Tac {
public:
    CondictionalJump(string _op, string _lhs, string _rhs)
        : Tac(_op, "", _rhs, "") {
            lhs = _lhs;
        }

    string generate_code() override {
        return "   iload " + lhs + "\n   " + op + " " + rhs + "\n";
    }
};


class Param : public Tac {
public:
    Param(string _op, string _rhs)
        : Tac(_op, "", _rhs, "") {}

    string generate_code() override {
        string out;
        if (isdigit(rhs[0]))
            out += "   iconst " + rhs + "\n";
        else
            out += "   iload " + rhs + "\n";

        return out;
    }
};

class MethodCall : public Tac {
public:
    MethodCall(string _op, string _rhs)
        : Tac(_op, "", _rhs, "") {}

    string generate_code() override {
        return "   invokevirtual " + rhs.substr(0,rhs.find(",")) + "\n";
    }
};

class LogicalNot : public Tac {
    private:
        map<string, string> boolien = {
            {"true", "1"},
            {"false", "0"}
        };

public:
    LogicalNot(string _op, string _rhs, string _result)
        : Tac(_op, "", _rhs, _result) {}
    
    string generate_code() override {
        return "   iconst " + boolien[rhs] + "\n   istore " + result + "\n";
    }
};

class Return : public Tac {
public:
    Return(string _op, string _rhs)
        : Tac(_op, "", _rhs, "") {}

    string generate_code() override {
        string out;
        if (isdigit(rhs[0]))
            out += "   iconst " + rhs + "\n";
        else
            out += "   iload " + rhs + "\n";
        out += "   ireturn\n";
        return out;
    }
};

class Copy : public Tac {
public:
    Copy(string _y, string _result)
        : Tac("", _y, "", _result) {}
    
    string generate_code() override {
        string out;
        if (isdigit(lhs[0]))
            out += "   iconst " + lhs + "\n";
        else
            out += "   iload " + lhs + "\n";
        out += "   istore " + result + "\n";
        return out;
    }
};

class BBlock {
public:
    string name;
    list<Tac*> instructions;
    Tac condition;
    BBlock *trueExit = nullptr;
    BBlock *falseExit = nullptr;
    BBlock() : trueExit(nullptr), falseExit(nullptr) {}
    
    ~BBlock() {
        for (auto &inst : instructions) {
            delete inst;
        }
        instructions.clear();
    }

    void dump() {
        printf("%s:\n", name.c_str());
        for (auto &i : instructions) {
            i->dump();
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
            block->instructions.back()->result = "result";
            lhs = "result";
        
        }else if ((*it)->type == "LogicalNot"){
            block->instructions.push_back(new LogicalNot("!", (*(*it)->children.begin())->value, "result"));
            lhs = "result";

        }else{
            lhs = (*it)->value;
        }

        if ((*(++it))->type.find("Expression") != string::npos){
            rhs = expression(*it, block, classSt);
        }else if ((*it)->type == "MethodCall"){
            method_call(*it, block, classSt);
            block->instructions.back()->result = "result";
            rhs = "result";

        }else{
            rhs = (*it)->value;
        }

        string result = genName();
        block->instructions.push_back(new Expression(op, lhs, rhs, result)); 

        return result;
    }
 
    void assignmentBlock(Node* node, BBlock* block, ST* classSt){
        string lhs, rhs;
        auto it = node->children.begin();

        lhs = (*it)->value;  
        it++;

        if (node->children.size()==2){
            if ((*it)->type == "Identifier" || (*it)->type == "int" || (*it)->type == "boolean")
                block->instructions.push_back(new Copy((*it)->value, lhs));

            else if ((*it)->type.find("Expression") != string::npos)
                expression(*it, block, classSt);

            // if ((*it)->type == "LogicalNot"){
            //     block->instructions.push_back(new LogicalNot("!", (*it)->children.front()->value, "result"));
            //     block->instructions.push_back(new Copy("result", lhs));
            // }
            
        }
        if ((*it)->type == "ArrayAccess"){
            string array = (*it)->children.front()->value;
            string index = (*it)->children.back()->value;
            block->instructions.push_back(new Copy(array + "[" + index + "]", lhs));
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
            block->instructions.push_back(new Copy(value, array + "[" + index + "]"));
        }
        if ((*it)->type == "Object_Instantiation"){
            string type = (*it)->children.front()->value;
            block->instructions.push_back(new Copy("new " + type, lhs));
        }
        if ((*it)->type == "    "){
            string size = (*it)->children.back()->value;
            block->instructions.push_back(new Copy("new , " + size , lhs));
        }
        if ((*it)->type.find("Expression") != string::npos){
            expression(*it, block, classSt);
        }
        if ((*it)->type == "MethodCall"){
            method_call(*it, block, classSt);
            block->instructions.back()->result = lhs;
        }     
    }
    
    MethodCall* method_call(Node* node, BBlock* block, ST* classSt){
        auto method = node->children.begin();
        Node * object = *(++method);
        method--;
        
        int n_parameters = node->children.size() - 2;
        MethodCall* right = new MethodCall("call", "");
        right->rhs = to_string(n_parameters);    
        
        auto it = node->children.begin();
        advance(it, 2);
        for (int i = 0; i < n_parameters; i++){
            if ((*it)->type == "MethodCall"){
                method_call(*it, block, classSt);
            } else if ((*it)->type == "Identifier" || (*it)->type == "int" || (*it)->type == "boolean"){
                block->instructions.push_back(new Param("param", (*it)->value));
            } 
        }

        if (object->type == "Object_Instantiation"){
            right->rhs = object->children.front()->value + "." + (*method)->value + ", " + to_string(n_parameters);
            string type = right->rhs.substr(0, right->rhs.find("."));
            block->instructions.push_back(new Tac("new", "", type, ""));
            block->instructions.push_back(right);
        }

        else if (object->type == "This"){
            string methodName = classSt->find((*method)->value, "method")->name;
            right->rhs = classSt->name + "." + methodName + ", " + to_string(n_parameters);
            block->instructions.push_back(right);
        }

        else if (object->type == "Identifier"){
            cout << object->value << endl;
            string type = classSt->find(object->value, "variable")->type;
            right->rhs = type + "." + (*method)->value + ", " + to_string(n_parameters);
            block->instructions.push_back(right);
        }

        else {    //(object->type == "MethodCall"){
            right = method_call(object, block, classSt);
            string objectName = right->rhs.substr(0, right->rhs.find("."));
            right->rhs = objectName + "." + (*method)->value + ", " + to_string(n_parameters);
            block->instructions.push_back(right);
        }

        return right;
    }

    BBlock* ifStatement(Node* node, BBlock* block1, ST* classSt){
        BBlock* expressionBlock = new BBlock();
        expressionBlock->name = genBlockName();
        block1->trueExit = expressionBlock;
        block1->instructions.push_back(new Jump("goto", expressionBlock->name));
        
        auto expression = node->children.begin();
        string op = (*expression)->value;
        auto it = (*expression)->children.begin();
        BBlock *tBlock = new BBlock();
        tBlock->name = genBlockName();
        
        BBlock *fBlock = new BBlock();
        fBlock->name = genBlockName();
        BBlock *joinBlock = new BBlock();
        joinBlock->name = genBlockName();
        string expr = this->expression(*expression, expressionBlock, classSt);
        expressionBlock->instructions.push_back(new CondictionalJump("iffalse goto", expr, fBlock->name));
        expressionBlock->trueExit = tBlock;
        expressionBlock->falseExit = fBlock;
        Node* trueNode = *(++expression);
        if (trueNode->type == "Block"){
            for (auto ifInstance = trueNode->children.begin(); ifInstance != trueNode->children.end(); ifInstance++)   //children of methods
                tBlock = runMethodBody(*ifInstance, tBlock, classSt);
        }else
            tBlock = runMethodBody(trueNode, tBlock, classSt);

        tBlock->trueExit = joinBlock;
        tBlock->instructions.push_back(new Jump("goto", joinBlock->name));
        Node* falseNode = *(++expression);
        if (falseNode->type == "Block"){
            for (auto ifInstance = falseNode->children.begin(); ifInstance != falseNode->children.end(); ifInstance++)   //children of methods
                fBlock = runMethodBody(*ifInstance, fBlock, classSt);
        }else
            fBlock = runMethodBody(falseNode, fBlock, classSt);
        fBlock->trueExit = joinBlock; 
        fBlock->instructions.push_back(new Jump("goto", joinBlock->name));
      
        return joinBlock;
    }

    BBlock* whileStm(Node* node, BBlock* block1, ST* classSt){
        BBlock* expressionBlock = new BBlock();
        expressionBlock->name = genBlockName();
        block1->trueExit = expressionBlock;
        block1->instructions.push_back(new Jump("goto", expressionBlock->name));
        auto expression = node->children.begin();
        string op = (*expression)->value;
        auto it = (*expression)->children.begin();
        BBlock *body = new BBlock();
        body->name = genBlockName();
        
        BBlock *joinBlock = new BBlock();
        joinBlock->name = genBlockName();

        string expr = this->expression(*expression, expressionBlock, classSt);
        expressionBlock->instructions.push_back(new CondictionalJump("iffalse goto", expr, joinBlock->name));
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
            block->instructions.back()->result = "result";
            block->instructions.push_back(new Print("print", "result"));
        }else if ((*print)->type.find("Expression") != string::npos){
            string result = expression(*print, block, classSt);
            block->instructions.push_back(new Print("print", result));
        }
    }

    BBlock* runMethodBody(Node* node, BBlock* block, ST* classSt){
        if (node->type == "Block"){
            for (auto blockInstance = node->children.begin(); blockInstance != node->children.end(); blockInstance++) {   //children of methods
                block = runMethodBody(*blockInstance, block, classSt);
            }
        }
        if (node->type == "Parameter"){
            string param = node->children.front()->value;
            block->instructions.push_back(new Param("param", param));
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
                block->instructions.push_back(new object_instantiation("new", type));
                block->instructions.push_back(new Return("return", "new"));
            }
            else if ((*it)->type == "MethodCall"){
                method_call(*it, block, classSt);
                block->instructions.back()->result = "result";
            }else if ((*it)->type == "Identifier" || (*it)->type == "int" || (*it)->type == "boolean")
                block->instructions.push_back(new Return("return", (*it)->value));
            else if ((*it)->type == "Print_Statement")
                block->instructions.push_back(new Print("print", (*it)->value));
        }
    
        return block;
    }

    list<BBlock *> build_cfg(Node* node, ST* St){
        int classIndex = 0;
        for (auto cls = node->children.begin(); cls != node->children.end(); cls++) {   // each element class
            auto it = St->children.begin();          // store class symboltalbe
            advance(it, classIndex);
            ST* classSt = *it;
            classIndex++;
            for (auto clsInstance = (*cls)->children.begin(); clsInstance !=(*cls)->children.end(); clsInstance++) {  // each element clsInstance or variable
                if ((*clsInstance)->type == "MethodDeclaration"){ 
                    BBlock *blockmethod = new BBlock();
                    blockmethod->name = (*cls)->value + "." + (*clsInstance)->value;
                    methodBlocks.push_back(blockmethod);
                    for (auto methodInstance = (*clsInstance)->children.begin(); methodInstance != (*clsInstance)->children.end(); methodInstance++) {   //children of methods
                        blockmethod = runMethodBody(*methodInstance, blockmethod, classSt);
                    }
                }
            }
        }
        writeDotFile();
        return methodBlocks;
    }

        
    int help_Write(BBlock* block, ofstream &out, set<string> &duplicateArrows){
        string label = block->name + " [label=\"" + block->name;
        if (duplicateArrows.insert(label).second)
            out << "    " << label << "\\n";
        else
            return -1;


        for (auto &i : block->instructions) {
            out << i->result << " := " << i->lhs << " " << i->op << " " << i->rhs << "\\n";
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
            out << "    " << block->name.replace(block->name.find("."), 1, "_") << " [label=\"" << block->name << "\\n";
            for (auto &i : block->instructions) {
                out << i->result << " := " << i->lhs << " " << i->op << " " << i->rhs << "\\n";
            }
            out << "\"];\n";
            
            if (block->trueExit){
                out << "    " << block->name << " -> " << block->trueExit->name << " [xlabel=\"true\"];\n";
                set<string> duplicateArrow;
                help_Write(block->trueExit, out, duplicateArrow);
                
            }
            
            block->name.replace(block->name.find("_"), 1, ".");
            if (block->name.find("main") != string::npos)
                block->name = "main";
            
        }

        out << "}\n";
        out.close();
    }

};