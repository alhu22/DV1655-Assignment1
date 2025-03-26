#ifndef GENERATE_H
#define GENERATE_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

/*
id    Instruction           Description
0     iload n               Push integer value stored in local variable n.
1     iconst v              Push integer value v.
2     istore n              Pop value v and store it in local variable n.
3     iadd                  Pop value v1 and v2. Push v2 + v1.
4     isub                  Pop value v1 and v2. Push v2 - v1.
5     imul                  Pop value v1 and v2. Push v2 * v1.
6     idiv                  Pop value v1 and v2. Push v2 / v1.
7     ilt                   Pop value v1 and v2. Push 1 if v2 < v1, else push 0.
8     iand                  Pop value v1 and v2. Push 0 if v2 * v1 == 0, else push 1.
9     ior                   Pop value v1 and v2. Push 0 if v2 + v1 == 0, else push 1.
10    inot                  Pop value v. Push 1 if v == 0, else push 0.
11    goto i                Jump to instruction labeled i unconditionally.
12    iffalse goto i         Pop value v from the data stack. If v == 0 jump to instruction labeled i, else continue with the following instruction.
13    invokevirtual m        Push current activation to the activation stack and switch to the method with qualified name m.
14    ireturn               Pop the activation from the activation stack and continue.
15    print                 Pop the value from the data stack and print it.
16    stop

*/


class GENERATE {

public:
    GENERATE() {}


    int help(BBlock *block, ofstream &out, map<string, int> &visited) {
        if (visited[block->name] == 1) {
            return 0;
        }else
            visited[block->name] = 1;

        out << block->name + ":\n";
        for (auto &i : block->instructions) {
            out <<  i->generate_code();
        }
        if (block->name == "main")
            out << "   stop\n";

        if (block->trueExit) {
            help(block->trueExit, out, visited);  
        }

        if (block->falseExit) {
            help(block->falseExit, out, visited);
        }

    }

    void loopBlocks(list<BBlock *> methodBlocks){
        string fileName = "out.bc";
        ofstream out(fileName);
        // string out;
        map<string, int> visited;
        for (auto &block : methodBlocks) {
            help(block, out, visited);
        }

        
        out.close();
        cout << "bytecode written to " << fileName << endl;
        // for (auto &block : methodBlocks) {
        //     cout << block << endl;
        //     delete block;
        // }
    }

};

#endif