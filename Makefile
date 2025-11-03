compiler: lex.yy.c parser.tab.o main.cc
		g++ -g -w -ocompiler parser.tab.o lex.yy.c main.cc -std=c++14
parser.tab.o: parser.tab.cc
		g++ -g -w -c parser.tab.cc -std=c++14
parser.tab.cc: parser.yy
		bison parser.yy
lex.yy.c: lexer.flex parser.tab.cc
		flex lexer.flex
tree: 
		 dot -Tpdf tree.dot -otree.pdf
st: 
		 dot -Tpdf symbol_tree.dot -osymbolTable.pdf
cfg: 
		 dot -Tpdf cfg.dot -ocfg.pdf

interprete: interpreter.cpp
		g++ -std=c++17 -o interpreter interpreter.cpp
		./interpreter

clean:
		rm -f parser.tab.* lex.yy.c* compiler stack.hh position.hh location.hh tree.dot tree.pdf symbolTable.pdf symbol_tree.dot out.bc interpreter cfg.dot cfg.pdf
		rm -R compiler.dSYM