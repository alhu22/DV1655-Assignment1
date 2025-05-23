%top{
    #include "parser.tab.hh"
    #define YY_DECL yy::parser::symbol_type yylex()
    YY_DECL;
    #include "Node.h"
    int lexical_errors = 0;
}
%option yylineno noyywrap nounput batch noinput stack 
%%
"System.out.println"    { if (USE_LEX_ONLY) { printf("System.out.println "); } else { return yy::parser::make_SYSTEM_OUT_PRINTLN(yytext); } }
"while"                 { if (USE_LEX_ONLY) { printf("WHILE "); } else { return yy::parser::make_WHILE(yytext); } }
"public"                { if (USE_LEX_ONLY) { printf("PUBLIC "); } else { return yy::parser::make_PUBLIC(yytext); } }
"class"                 { if (USE_LEX_ONLY) { printf("CLASS "); } else { return yy::parser::make_CLASS(yytext); } }
"main"                  { if (USE_LEX_ONLY) { printf("MAIN "); } else { return yy::parser::make_MAIN(yytext); } }
"void"                  { if (USE_LEX_ONLY) { printf("VOID "); } else { return yy::parser::make_VOID(yytext); } }
"int"                   { if (USE_LEX_ONLY) { printf("INTIGER "); } else { return yy::parser::make_INTIGER(yytext); } }
"return"                { if (USE_LEX_ONLY) { printf("RETURN "); } else { return yy::parser::make_RETURN(yytext); } }
"boolean"               { if (USE_LEX_ONLY) { printf("BOOLEAN "); } else { return yy::parser::make_BOOLEAN(yytext); } }
"static"                { if (USE_LEX_ONLY) { printf("STATIC "); } else { return yy::parser::make_STATIC(yytext); } }
"if"                    { if (USE_LEX_ONLY) { printf("IF "); } else { return yy::parser::make_IF(yytext); } }
"else"                  { if (USE_LEX_ONLY) { printf("ELSE "); } else { return yy::parser::make_ELSE(yytext); } }
"new"                   { if (USE_LEX_ONLY) { printf("NEW "); } else { return yy::parser::make_NEW(yytext); } }
"this"                  { if (USE_LEX_ONLY) { printf("THIS "); } else { return yy::parser::make_THIS(yytext); } }
"true"                  { if (USE_LEX_ONLY) { printf("TRUE "); } else { return yy::parser::make_TRUE(yytext); } }
"false"                 { if (USE_LEX_ONLY) { printf("FALSE "); } else { return yy::parser::make_FALSE(yytext); } }
"float"                 { if (USE_LEX_ONLY) { printf("FLOAT "); } else { return yy::parser::make_FLOAT(yytext); } }
"double"                { if (USE_LEX_ONLY) { printf("DOUBLE "); } else { return yy::parser::make_DOUBLE(yytext); } }
"char"                  { if (USE_LEX_ONLY) { printf("CHAR "); } else { return yy::parser::make_CHAR(yytext); } }
"String"                { if (USE_LEX_ONLY) { printf("STRING "); } else { return yy::parser::make_STRING(yytext); } }

"length"                { if (USE_LEX_ONLY) { printf("length "); } else { return yy::parser::make_length(yytext); } }


"=="                    { if (USE_LEX_ONLY) { printf("EQ "); } else { return yy::parser::make_EQ(yytext); } }
"<"                     { if (USE_LEX_ONLY) { printf("LT "); } else { return yy::parser::make_LT(yytext); } }
">"                     { if (USE_LEX_ONLY) { printf("GT "); } else { return yy::parser::make_GT(yytext); } }
"{"                     { if (USE_LEX_ONLY) { printf("LBRACE "); } else { return yy::parser::make_LBRACE(yytext); } }
"}"                     { if (USE_LEX_ONLY) { printf("RBRACE "); } else { return yy::parser::make_RBRACE(yytext); } }
";"                     { if (USE_LEX_ONLY) { printf("SEMICOLON "); } else { return yy::parser::make_SEMICOLON(yytext); } }
"["                     { if (USE_LEX_ONLY) { printf("LBRACKET "); } else { return yy::parser::make_LBRACKET(yytext); } }
"]"                     { if (USE_LEX_ONLY) { printf("RBRACKET "); } else { return yy::parser::make_RBRACKET(yytext); } }
"="                     { if (USE_LEX_ONLY) { printf("ASSIGN "); } else { return yy::parser::make_ASSIGN(yytext); } }
"."                     { if (USE_LEX_ONLY) { printf("DOT "); } else { return yy::parser::make_DOT(yytext); } }
","                     { if (USE_LEX_ONLY) { printf("COMMA "); } else { return yy::parser::make_COMMA(yytext); } }
"!"                     { if (USE_LEX_ONLY) { printf("NOT "); } else { return yy::parser::make_NOT(yytext); } }
"&&"                    { if (USE_LEX_ONLY) { printf("AND "); } else { return yy::parser::make_AND(yytext); } }
"||"                    { if (USE_LEX_ONLY) { printf("OR "); } else { return yy::parser::make_OR(yytext); } }

"+"                     {if(USE_LEX_ONLY) {printf("PLUSOP ");} else {return yy::parser::make_PLUSOP(yytext);}}
"-"                     {if(USE_LEX_ONLY) {printf("SUBOP ");} else {return yy::parser::make_MINUSOP(yytext);}}
"*"                     {if(USE_LEX_ONLY) {printf("MULTOP ");} else {return yy::parser::make_MULTOP(yytext);}}
"("                     {if(USE_LEX_ONLY) {printf("LP ");} else {return yy::parser::make_LP(yytext);}}
")"                     {if(USE_LEX_ONLY) {printf("RP ");} else {return yy::parser::make_RP(yytext);}}

[a-zA-Z_][a-zA-Z0-9_]*    {if(USE_LEX_ONLY) {printf("IDENTIFIER ");} else {return yy::parser::make_IDENTIFIER(yytext);}}
0|[1-9][0-9]*            {if(USE_LEX_ONLY) {printf("INT ");} else {return yy::parser::make_INT(yytext);}}


[ \t\n\r]+              {}
"//"[^\n]*              {}
.                       { if(!lexical_errors) fprintf(stderr, "Lexical errors found! See the logs below: \n"); fprintf(stderr,"\t@error at line %d. Character %s is not recognized\n", yylineno, yytext); lexical_errors = 1;}
<<EOF>> { return yy::parser::make_END(); }
%%

