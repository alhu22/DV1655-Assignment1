/* Skeleton and definitions for generating a LALR(1) parser in C++ */
%skeleton "lalr1.cc" 
%defines
%define parse.error verbose
%define api.value.type variant
%define api.token.constructor
%token <std::string> SYSTEM_OUT_PRINTLN WHILE PUBLIC CLASS VOID RETURN STATIC IF ELSE NEW THIS TRUE FALSE
%token <std::string> IDENTIFIER EQ LT GT LBRACE RBRACE SEMICOLON LBRACKET RBRACKET ASSIGN DOT COMMA NOT AND OR
%token <std::string> BOOLEAN MAIN STRING


/* Required code included before the parser definition begins */
%code requires{
  #include <string>
  #include "Node.h"
  #define USE_LEX_ONLY false //change this macro to true if you want to isolate the lexer from the parser.
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
%left PLUSOP MINUSOP
%left MULTOP
%right ELSE


/* Specify types for non-terminals in the grammar */
%type <Node *> root statement expression factor MethodDeclaration
%type <std::vector<Node*>> variables statement_list parameters
%type <std::string> type



/* Grammar rules section */
%%

root: statement { root = $1; };

type: INT LBRACKET RBRACKET { $$ = "int[]"; }
    | BOOLEAN               { $$ = "boolean"; }
    | INT                   { $$ = "int"; }
    | IDENTIFIER            { $$ = $1; }  // Custom class type
    ;


/* Define statements */
statement: expression SEMICOLON { 
               $$ = new Node("ExpressionStatement", "", yylineno);
               $$->children.push_back($1);
           }
           | LBRACE statement_list RBRACE { 
               $$ = new Node("BlockStatement", "", yylineno);
               for (Node* stmt : $2) { 
                   $$->children.push_back(stmt); 
               }
           }
           | SYSTEM_OUT_PRINTLN LP expression RP SEMICOLON { 
                $$ = new Node("PrintStatement", "", yylineno);
                $$->children.push_back($3);
            }
           
           | IDENTIFIER ASSIGN expression SEMICOLON { 
                $$ = new Node("Assignment", $1, yylineno);
                $$->children.push_back($3);  // Assigned expression
            }
            | IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression SEMICOLON { 
                $$ = new Node("ArrayAssignment", $1, yylineno);
                $$->children.push_back($3);  // Array index
                $$->children.push_back($6);  // Assigned value
            }
            | IF LP expression RP statement %prec IF { 
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
            
        ;

MethodDeclaration:
    PUBLIC type IDENTIFIER LP parameters RP LBRACE statement_list RETURN expression SEMICOLON RBRACE {
        $$ = new Node("MethodDeclaration", $3, yylineno);  // $3 is the method name
        $$->children.push_back(new Node("Type", $2, yylineno));  // $2 is the type
        $$->children.push_back($6);  // $6 is parameters (which is a vector of Node*)
        $$->children.push_back($7);  // $7 is statement_list
        $$->children.push_back($9);  // $9 is expression
    }


parameters:
    /* empty */ { $$ = std::vector<Node*>(); }
    | type IDENTIFIER { $$ = std::vector<Node*>(); $$.push_back($1); $$.push_back($2); }
    | type IDENTIFIER COMMA parameters { $$ = $3; $$.insert($$.begin(), $1); $$.insert($$.begin() + 1, $2); }
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
            | expression DOT IDENTIFIER LP variables RP {
                $$ = new Node("MethodCall", $3, yylineno);
                $$->children.push_back($1); // Object calling the method

                // Add all arguments from $5 (variables) to the children of MethodCall
                for (Node* arg : $5) {
                    $$->children.push_back(arg);
                }
            }

            | NEW INT LBRACKET expression RBRACKET {
                $$ = new Node("NewIntArray", "", yylineno);
                $$->children.push_back($4);
            }
            

            | factor { $$ = $1; }
            ;
statement_list:
      statement { 
          $$ = std::vector<Node*>(); 
          $$.push_back($1); 
      }
    | statement statement_list { 
          $$ = $2; 
          $$.insert($$.begin(), $1); // Add statement before the rest
      }
;
variables:
      /* empty */ { 
          $$ = std::vector<Node*>(); // No arguments
      }
    | expression { 
          $$ = std::vector<Node*>(); 
          $$.push_back($1); 
      }
    | expression COMMA variables { 
          $$ = $3; 
          $$.insert($$.begin(), $1); // Insert first argument before the rest
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
