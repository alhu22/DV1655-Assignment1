#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <variant>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// ---------- Instruction ----------
struct Instruction
{
    string id;
    variant<int, string> argument;

    Instruction(const string &id, variant<int, string> arg = 0)
        : id(id), argument(arg) {}
};

// ---------- Activation ----------
struct Activation
{
    int pc;
    map<string, int> local_variable_values;
    Instruction *instructions;

    Activation(int pc, Instruction *instructions)
        : pc(pc), instructions(instructions) {}

    Instruction getNextInstruction()
    {
        return instructions[pc++];
    }

    void storeValue(const string &var, int value)
    {
        local_variable_values[var] = value;
    }

    int getValue(const string &var) const
    {
        auto it = local_variable_values.find(var);
        return it != local_variable_values.end() ? it->second : 0;
    }
};

// ---------- Interpreter ----------
class Interpreter
{
private:
    stack<int> data_stack;
    vector<Instruction> instructions;

public:
    // Construct interpreter directly from a single method's instructions
    Interpreter(const vector<Instruction> &instructions)
    {
        this->instructions = instructions;
    }

    void execute()
    {
        Activation current_activation(0, instructions.data()); // Use data() to get raw pointer
        Instruction instruction("stop");

        while (true)
        {
            instruction = current_activation.getNextInstruction();

            if (instruction.id == "iconst")
            {
                int val = get<int>(instruction.argument);
                data_stack.push(val);
            }
            else if (instruction.id == "istore")  // store top of stack into variable
            {
                if (data_stack.empty())
                {
                    cerr << "ERROR: Stack empty on ISTORE" << endl;
                    return;
                }
                string var = get<string>(instruction.argument);
                int val = data_stack.top();
                data_stack.pop();
                current_activation.storeValue(var, val);
            }
            else if (instruction.id == "iadd")
            {
                if (data_stack.size() < 2)
                {
                    cerr << "ERROR: Not enough values on stack for IADD" << endl;
                    return;
                }
                int a = data_stack.top();
                data_stack.pop();
                int b = data_stack.top();
                data_stack.pop();
                data_stack.push(b + a);
            }
            else if (instruction.id == "stop")
            {
                return;
            }
            else if (instruction.id == "iload")
            {
                string var = get<string>(instruction.argument);
                int val = current_activation.getValue(var);
                data_stack.push(val);
            }
            else if (instruction.id == "imul")
            {
                if (data_stack.size() < 2)
                {
                    cerr << "Not enough values for IMUL\n";
                    return;
                }
                int a = data_stack.top();
                data_stack.pop();
                int b = data_stack.top();
                data_stack.pop();
                data_stack.push(b * a);
            }
            else if (instruction.id == "isub")
            {
                if (data_stack.size() < 2)
                {
                    cerr << "Not enough values for ISUB\n";
                    return;
                }
                int a = data_stack.top();
                data_stack.pop();
                int b = data_stack.top();
                data_stack.pop();
                data_stack.push(b - a);
            }
            else if (instruction.id == "iand")
            {
                int a = data_stack.top();
                data_stack.pop();
                int b = data_stack.top();
                data_stack.pop();
                data_stack.push(b & a);
            }
            else if (instruction.id == "ior")
            {
                int a = data_stack.top();
                data_stack.pop();
                int b = data_stack.top();
                data_stack.pop();
                data_stack.push(b | a);
            }
            else if (instruction.id == "ieq")
            {
                int a = data_stack.top();
                data_stack.pop();
                int b = data_stack.top();
                data_stack.pop();
                data_stack.push(b == a ? 1 : 0);
            }
            else if (instruction.id == "igt")
            {
                int a = data_stack.top();
                data_stack.pop();
                int b = data_stack.top();
                data_stack.pop();
                data_stack.push(b > a ? 1 : 0);
            }
            else if (instruction.id == "ilt")
            {
                int a = data_stack.top();
                data_stack.pop();
                int b = data_stack.top();
                data_stack.pop();
                data_stack.push(b < a ? 1 : 0);
            }
            else if (instruction.id == "print")
            {
                if (data_stack.empty())
                {
                    cerr << "Stack empty on PRINT\n";
                }
                else
                {
                    cout << " " << data_stack.top() << endl;
                }
            }
            else
            {
                cerr << "Unknown instruction: " << instruction.id << endl;
                return;
            }
        }
    }
};

// ---------- Helper Functions ----------
vector<Instruction> loadInstructionsFromFile(const string &filename)
{
    ifstream infile(filename);
    vector<Instruction> instructions;
    string line;

    while (getline(infile, line))
    {
        if (line.find(':') != string::npos) // skip method name
            continue;

        istringstream iss(line);
        string opcode;
        iss >> opcode;

        string arg;
        if (iss >> arg)
        {
            if (isdigit(arg[0]) || (arg[0] == '-' && isdigit(arg[1])))
            { // string to int
                instructions.emplace_back(opcode, stoi(arg));
            }
            else
            {
                instructions.emplace_back(opcode, arg);
            }
        }
        else
        {
            instructions.emplace_back(opcode);
        }
    }

    return instructions;
}

// ---------- Main ----------
int main()
{
    string filename = "out.bc";
    vector<Instruction> instructions = loadInstructionsFromFile(filename);
    
    Interpreter interp(instructions);
    interp.execute();

    return 0;
}
