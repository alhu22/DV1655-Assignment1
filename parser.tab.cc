// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.tab.hh"


// Unqualified %code blocks.
#line 22 "parser.yy"

  #define YY_DECL yy::parser::symbol_type yylex()
  YY_DECL;
  Node* root;
  extern int yylineno;

#line 53 "parser.tab.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 126 "parser.tab.cc"

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_Goal: // Goal
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_MainClass: // MainClass
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_parameter: // parameter
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_factor: // factor
        value.YY_MOVE_OR_COPY< Node * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lineno: // lineno
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ClassDeclaration_list: // ClassDeclaration_list
      case symbol_kind::S_Methodbody: // Methodbody
      case symbol_kind::S_parameter_list: // parameter_list
      case symbol_kind::S_parameter_sequence: // parameter_sequence
      case symbol_kind::S_expression_list: // expression_list
      case symbol_kind::S_expression_sequence: // expression_sequence
      case symbol_kind::S_MethodDeclaration_list: // MethodDeclaration_list
      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_variables: // variables
        value.YY_MOVE_OR_COPY< std::list<Node*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SYSTEM_OUT_PRINTLN: // SYSTEM_OUT_PRINTLN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_DOUBLE: // DOUBLE
      case symbol_kind::S_CHAR: // CHAR
      case symbol_kind::S_PRIVATE: // PRIVATE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_INTIGER: // INTIGER
      case symbol_kind::S_PLUSOP: // PLUSOP
      case symbol_kind::S_MINUSOP: // MINUSOP
      case symbol_kind::S_MULTOP: // MULTOP
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_length: // length
      case symbol_kind::S_Type: // Type
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_Goal: // Goal
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_MainClass: // MainClass
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_parameter: // parameter
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_factor: // factor
        value.move< Node * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lineno: // lineno
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ClassDeclaration_list: // ClassDeclaration_list
      case symbol_kind::S_Methodbody: // Methodbody
      case symbol_kind::S_parameter_list: // parameter_list
      case symbol_kind::S_parameter_sequence: // parameter_sequence
      case symbol_kind::S_expression_list: // expression_list
      case symbol_kind::S_expression_sequence: // expression_sequence
      case symbol_kind::S_MethodDeclaration_list: // MethodDeclaration_list
      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_variables: // variables
        value.move< std::list<Node*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SYSTEM_OUT_PRINTLN: // SYSTEM_OUT_PRINTLN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_DOUBLE: // DOUBLE
      case symbol_kind::S_CHAR: // CHAR
      case symbol_kind::S_PRIVATE: // PRIVATE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_INTIGER: // INTIGER
      case symbol_kind::S_PLUSOP: // PLUSOP
      case symbol_kind::S_MINUSOP: // MINUSOP
      case symbol_kind::S_MULTOP: // MULTOP
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_length: // length
      case symbol_kind::S_Type: // Type
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_Goal: // Goal
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_MainClass: // MainClass
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_parameter: // parameter
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_factor: // factor
        value.copy< Node * > (that.value);
        break;

      case symbol_kind::S_lineno: // lineno
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_ClassDeclaration_list: // ClassDeclaration_list
      case symbol_kind::S_Methodbody: // Methodbody
      case symbol_kind::S_parameter_list: // parameter_list
      case symbol_kind::S_parameter_sequence: // parameter_sequence
      case symbol_kind::S_expression_list: // expression_list
      case symbol_kind::S_expression_sequence: // expression_sequence
      case symbol_kind::S_MethodDeclaration_list: // MethodDeclaration_list
      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_variables: // variables
        value.copy< std::list<Node*> > (that.value);
        break;

      case symbol_kind::S_SYSTEM_OUT_PRINTLN: // SYSTEM_OUT_PRINTLN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_DOUBLE: // DOUBLE
      case symbol_kind::S_CHAR: // CHAR
      case symbol_kind::S_PRIVATE: // PRIVATE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_INTIGER: // INTIGER
      case symbol_kind::S_PLUSOP: // PLUSOP
      case symbol_kind::S_MINUSOP: // MINUSOP
      case symbol_kind::S_MULTOP: // MULTOP
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_length: // length
      case symbol_kind::S_Type: // Type
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_Goal: // Goal
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_MainClass: // MainClass
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_parameter: // parameter
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_factor: // factor
        value.move< Node * > (that.value);
        break;

      case symbol_kind::S_lineno: // lineno
        value.move< int > (that.value);
        break;

      case symbol_kind::S_ClassDeclaration_list: // ClassDeclaration_list
      case symbol_kind::S_Methodbody: // Methodbody
      case symbol_kind::S_parameter_list: // parameter_list
      case symbol_kind::S_parameter_sequence: // parameter_sequence
      case symbol_kind::S_expression_list: // expression_list
      case symbol_kind::S_expression_sequence: // expression_sequence
      case symbol_kind::S_MethodDeclaration_list: // MethodDeclaration_list
      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_variables: // variables
        value.move< std::list<Node*> > (that.value);
        break;

      case symbol_kind::S_SYSTEM_OUT_PRINTLN: // SYSTEM_OUT_PRINTLN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_DOUBLE: // DOUBLE
      case symbol_kind::S_CHAR: // CHAR
      case symbol_kind::S_PRIVATE: // PRIVATE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_INTIGER: // INTIGER
      case symbol_kind::S_PLUSOP: // PLUSOP
      case symbol_kind::S_MINUSOP: // MINUSOP
      case symbol_kind::S_MULTOP: // MULTOP
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_length: // length
      case symbol_kind::S_Type: // Type
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_Goal: // Goal
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_MainClass: // MainClass
      case symbol_kind::S_ClassDeclaration: // ClassDeclaration
      case symbol_kind::S_MethodDeclaration: // MethodDeclaration
      case symbol_kind::S_parameter: // parameter
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_VarDeclaration: // VarDeclaration
      case symbol_kind::S_factor: // factor
        yylhs.value.emplace< Node * > ();
        break;

      case symbol_kind::S_lineno: // lineno
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_ClassDeclaration_list: // ClassDeclaration_list
      case symbol_kind::S_Methodbody: // Methodbody
      case symbol_kind::S_parameter_list: // parameter_list
      case symbol_kind::S_parameter_sequence: // parameter_sequence
      case symbol_kind::S_expression_list: // expression_list
      case symbol_kind::S_expression_sequence: // expression_sequence
      case symbol_kind::S_MethodDeclaration_list: // MethodDeclaration_list
      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_variables: // variables
        yylhs.value.emplace< std::list<Node*> > ();
        break;

      case symbol_kind::S_SYSTEM_OUT_PRINTLN: // SYSTEM_OUT_PRINTLN
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_PUBLIC: // PUBLIC
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_STATIC: // STATIC
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_NEW: // NEW
      case symbol_kind::S_THIS: // THIS
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_DOUBLE: // DOUBLE
      case symbol_kind::S_CHAR: // CHAR
      case symbol_kind::S_PRIVATE: // PRIVATE
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_EQ: // EQ
      case symbol_kind::S_LT: // LT
      case symbol_kind::S_GT: // GT
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_BOOLEAN: // BOOLEAN
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_INTIGER: // INTIGER
      case symbol_kind::S_PLUSOP: // PLUSOP
      case symbol_kind::S_MINUSOP: // MINUSOP
      case symbol_kind::S_MULTOP: // MULTOP
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_length: // length
      case symbol_kind::S_Type: // Type
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // root: Goal
#line 59 "parser.yy"
           { root = yystack_[0].value.as < Node * > (); }
#line 887 "parser.tab.cc"
    break;

  case 3: // Goal: MainClass ClassDeclaration_list
#line 63 "parser.yy"
                                    {
        // Root node for the entire program
        yylhs.value.as < Node * > () = new Node("Goal", "", yylineno);
        yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
        // Append all class declarations
        for (Node* classNode : yystack_[0].value.as < std::list<Node*> > ()) {
            yylhs.value.as < Node * > ()->children.push_back(classNode);
        }
    }
#line 901 "parser.tab.cc"
    break;

  case 4: // ClassDeclaration_list: %empty
#line 74 "parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 907 "parser.tab.cc"
    break;

  case 5: // ClassDeclaration_list: ClassDeclaration ClassDeclaration_list
#line 75 "parser.yy"
                                             {
        yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > ();
        yylhs.value.as < std::list<Node*> > ().insert(yylhs.value.as < std::list<Node*> > ().begin(), yystack_[1].value.as < Node * > ());
    }
#line 916 "parser.tab.cc"
    break;

  case 6: // Type: INTIGER LBRACKET RBRACKET
#line 82 "parser.yy"
                                { yylhs.value.as < std::string > () = "int[]"; }
#line 922 "parser.tab.cc"
    break;

  case 7: // Type: BOOLEAN
#line 83 "parser.yy"
                            { yylhs.value.as < std::string > () = "boolean"; }
#line 928 "parser.tab.cc"
    break;

  case 8: // Type: INTIGER
#line 84 "parser.yy"
                            { yylhs.value.as < std::string > () = "int"; }
#line 934 "parser.tab.cc"
    break;

  case 9: // Type: IDENTIFIER
#line 85 "parser.yy"
                            { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 940 "parser.tab.cc"
    break;

  case 10: // lineno: %empty
#line 89 "parser.yy"
                { yylhs.value.as < int > () = yylineno; }
#line 946 "parser.tab.cc"
    break;

  case 11: // statement: LBRACE statement_list RBRACE
#line 94 "parser.yy"
                                         {
                yylhs.value.as < Node * > () = new Node("Block", "", yylineno);
                yylhs.value.as < Node * > ()->children = yystack_[1].value.as < std::list<Node*> > (); // Store the list of statements inside the block
            }
#line 955 "parser.tab.cc"
    break;

  case 12: // statement: IF LP expression RP statement
#line 98 "parser.yy"
                                            { 
                yylhs.value.as < Node * > () = new Node("IfStatement", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());  // Condition
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());  // If-block
                yylhs.value.as < Node * > ()->children.push_back(new Node("EmptyElse", "", yylineno)); // No Else
            }
#line 966 "parser.tab.cc"
    break;

  case 13: // statement: IF LP expression RP statement ELSE statement
#line 104 "parser.yy"
                                                           {
                yylhs.value.as < Node * > () = new Node("IfStatement", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ());  // Condition
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());  // If-block
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());  // Else-block (Exists now)
            }
#line 977 "parser.tab.cc"
    break;

  case 14: // statement: WHILE LP expression RP statement
#line 110 "parser.yy"
                                               { 
                yylhs.value.as < Node * > () = new Node("WhileStatement", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());  // Condition
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());  // Loop body
            }
#line 987 "parser.tab.cc"
    break;

  case 15: // statement: SYSTEM_OUT_PRINTLN LP expression RP SEMICOLON
#line 115 "parser.yy"
                                                           {
                yylhs.value.as < Node * > () = new Node("Print_Statement", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); // Attach the expression being printed
            }
#line 996 "parser.tab.cc"
    break;

  case 16: // statement: IDENTIFIER ASSIGN expression SEMICOLON
#line 119 "parser.yy"
                                                     { 
                yylhs.value.as < Node * > () = new Node("Assignment", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(new Node("Identifier", yystack_[3].value.as < std::string > (), yylineno));  // Assigned expression
                yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());  // Assigned expression
            }
#line 1006 "parser.tab.cc"
    break;

  case 17: // statement: IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression SEMICOLON
#line 124 "parser.yy"
                                                                                  { 
                yylhs.value.as < Node * > () = new Node("ArrayAssignment", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(new Node("Identifier", yystack_[6].value.as < std::string > (), yylineno)); 
                yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ());  // Array index
                yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());  // Assigned value
            }
#line 1017 "parser.tab.cc"
    break;

  case 18: // MainClass: PUBLIC CLASS IDENTIFIER lineno LBRACE PUBLIC STATIC VOID MAIN LP STRING LBRACKET RBRACKET IDENTIFIER RP LBRACE statement_list RBRACE RBRACE
#line 133 "parser.yy"
                                                                                                                                                {
        // Creating a new Node for MainClass
        yylhs.value.as < Node * > () = new Node("ClassDeclaration", yystack_[16].value.as < std::string > (), yystack_[15].value.as < int > ()); // $3 is the class name (IDENTIFIER)

        // Create a new Node for the main method
        Node* mainMethodNode = new Node("MethodDeclaration", "main", yylineno);
        
        // Adding the method's signature (public static void main(String[] args))
        Node* mainMethodType = new Node("Type", "void", yylineno);
        mainMethodNode->children.push_back(mainMethodType);
        
        Node* paramNode = new Node("Parameter", "", yylineno);
        paramNode->children.push_back(new Node("Type", "String[]", yylineno));
        paramNode->children.push_back(new Node("Identifier", yystack_[5].value.as < std::string > (), yylineno)); // Parameter identifier "args"
        mainMethodNode->children.push_back(paramNode);
                
        for (Node* stmt : yystack_[2].value.as < std::list<Node*> > ()) {
            mainMethodNode->children.push_back(stmt);
        }

        // Adding the method to the class node
        yylhs.value.as < Node * > ()->children.push_back(mainMethodNode);
    }
#line 1045 "parser.tab.cc"
    break;

  case 19: // ClassDeclaration: CLASS IDENTIFIER lineno LBRACE variables MethodDeclaration_list RBRACE
#line 159 "parser.yy"
                                                                          {
        yylhs.value.as < Node * > () = new Node("ClassDeclaration", yystack_[5].value.as < std::string > (), yystack_[4].value.as < int > ());
        for (Node* var : yystack_[2].value.as < std::list<Node*> > ()) yylhs.value.as < Node * > ()->children.push_back(var);

        for (Node* method : yystack_[1].value.as < std::list<Node*> > ()) yylhs.value.as < Node * > ()->children.push_back(method);
    }
#line 1056 "parser.tab.cc"
    break;

  case 20: // MethodDeclaration: PUBLIC Type IDENTIFIER lineno LP parameter_sequence RP LBRACE Methodbody RETURN expression SEMICOLON RBRACE
#line 169 "parser.yy"
                                                                                                                {
        yylhs.value.as < Node * > () = new Node("MethodDeclaration", yystack_[10].value.as < std::string > (), yystack_[9].value.as < int > ());
        yylhs.value.as < Node * > ()->children.push_back(new Node("Type", yystack_[11].value.as < std::string > (), yylineno));

        for (Node* param : yystack_[7].value.as < std::list<Node*> > ()) yylhs.value.as < Node * > ()->children.push_back(param);

        for (Node* stmt : yystack_[4].value.as < std::list<Node*> > ()) yylhs.value.as < Node * > ()->children.push_back(stmt);
    }
#line 1069 "parser.tab.cc"
    break;

  case 21: // Methodbody: %empty
#line 180 "parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 1075 "parser.tab.cc"
    break;

  case 22: // Methodbody: Methodbody VarDeclaration
#line 181 "parser.yy"
                                { 
        yylhs.value.as < std::list<Node*> > () = yystack_[1].value.as < std::list<Node*> > (); 
        yylhs.value.as < std::list<Node*> > ().push_back(yystack_[0].value.as < Node * > ());
    }
#line 1084 "parser.tab.cc"
    break;

  case 23: // Methodbody: Methodbody statement
#line 185 "parser.yy"
                           {
        yylhs.value.as < std::list<Node*> > () = yystack_[1].value.as < std::list<Node*> > (); 
        yylhs.value.as < std::list<Node*> > ().push_back(yystack_[0].value.as < Node * > ());
    }
#line 1093 "parser.tab.cc"
    break;

  case 24: // parameter: Type IDENTIFIER
#line 192 "parser.yy"
                    {
        yylhs.value.as < Node * > () = new Node("Parameter", "", yylineno);
        yylhs.value.as < Node * > ()->children.push_back(new Node("Type", yystack_[1].value.as < std::string > (), yylineno));
        yylhs.value.as < Node * > ()->children.push_back(new Node("Identifier", yystack_[0].value.as < std::string > (), yylineno));
    }
#line 1103 "parser.tab.cc"
    break;

  case 25: // parameter_list: parameter
#line 200 "parser.yy"
              { 
        yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); 
        yylhs.value.as < std::list<Node*> > ().push_back(yystack_[0].value.as < Node * > ());
    }
#line 1112 "parser.tab.cc"
    break;

  case 26: // parameter_list: parameter_list COMMA parameter
#line 204 "parser.yy"
                                     { 
        yylhs.value.as < std::list<Node*> > () = yystack_[2].value.as < std::list<Node*> > (); 
        yylhs.value.as < std::list<Node*> > ().push_back(yystack_[0].value.as < Node * > ());
    }
#line 1121 "parser.tab.cc"
    break;

  case 27: // parameter_sequence: parameter_list
#line 211 "parser.yy"
                   { yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > (); }
#line 1127 "parser.tab.cc"
    break;

  case 28: // parameter_sequence: %empty
#line 212 "parser.yy"
                  { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 1133 "parser.tab.cc"
    break;

  case 29: // expression: expression PLUSOP expression
#line 218 "parser.yy"
                                         { 
                            yylhs.value.as < Node * > () = new Node("AddExpression", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                          }
#line 1143 "parser.tab.cc"
    break;

  case 30: // expression: expression MINUSOP expression
#line 223 "parser.yy"
                                            {
                            yylhs.value.as < Node * > () = new Node("SubExpression", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                          }
#line 1153 "parser.tab.cc"
    break;

  case 31: // expression: expression MULTOP expression
#line 228 "parser.yy"
                                           {
                            yylhs.value.as < Node * > () = new Node("MultExpression", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                          }
#line 1163 "parser.tab.cc"
    break;

  case 32: // expression: expression AND expression
#line 233 "parser.yy"
                                        { 
                yylhs.value.as < Node * > () = new Node("LogicalExpression", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1173 "parser.tab.cc"
    break;

  case 33: // expression: expression OR expression
#line 238 "parser.yy"
                                       { 
                yylhs.value.as < Node * > () = new Node("LogicalExpression", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1183 "parser.tab.cc"
    break;

  case 34: // expression: expression EQ expression
#line 243 "parser.yy"
                                       { 
                yylhs.value.as < Node * > () = new Node("LogicalExpression", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1193 "parser.tab.cc"
    break;

  case 35: // expression: expression LT expression
#line 248 "parser.yy"
                                       { 
                yylhs.value.as < Node * > () = new Node("RelationalExpression", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1203 "parser.tab.cc"
    break;

  case 36: // expression: expression GT expression
#line 253 "parser.yy"
                                       { 
                yylhs.value.as < Node * > () = new Node("RelationalExpression", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1213 "parser.tab.cc"
    break;

  case 37: // expression: expression LBRACKET expression RBRACKET
#line 258 "parser.yy"
                                                      {
                yylhs.value.as < Node * > () = new Node("ArrayAccess", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ());
                yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
            }
#line 1223 "parser.tab.cc"
    break;

  case 38: // expression: expression DOT length
#line 263 "parser.yy"
                                    {
                yylhs.value.as < Node * > () = new Node("ArrayLength", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
            }
#line 1232 "parser.tab.cc"
    break;

  case 39: // expression: expression DOT IDENTIFIER LP expression_sequence RP
#line 267 "parser.yy"
                                                                  { 
                yylhs.value.as < Node * > () = new Node("MethodCall", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(new Node("Identifier", yystack_[3].value.as < std::string > (), yylineno));
                yylhs.value.as < Node * > ()->children.push_back(yystack_[5].value.as < Node * > ());

                for (Node* arg : yystack_[1].value.as < std::list<Node*> > ()) {  // Iterate over list
                    yylhs.value.as < Node * > ()->children.push_back(arg);
                }
            }
#line 1246 "parser.tab.cc"
    break;

  case 40: // expression: NEW INTIGER LBRACKET expression RBRACKET
#line 276 "parser.yy"
                                                      {
                yylhs.value.as < Node * > () = new Node("Array_Instantiation", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(new Node("Type", "int", yylineno));
                yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); // Array size expression
            }
#line 1256 "parser.tab.cc"
    break;

  case 41: // expression: NEW IDENTIFIER LP RP
#line 281 "parser.yy"
                                  {
                yylhs.value.as < Node * > () = new Node("Object_Instantiation", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(new Node("Identifier", yystack_[2].value.as < std::string > (), yylineno)); // Store class name
            }
#line 1265 "parser.tab.cc"
    break;

  case 42: // expression: factor
#line 286 "parser.yy"
                     { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1271 "parser.tab.cc"
    break;

  case 43: // expression_list: expression
#line 290 "parser.yy"
               { 
        yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); 
        yylhs.value.as < std::list<Node*> > ().push_back(yystack_[0].value.as < Node * > ());
    }
#line 1280 "parser.tab.cc"
    break;

  case 44: // expression_list: expression_list COMMA expression
#line 294 "parser.yy"
                                       { 
        yylhs.value.as < std::list<Node*> > () = yystack_[2].value.as < std::list<Node*> > (); 
        yylhs.value.as < std::list<Node*> > ().push_back(yystack_[0].value.as < Node * > ());
    }
#line 1289 "parser.tab.cc"
    break;

  case 45: // expression_sequence: expression_list
#line 301 "parser.yy"
                    { yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > (); }
#line 1295 "parser.tab.cc"
    break;

  case 46: // expression_sequence: %empty
#line 302 "parser.yy"
                  { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 1301 "parser.tab.cc"
    break;

  case 47: // MethodDeclaration_list: %empty
#line 308 "parser.yy"
                { 
        yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); // Create an empty list for no methods
      }
#line 1309 "parser.tab.cc"
    break;

  case 48: // MethodDeclaration_list: MethodDeclaration MethodDeclaration_list
#line 311 "parser.yy"
                                               { 
          yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > (); 
          yylhs.value.as < std::list<Node*> > ().insert(yylhs.value.as < std::list<Node*> > ().begin(), yystack_[1].value.as < Node * > ()); // Insert the new method before the rest
    }
#line 1318 "parser.tab.cc"
    break;

  case 49: // statement_list: statement
#line 319 "parser.yy"
             { 
          yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); 
          yylhs.value.as < std::list<Node*> > ().push_back(yystack_[0].value.as < Node * > ()); 
    }
#line 1327 "parser.tab.cc"
    break;

  case 50: // statement_list: statement statement_list
#line 323 "parser.yy"
                               { 
          yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > (); 
          yylhs.value.as < std::list<Node*> > ().insert(yylhs.value.as < std::list<Node*> > ().begin(), yystack_[1].value.as < Node * > ()); // Add statement before the rest
    }
#line 1336 "parser.tab.cc"
    break;

  case 51: // VarDeclaration: Type IDENTIFIER SEMICOLON
#line 330 "parser.yy"
                              {
        yylhs.value.as < Node * > () = new Node("VarDeclaration", "", yylineno);
        yylhs.value.as < Node * > ()->children.push_back(new Node("Type", yystack_[2].value.as < std::string > (), yylineno));
        yylhs.value.as < Node * > ()->children.push_back(new Node("Identifier", yystack_[1].value.as < std::string > (), yylineno));
    }
#line 1346 "parser.tab.cc"
    break;

  case 52: // variables: %empty
#line 339 "parser.yy"
                  { 
          yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); // Create an empty list for no variables
      }
#line 1354 "parser.tab.cc"
    break;

  case 53: // variables: VarDeclaration variables
#line 342 "parser.yy"
                               { 
          yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > (); 
          yylhs.value.as < std::list<Node*> > ().insert(yylhs.value.as < std::list<Node*> > ().begin(), yystack_[1].value.as < Node * > ()); // Insert the new variable before the rest
      }
#line 1363 "parser.tab.cc"
    break;

  case 54: // factor: INT
#line 348 "parser.yy"
                          { yylhs.value.as < Node * > () = new Node("Int", yystack_[0].value.as < std::string > (), yylineno); }
#line 1369 "parser.tab.cc"
    break;

  case 55: // factor: LP expression RP
#line 349 "parser.yy"
                               { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); }
#line 1375 "parser.tab.cc"
    break;

  case 56: // factor: IDENTIFIER
#line 350 "parser.yy"
                         { yylhs.value.as < Node * > () = new Node("Identifier", yystack_[0].value.as < std::string > (), yylineno); }
#line 1381 "parser.tab.cc"
    break;

  case 57: // factor: MINUSOP factor
#line 351 "parser.yy"
                             { 
                yylhs.value.as < Node * > () = new Node("Negate", "", yylineno); 
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
            }
#line 1390 "parser.tab.cc"
    break;

  case 58: // factor: NOT factor
#line 355 "parser.yy"
                         {
                yylhs.value.as < Node * > () = new Node("LogicalNot", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1399 "parser.tab.cc"
    break;

  case 59: // factor: TRUE
#line 359 "parser.yy"
                   { yylhs.value.as < Node * > () = new Node("Boolean", "true", yylineno); }
#line 1405 "parser.tab.cc"
    break;

  case 60: // factor: FALSE
#line 360 "parser.yy"
                    { yylhs.value.as < Node * > () = new Node("Boolean", "false", yylineno); }
#line 1411 "parser.tab.cc"
    break;

  case 61: // factor: THIS
#line 361 "parser.yy"
                   { yylhs.value.as < Node * > () = new Node("This", "this", yylineno); }
#line 1417 "parser.tab.cc"
    break;


#line 1421 "parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -69;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
       4,    15,    22,   -69,    19,    25,   -69,    29,   -69,    19,
     -69,   -69,   -69,    18,    38,    58,   -15,    56,   -69,   -69,
      46,    47,   -15,    61,    67,    48,    54,   -69,   -15,    61,
      63,    55,   -69,   -69,    72,   -69,   -69,    50,   -69,    57,
      52,    69,   -15,    73,    77,   -69,    78,    60,    83,   -69,
     -15,    91,    64,   -69,   -69,    92,    40,    37,    76,    87,
      39,    88,   -10,    37,   -69,   -69,   -10,    37,   102,    39,
      39,   -14,   -69,   -69,   -69,   -69,    70,    70,   -69,    39,
     153,   -69,    39,    39,    39,   109,   -69,   117,    84,    99,
     103,   118,   -69,   -69,   114,    39,    39,    39,   124,    39,
     -13,    39,    39,    39,    39,    39,   129,   168,   189,   -69,
     -69,   131,    37,   116,    39,   -69,    59,    59,    59,   -69,
     204,   121,   -69,   270,   270,    28,    28,   -17,    37,   132,
     -69,   -69,   -69,   -69,   219,   -69,    39,   154,    39,   -69,
     255,   135,   123,    37,   240,    39,   -69,   -69,   -69,   255
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     2,     4,     0,     1,     0,     3,     4,
      10,    10,     5,     0,     0,     0,    52,     0,     9,     7,
       8,     0,    52,    47,     0,     0,     0,    53,     0,    47,
       0,     0,     6,    51,     0,    48,    19,     0,    10,     0,
       0,     0,    28,     0,     0,    25,    27,     0,     0,    24,
       0,     0,     0,    26,    21,     0,     0,     0,     0,     0,
       0,     0,     9,     0,    23,    22,     0,    49,     0,     0,
       0,     0,    61,    59,    60,    56,     0,     0,    54,     0,
       0,    42,     0,     0,     0,     0,    50,     0,     0,     0,
       0,     0,    58,    57,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    11,
      18,     0,     0,     0,     0,    55,    34,    35,    36,    20,
       0,     0,    38,    32,    33,    29,    30,    31,     0,     0,
      16,    15,    14,    41,     0,    37,    46,    12,     0,    40,
      43,    45,     0,     0,     0,     0,    39,    13,    17,    44
  };

  const short
  parser::yypgoto_[] =
  {
     -69,   -69,   -69,   162,   -24,    -8,   -56,   -69,   -69,   -69,
     -69,   122,   -69,   -69,   -68,   -69,   -69,   148,   -55,   125,
     156,   -38
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     2,     3,     8,    21,    13,    67,     4,     9,    29,
      56,    45,    46,    47,    80,   141,   142,    30,    68,    22,
      23,    81
  };

  const unsigned char
  parser::yytable_[] =
  {
      64,    88,    89,    14,    34,    18,    90,   121,    85,     1,
      99,    94,    86,   100,   106,   107,   108,    83,    44,    84,
      19,     5,     6,    20,    91,     7,    44,   116,   117,   118,
      40,   120,   122,   123,   124,   125,   126,   127,    92,    93,
      58,    59,    15,    58,    59,    10,   134,    61,    60,    11,
      61,    71,    72,    73,    74,    99,   132,    66,   100,    75,
      62,    63,    16,    17,    63,    24,    28,    26,   140,   105,
     144,    76,   137,    25,    31,    19,    32,   149,    20,    77,
      33,    78,    79,    72,    73,    74,    99,   147,    36,   100,
      75,    37,    38,    39,    41,    42,    43,    49,   103,   104,
     105,    48,    76,    52,    51,    95,    96,    97,    55,    50,
      77,    99,    78,    79,   100,    54,    57,   101,   102,    69,
      95,    96,    97,   103,   104,   105,    99,    87,   111,   100,
      70,    82,   101,   102,   109,    95,    96,    97,   103,   104,
     105,    99,   110,   112,   100,   114,   113,   101,   102,   119,
      95,    96,    97,   103,   104,   105,    99,   131,   115,   100,
     133,   138,   101,   102,   136,   143,   145,   146,   103,   104,
     105,    12,    53,   128,    95,    96,    97,    35,    27,    98,
      99,    65,     0,   100,     0,     0,   101,   102,     0,    95,
      96,    97,   103,   104,   105,    99,   129,     0,   100,     0,
       0,   101,   102,     0,     0,     0,     0,   103,   104,   105,
      95,    96,    97,     0,     0,   130,    99,     0,     0,   100,
       0,     0,   101,   102,     0,    95,    96,    97,   103,   104,
     105,    99,   135,     0,   100,     0,     0,   101,   102,     0,
      95,    96,    97,   103,   104,   105,    99,   139,     0,   100,
       0,     0,   101,   102,     0,     0,     0,     0,   103,   104,
     105,    95,    96,    97,     0,     0,   148,    99,     0,     0,
     100,     0,     0,   101,   102,     0,    95,    96,    97,   103,
     104,   105,    99,     0,     0,   100,     0,     0,   101,   102,
       0,    95,    96,    97,   103,   104,   105,    99,     0,     0,
     100,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     104,   105
  };

  const short
  parser::yycheck_[] =
  {
      56,    69,    70,    11,    28,    20,    20,    20,    63,     5,
      27,    79,    67,    30,    82,    83,    84,    27,    42,    29,
      35,     6,     0,    38,    38,     6,    50,    95,    96,    97,
      38,    99,    45,   101,   102,   103,   104,   105,    76,    77,
       3,     4,    24,     3,     4,    20,   114,    10,     8,    20,
      10,    12,    13,    14,    15,    27,   112,    20,    30,    20,
      20,    24,    24,     5,    24,     9,     5,    20,   136,    41,
     138,    32,   128,    27,     7,    35,    28,   145,    38,    40,
      26,    42,    43,    13,    14,    15,    27,   143,    25,    30,
      20,    36,    20,    43,    37,    43,    27,    20,    39,    40,
      41,    28,    32,    20,    44,    21,    22,    23,    44,    31,
      40,    27,    42,    43,    30,    24,    24,    33,    34,    43,
      21,    22,    23,    39,    40,    41,    27,    25,    44,    30,
      43,    43,    33,    34,    25,    21,    22,    23,    39,    40,
      41,    27,    25,    44,    30,    27,    43,    33,    34,    25,
      21,    22,    23,    39,    40,    41,    27,    26,    44,    30,
      44,    29,    33,    34,    43,    11,    31,    44,    39,    40,
      41,     9,    50,    44,    21,    22,    23,    29,    22,    26,
      27,    56,    -1,    30,    -1,    -1,    33,    34,    -1,    21,
      22,    23,    39,    40,    41,    27,    28,    -1,    30,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    39,    40,    41,
      21,    22,    23,    -1,    -1,    26,    27,    -1,    -1,    30,
      -1,    -1,    33,    34,    -1,    21,    22,    23,    39,    40,
      41,    27,    28,    -1,    30,    -1,    -1,    33,    34,    -1,
      21,    22,    23,    39,    40,    41,    27,    28,    -1,    30,
      -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    39,    40,
      41,    21,    22,    23,    -1,    -1,    26,    27,    -1,    -1,
      30,    -1,    -1,    33,    34,    -1,    21,    22,    23,    39,
      40,    41,    27,    -1,    -1,    30,    -1,    -1,    33,    34,
      -1,    21,    22,    23,    39,    40,    41,    27,    -1,    -1,
      30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      40,    41
  };

  const signed char
  parser::yystos_[] =
  {
       0,     5,    47,    48,    53,     6,     0,     6,    49,    54,
      20,    20,    49,    51,    51,    24,    24,     5,    20,    35,
      38,    50,    65,    66,     9,    27,    20,    66,     5,    55,
      63,     7,    28,    26,    50,    63,    25,    36,    20,    43,
      51,    37,    43,    27,    50,    57,    58,    59,    28,    20,
      31,    44,    20,    57,    24,    44,    56,    24,     3,     4,
       8,    10,    20,    24,    52,    65,    20,    52,    64,    43,
      43,    12,    13,    14,    15,    20,    32,    40,    42,    43,
      60,    67,    43,    27,    29,    64,    64,    25,    60,    60,
      20,    38,    67,    67,    60,    21,    22,    23,    26,    27,
      30,    33,    34,    39,    40,    41,    60,    60,    60,    25,
      25,    44,    44,    43,    27,    44,    60,    60,    60,    25,
      60,    20,    45,    60,    60,    60,    60,    60,    44,    28,
      26,    26,    52,    44,    60,    28,    43,    52,    29,    28,
      60,    61,    62,    11,    60,    31,    44,    52,    26,    60
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    46,    47,    48,    49,    49,    50,    50,    50,    50,
      51,    52,    52,    52,    52,    52,    52,    52,    53,    54,
      55,    56,    56,    56,    57,    58,    58,    59,    59,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    61,    61,    62,    62,    63,    63,    64,
      64,    65,    66,    66,    67,    67,    67,    67,    67,    67,
      67,    67
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     0,     2,     3,     1,     1,     1,
       0,     3,     5,     7,     5,     5,     4,     7,    19,     7,
      13,     0,     2,     2,     2,     1,     3,     1,     0,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     3,     6,
       5,     4,     1,     1,     3,     1,     0,     0,     2,     1,
       2,     3,     0,     2,     1,     3,     1,     2,     2,     1,
       1,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "SYSTEM_OUT_PRINTLN",
  "WHILE", "PUBLIC", "CLASS", "VOID", "RETURN", "STATIC", "IF", "ELSE",
  "NEW", "THIS", "TRUE", "FALSE", "FLOAT", "DOUBLE", "CHAR", "PRIVATE",
  "IDENTIFIER", "EQ", "LT", "GT", "LBRACE", "RBRACE", "SEMICOLON",
  "LBRACKET", "RBRACKET", "ASSIGN", "DOT", "COMMA", "NOT", "AND", "OR",
  "BOOLEAN", "MAIN", "STRING", "INTIGER", "PLUSOP", "MINUSOP", "MULTOP",
  "INT", "LP", "RP", "length", "$accept", "root", "Goal",
  "ClassDeclaration_list", "Type", "lineno", "statement", "MainClass",
  "ClassDeclaration", "MethodDeclaration", "Methodbody", "parameter",
  "parameter_list", "parameter_sequence", "expression", "expression_list",
  "expression_sequence", "MethodDeclaration_list", "statement_list",
  "VarDeclaration", "variables", "factor", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,    59,    59,    63,    74,    75,    82,    83,    84,    85,
      89,    94,    98,   104,   110,   115,   119,   124,   133,   159,
     169,   180,   181,   185,   192,   200,   204,   211,   212,   218,
     223,   228,   233,   238,   243,   248,   253,   258,   263,   267,
     276,   281,   286,   290,   294,   301,   302,   308,   311,   319,
     323,   330,   339,   342,   348,   349,   350,   351,   355,   359,
     360,   361
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 2012 "parser.tab.cc"

