/* Skeleton and definitions for generating a LALR(1) parser in C++ */
%skeleton "lalr1.cc" 
%defines
%define parse.error verbose
%define api.value.type variant
%define api.token.constructor
%token <std::string> SYSTEM_OUT_PRINTLN WHILE PUBLIC CLASS VOID RETURN STATIC IF ELSE NEW THIS TRUE FALSE FLOAT DOUBLE CHAR PRIVATE
%token <std::string> IDENTIFIER EQ LT GT LBRACE RBRACE SEMICOLON LBRACKET RBRACKET ASSIGN DOT COMMA NOT AND OR 
%token <std::string> BOOLEAN MAIN STRING INTIGER

%type <int> lineno


/* Required code included before the parser definition begins */
%code requires{
  #include <string>
  #include "Node.h"
  #define USE_LEX_ONLY false //change this macro to false if you want to isolate the lexer from the parser.
}

/* Code included in the parser implementation file */
%code{
  #define YY_DECL yy::parser::symbol_type yylex()
  YY_DECL;
  Node* root;
  extern int yylineno;
}


/* Token definitions for the grammar */
%token <std::string> PLUSOP MINUSOP MULTOP INT LP RP
%token END 0 "end of file"

%token <std::string> length

/* Operator precedence and associativity rules */
%right ASSIGN
%left OR AND
%left EQ LT GT
%left PLUSOP MINUSOP
%left MULTOP
%left RP LP
%right NOT
%left LBRACKET RBRACKET
%left DOT
%right ELSE


/* Specify types for non-terminals in the grammar */
%type <Node *> root statement expression factor MethodDeclaration ClassDeclaration VarDeclaration parameter Goal MainClass
%type <std::list<Node*>> variables statement_list parameter_list MethodDeclaration_list  ClassDeclaration_list expression_list parameter_sequence expression_sequence Methodbody
%type <std::string> Type 



/* Grammar rules section */
%%

root: Goal { root = $1; };


Goal:
    MainClass ClassDeclaration_list {
        // Root node for the entire program
        $$ = new Node("Goal", "", yylineno);
        $$->children.push_back($1);
        // Append all class declarations
        for (Node* classNode : $2) {
            $$->children.push_back(classNode);
        }
    }
;
ClassDeclaration_list:
    /* Empty */ { $$ = std::list<Node*>(); }
    | ClassDeclaration ClassDeclaration_list {
        $$ = $2;
        $$.insert($$.begin(), $1);
    }



Type: INTIGER LBRACKET RBRACKET { $$ = "int[]"; }
    | BOOLEAN               { $$ = "boolean"; }
    | INTIGER               { $$ = "int"; }
    | IDENTIFIER            { $$ = $1; }  // Custom class type
;

lineno:
    /* Empty */ { $$ = yylineno; }
;


/* Define statements */
statement:  LBRACE statement_list RBRACE {
                $$ = new Node("Block", "", yylineno);
                $$->children = $2; // Store the list of statements inside the block
            }
            | IF LP expression RP statement { 
                $$ = new Node("IfStatement", "", yylineno);
                $$->children.push_back($3);  // Condition
                $$->children.push_back($5);  // If-block
                $$->children.push_back(new Node("EmptyElse", "", yylineno)); // No Else
            }
            | IF LP expression RP statement ELSE statement {
                $$ = new Node("IfStatement", "", yylineno);
                $$->children.push_back($3);  // Condition
                $$->children.push_back($5);  // If-block
                $$->children.push_back($7);  // Else-block (Exists now)
            }
            | WHILE LP expression RP statement { 
                $$ = new Node("WhileStatement", "", yylineno);
                $$->children.push_back($3);  // Condition
                $$->children.push_back($5);  // Loop body
            }
            |SYSTEM_OUT_PRINTLN LP expression RP SEMICOLON {
                $$ = new Node("Print_Statement", "", yylineno);
                $$->children.push_back($3); // Attach the expression being printed
            }
            | IDENTIFIER ASSIGN expression SEMICOLON { 
                $$ = new Node("Assignment", "", yylineno);
                $$->children.push_back(new Node("Identifier", $1, yylineno));  // Assigned expression
                $$->children.push_back($3);  // Assigned expression
            }
            | IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression SEMICOLON { 
                $$ = new Node("ArrayAssignment", "", yylineno);
                $$->children.push_back(new Node("Identifier", $1, yylineno)); 
                $$->children.push_back($3);  // Array index
                $$->children.push_back($6);  // Assigned value
            }
        ;
        
MainClass:
    PUBLIC CLASS IDENTIFIER lineno LBRACE PUBLIC STATIC VOID MAIN LP STRING LBRACKET RBRACKET IDENTIFIER RP LBRACE statement_list RBRACE RBRACE {
        // Creating a new Node for MainClass
        $$ = new Node("ClassDeclaration", $3, $4); // $3 is the class name (IDENTIFIER)

        // Create a new Node for the main method
        Node* mainMethodNode = new Node("MethodDeclaration", "main", yylineno);
        
        // Adding the method's signature (public static void main(String[] args))
        Node* mainMethodType = new Node("Type", "void", yylineno);
        mainMethodNode->children.push_back(mainMethodType);
        
        Node* paramNode = new Node("Parameter", "", yylineno);
        paramNode->children.push_back(new Node("Type", "String[]", yylineno));
        paramNode->children.push_back(new Node("Identifier", $14, yylineno)); // Parameter identifier "args"
        mainMethodNode->children.push_back(paramNode);
                
        for (Node* stmt : $17) {
            mainMethodNode->children.push_back(stmt);
        }

        // Adding the method to the class node
        $$->children.push_back(mainMethodNode);
    }
;

ClassDeclaration:
    CLASS IDENTIFIER lineno LBRACE variables MethodDeclaration_list RBRACE{
        $$ = new Node("ClassDeclaration", $2, $3);
        for (Node* var : $5) $$->children.push_back(var);

        for (Node* method : $6) $$->children.push_back(method);
    }
;


MethodDeclaration:
    PUBLIC Type IDENTIFIER lineno LP parameter_sequence RP LBRACE Methodbody RETURN expression SEMICOLON RBRACE {
        $$ = new Node("MethodDeclaration", $3, $4);
        $$->children.push_back(new Node("Type", $2, yylineno));

        for (Node* param : $6) $$->children.push_back(param);

        for (Node* stmt : $9) $$->children.push_back(stmt);
    }   
;

Methodbody:
    /* Empty */ { $$ = std::list<Node*>(); } // Empty body
    | Methodbody VarDeclaration { 
        $$ = $1; 
        $$.push_back($2);
    }
    | Methodbody statement {
        $$ = $1; 
        $$.push_back($2);
    }
;

parameter:
    Type IDENTIFIER {
        $$ = new Node("Parameter", "", yylineno);
        $$->children.push_back(new Node("Type", $1, yylineno));
        $$->children.push_back(new Node("Identifier", $2, yylineno));
    } 
;

parameter_list:
    parameter { 
        $$ = std::list<Node*>(); 
        $$.push_back($1);
    }
    | parameter_list COMMA parameter { 
        $$ = $1; 
        $$.push_back($3);
    }
;

parameter_sequence:
    parameter_list { $$ = $1; } 
    | /* Empty */ { $$ = std::list<Node*>(); }
;



/* Expressions */
expression: expression PLUSOP expression { 
                            $$ = new Node("AddExpression", "", yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                          }
            | expression MINUSOP expression {
                            $$ = new Node("SubExpression", "", yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                          }
            | expression MULTOP expression {
                            $$ = new Node("MultExpression", "", yylineno);
                            $$->children.push_back($1);
                            $$->children.push_back($3);
                          }
            | expression AND expression { 
                $$ = new Node("LogicalExpression", "", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($3);
            }
            | expression OR expression { 
                $$ = new Node("LogicalExpression", "", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($3);
            }
            | expression EQ expression { 
                $$ = new Node("LogicalExpression", "", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($3);
            }
            | expression LT expression { 
                $$ = new Node("RelationalExpression", "", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($3);
            }
            | expression GT expression { 
                $$ = new Node("RelationalExpression", "", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($3);
            }
            | expression LBRACKET expression RBRACKET {
                $$ = new Node("ArrayAccess", "", yylineno);
                $$->children.push_back($1);
                $$->children.push_back($3);
            }
            | expression DOT length {
                $$ = new Node("ArrayLength", "", yylineno);
                $$->children.push_back($1);
            }
            | expression DOT IDENTIFIER LP expression_sequence RP { 
                $$ = new Node("MethodCall", "", yylineno);
                $$->children.push_back(new Node("Identifier", $3, yylineno));
                $$->children.push_back($1);

                for (Node* arg : $5) {  // Iterate over list
                    $$->children.push_back(arg);
                }
            }            
            |NEW INTIGER LBRACKET expression RBRACKET {
                $$ = new Node("Array_Instantiation", "", yylineno);
                $$->children.push_back(new Node("Type", "int", yylineno));
                $$->children.push_back($4); // Array size expression
            }
            |NEW IDENTIFIER LP RP {
                $$ = new Node("Object_Instantiation", "", yylineno);
                $$->children.push_back(new Node("Identifier", $2, yylineno)); // Store class name
            }
           
            | factor { $$ = $1; }
            ;

expression_list:
    expression { 
        $$ = std::list<Node*>(); 
        $$.push_back($1);
    }
    | expression_list COMMA expression { 
        $$ = $1; 
        $$.push_back($3);
    }
;

expression_sequence:
    expression_list { $$ = $1; } 
    | /* Empty */ { $$ = std::list<Node*>(); }
;



MethodDeclaration_list:
    /* Empty */ { 
        $$ = std::list<Node*>(); // Create an empty list for no methods
      }
    | MethodDeclaration MethodDeclaration_list { 
          $$ = $2; 
          $$.insert($$.begin(), $1); // Insert the new method before the rest
    }
;


statement_list:
   statement { 
          $$ = std::list<Node*>(); 
          $$.push_back($1); 
    }
    | statement statement_list { 
          $$ = $2; 
          $$.insert($$.begin(), $1); // Add statement before the rest
    }
;

VarDeclaration:
    Type IDENTIFIER SEMICOLON {
        $$ = new Node("VarDeclaration", "", yylineno);
        $$->children.push_back(new Node("Type", $1, yylineno));
        $$->children.push_back(new Node("Identifier", $2, yylineno));
    }
;


variables:
      /* Empty */ { 
          $$ = std::list<Node*>(); // Create an empty list for no variables
      }
    | VarDeclaration variables { 
          $$ = $2; 
          $$.insert($$.begin(), $1); // Insert the new variable before the rest
      }
;

factor:     INT           { $$ = new Node("Int", $1, yylineno); }
            | LP expression RP { $$ = $2; }
            | IDENTIFIER { $$ = new Node("Identifier", $1, yylineno); }
            | MINUSOP factor { 
                $$ = new Node("Negate", "", yylineno); 
                $$->children.push_back($2); 
            }
            | NOT factor {
                $$ = new Node("LogicalNot", "", yylineno);
                $$->children.push_back($2);
            }
            | TRUE { $$ = new Node("Boolean", "true", yylineno); }
            | FALSE { $$ = new Node("Boolean", "false", yylineno); }
            | THIS { $$ = new Node("This", "this", yylineno); }
            ;