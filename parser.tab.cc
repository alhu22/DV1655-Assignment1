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
#line 20 "parser.yy"

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
#line 58 "parser.yy"
           { root = yystack_[0].value.as < Node * > (); }
#line 867 "parser.tab.cc"
    break;

  case 3: // Goal: MainClass ClassDeclaration_list
#line 62 "parser.yy"
                                    {
        // Root node for the entire program
        yylhs.value.as < Node * > () = new Node("Goal", "", yylineno);
        yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
        // Append all class declarations
        for (Node* classNode : yystack_[0].value.as < std::list<Node*> > ()) {
            yylhs.value.as < Node * > ()->children.push_back(classNode);
        }
    }
#line 881 "parser.tab.cc"
    break;

  case 4: // ClassDeclaration_list: %empty
#line 73 "parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 887 "parser.tab.cc"
    break;

  case 5: // ClassDeclaration_list: ClassDeclaration ClassDeclaration_list
#line 74 "parser.yy"
                                             {
        yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > ();
        yylhs.value.as < std::list<Node*> > ().insert(yylhs.value.as < std::list<Node*> > ().begin(), yystack_[1].value.as < Node * > ());
    }
#line 896 "parser.tab.cc"
    break;

  case 6: // Type: INTIGER LBRACKET RBRACKET
#line 81 "parser.yy"
                                { yylhs.value.as < std::string > () = "int[]"; }
#line 902 "parser.tab.cc"
    break;

  case 7: // Type: BOOLEAN
#line 82 "parser.yy"
                            { yylhs.value.as < std::string > () = "boolean"; }
#line 908 "parser.tab.cc"
    break;

  case 8: // Type: INTIGER
#line 83 "parser.yy"
                            { yylhs.value.as < std::string > () = "int"; }
#line 914 "parser.tab.cc"
    break;

  case 9: // Type: IDENTIFIER
#line 84 "parser.yy"
                            { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 920 "parser.tab.cc"
    break;

  case 10: // statement: LBRACE statement_list RBRACE
#line 90 "parser.yy"
                                         {
                yylhs.value.as < Node * > () = new Node("Block", "", yylineno);
                yylhs.value.as < Node * > ()->children = yystack_[1].value.as < std::list<Node*> > (); // Store the list of statements inside the block
            }
#line 929 "parser.tab.cc"
    break;

  case 11: // statement: IF LP expression RP statement
#line 94 "parser.yy"
                                            { 
                yylhs.value.as < Node * > () = new Node("IfStatement", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());  // Condition
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());  // If-block
                yylhs.value.as < Node * > ()->children.push_back(new Node("EmptyElse", "", yylineno)); // No Else
            }
#line 940 "parser.tab.cc"
    break;

  case 12: // statement: IF LP expression RP statement ELSE statement
#line 100 "parser.yy"
                                                           {
                yylhs.value.as < Node * > () = new Node("IfStatement", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ());  // Condition
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());  // If-block
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());  // Else-block (Exists now)
            }
#line 951 "parser.tab.cc"
    break;

  case 13: // statement: WHILE LP expression RP statement
#line 106 "parser.yy"
                                               { 
                yylhs.value.as < Node * > () = new Node("WhileStatement", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());  // Condition
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());  // Loop body
            }
#line 961 "parser.tab.cc"
    break;

  case 14: // statement: SYSTEM_OUT_PRINTLN LP expression RP SEMICOLON
#line 111 "parser.yy"
                                                           {
                yylhs.value.as < Node * > () = new Node("Print_Statement", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ()); // Attach the expression being printed
            }
#line 970 "parser.tab.cc"
    break;

  case 15: // statement: IDENTIFIER ASSIGN expression SEMICOLON
#line 115 "parser.yy"
                                                     { 
                yylhs.value.as < Node * > () = new Node("Assignment", yystack_[3].value.as < std::string > (), yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());  // Assigned expression
            }
#line 979 "parser.tab.cc"
    break;

  case 16: // statement: IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression SEMICOLON
#line 119 "parser.yy"
                                                                                  { 
                yylhs.value.as < Node * > () = new Node("ArrayAssignment", yystack_[6].value.as < std::string > (), yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ());  // Array index
                yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());  // Assigned value
            }
#line 989 "parser.tab.cc"
    break;

  case 17: // MainClass: PUBLIC CLASS IDENTIFIER LBRACE PUBLIC STATIC VOID MAIN LP STRING LBRACKET RBRACKET IDENTIFIER RP LBRACE statement_list RBRACE RBRACE
#line 127 "parser.yy"
                                                                                                                                         {
        // Creating a new Node for MainClass
        yylhs.value.as < Node * > () = new Node("MainClass", yystack_[15].value.as < std::string > (), yylineno); // $3 is the class name (IDENTIFIER)

        // Create a new Node for the main method
        Node* mainMethodNode = new Node("MethodDeclaration", "main", yylineno);
        
        // Adding the method's signature (public static void main(String[] args))
        Node* mainMethodType = new Node("Type", "void", yylineno);
        mainMethodNode->children.push_back(mainMethodType);
        
        Node* paramNode = new Node("Parameter", "", yylineno);
        paramNode->children.push_back(new Node("Type", "String[]", yylineno));
        paramNode->children.push_back(new Node("Identifier", yystack_[5].value.as < std::string > (), yylineno)); // Parameter identifier "args"
        Node* paramsNode = new Node("Parameters", "", yylineno);
        paramsNode->children.push_back(paramNode);
        mainMethodNode->children.push_back(paramsNode);
        
        // Add statements (body of main method)
        Node* bodyNode = new Node("Body", "", yylineno);
        for (Node* stmt : yystack_[2].value.as < std::list<Node*> > ()) {
            bodyNode->children.push_back(stmt);
        }
        mainMethodNode->children.push_back(bodyNode);

        // Adding the method to the class node
        yylhs.value.as < Node * > ()->children.push_back(mainMethodNode);
    }
#line 1022 "parser.tab.cc"
    break;

  case 18: // ClassDeclaration: CLASS IDENTIFIER LBRACE variables MethodDeclaration_list RBRACE
#line 158 "parser.yy"
                                                                   {
        std::cout << "Class detected: " << yystack_[4].value.as < std::string > () << std::endl;

        yylhs.value.as < Node * > () = new Node("ClassDeclaration", yystack_[4].value.as < std::string > (), yylineno);
        Node* varsNode = new Node("Variables", "", yylineno);
        for (Node* var : yystack_[2].value.as < std::list<Node*> > ()) varsNode->children.push_back(var);
        yylhs.value.as < Node * > ()->children.push_back(varsNode);

        Node* methodsNode = new Node("Methods", "", yylineno);
        for (Node* method : yystack_[1].value.as < std::list<Node*> > ()) methodsNode->children.push_back(method);
        yylhs.value.as < Node * > ()->children.push_back(methodsNode);
    }
#line 1039 "parser.tab.cc"
    break;

  case 19: // MethodDeclaration: PUBLIC Type IDENTIFIER LP parameter_sequence RP LBRACE Methodbody RETURN expression SEMICOLON RBRACE
#line 174 "parser.yy"
                                                                                                         {
        std::cout << "Method detected: " << yystack_[9].value.as < std::string > () << " of type " << yystack_[10].value.as < std::string > () << std::endl;

        yylhs.value.as < Node * > () = new Node("MethodDeclaration", yystack_[9].value.as < std::string > (), yylineno);
        yylhs.value.as < Node * > ()->children.push_back(new Node("Type", yystack_[10].value.as < std::string > (), yylineno));

        Node* paramsNode = new Node("Parameters", "", yylineno);
        for (Node* param : yystack_[7].value.as < std::list<Node*> > ()) paramsNode->children.push_back(param);
        yylhs.value.as < Node * > ()->children.push_back(paramsNode);

        Node* bodyNode = new Node("Body", "", yylineno);
        for (Node* stmt : yystack_[4].value.as < std::list<Node*> > ()) bodyNode->children.push_back(stmt);
        yylhs.value.as < Node * > ()->children.push_back(bodyNode);
    }
#line 1058 "parser.tab.cc"
    break;

  case 20: // Methodbody: %empty
#line 191 "parser.yy"
                { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 1064 "parser.tab.cc"
    break;

  case 21: // Methodbody: Methodbody VarDeclaration
#line 192 "parser.yy"
                                { 
        yylhs.value.as < std::list<Node*> > () = yystack_[1].value.as < std::list<Node*> > (); 
        yylhs.value.as < std::list<Node*> > ().push_back(yystack_[0].value.as < Node * > ());
    }
#line 1073 "parser.tab.cc"
    break;

  case 22: // Methodbody: Methodbody statement
#line 196 "parser.yy"
                           {
        yylhs.value.as < std::list<Node*> > () = yystack_[1].value.as < std::list<Node*> > (); 
        yylhs.value.as < std::list<Node*> > ().push_back(yystack_[0].value.as < Node * > ());
    }
#line 1082 "parser.tab.cc"
    break;

  case 23: // parameter: Type IDENTIFIER
#line 203 "parser.yy"
                    {
        yylhs.value.as < Node * > () = new Node("Parameter", "", yylineno);
        yylhs.value.as < Node * > ()->children.push_back(new Node("Type", yystack_[1].value.as < std::string > (), yylineno));
        yylhs.value.as < Node * > ()->children.push_back(new Node("Identifier", yystack_[0].value.as < std::string > (), yylineno));
    }
#line 1092 "parser.tab.cc"
    break;

  case 24: // parameter_list: parameter
#line 211 "parser.yy"
              { 
        yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); 
        yylhs.value.as < std::list<Node*> > ().push_back(yystack_[0].value.as < Node * > ());
    }
#line 1101 "parser.tab.cc"
    break;

  case 25: // parameter_list: parameter_list COMMA parameter
#line 215 "parser.yy"
                                     { 
        yylhs.value.as < std::list<Node*> > () = yystack_[2].value.as < std::list<Node*> > (); 
        yylhs.value.as < std::list<Node*> > ().push_back(yystack_[0].value.as < Node * > ());
    }
#line 1110 "parser.tab.cc"
    break;

  case 26: // parameter_sequence: parameter_list
#line 222 "parser.yy"
                   { yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > (); }
#line 1116 "parser.tab.cc"
    break;

  case 27: // parameter_sequence: %empty
#line 223 "parser.yy"
                  { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 1122 "parser.tab.cc"
    break;

  case 28: // expression: expression PLUSOP expression
#line 229 "parser.yy"
                                         { 
                            yylhs.value.as < Node * > () = new Node("AddExpression", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                          }
#line 1132 "parser.tab.cc"
    break;

  case 29: // expression: expression MINUSOP expression
#line 234 "parser.yy"
                                            {
                            yylhs.value.as < Node * > () = new Node("SubExpression", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                          }
#line 1142 "parser.tab.cc"
    break;

  case 30: // expression: expression MULTOP expression
#line 239 "parser.yy"
                                           {
                            yylhs.value.as < Node * > () = new Node("MultExpression", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                          }
#line 1152 "parser.tab.cc"
    break;

  case 31: // expression: expression AND expression
#line 244 "parser.yy"
                                        { 
                yylhs.value.as < Node * > () = new Node("LogicalExpression", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1162 "parser.tab.cc"
    break;

  case 32: // expression: expression OR expression
#line 249 "parser.yy"
                                       { 
                yylhs.value.as < Node * > () = new Node("LogicalExpression", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1172 "parser.tab.cc"
    break;

  case 33: // expression: expression EQ expression
#line 254 "parser.yy"
                                       { 
                yylhs.value.as < Node * > () = new Node("LogicalExpression", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1182 "parser.tab.cc"
    break;

  case 34: // expression: expression LT expression
#line 259 "parser.yy"
                                       { 
                yylhs.value.as < Node * > () = new Node("RelationalExpression", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1192 "parser.tab.cc"
    break;

  case 35: // expression: expression GT expression
#line 264 "parser.yy"
                                       { 
                yylhs.value.as < Node * > () = new Node("RelationalExpression", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1202 "parser.tab.cc"
    break;

  case 36: // expression: expression LBRACKET expression RBRACKET
#line 269 "parser.yy"
                                                      {
                yylhs.value.as < Node * > () = new Node("ArrayAccess", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ());
                yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
            }
#line 1212 "parser.tab.cc"
    break;

  case 37: // expression: expression DOT length
#line 274 "parser.yy"
                                    {
                yylhs.value.as < Node * > () = new Node("ArrayLength", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
            }
#line 1221 "parser.tab.cc"
    break;

  case 38: // expression: expression DOT IDENTIFIER LP expression_sequence RP
#line 278 "parser.yy"
                                                                  { 
                yylhs.value.as < Node * > () = new Node("MethodCall", yystack_[3].value.as < std::string > (), yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[5].value.as < Node * > ());

                Node* argsNode = new Node("Arguments", "", yylineno);
                for (Node* arg : yystack_[1].value.as < std::list<Node*> > ()) {  // Iterate over list
                    argsNode->children.push_back(arg);
                }
                yylhs.value.as < Node * > ()->children.push_back(argsNode); // Attach argument list
            }
#line 1236 "parser.tab.cc"
    break;

  case 39: // expression: NEW INTIGER LBRACKET expression RBRACKET
#line 288 "parser.yy"
                                                      {
                yylhs.value.as < Node * > () = new Node("Array_Instantiation", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(new Node("Type", "int", yylineno));
                yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ()); // Array size expression
            }
#line 1246 "parser.tab.cc"
    break;

  case 40: // expression: NEW IDENTIFIER LP RP
#line 293 "parser.yy"
                                  {
                yylhs.value.as < Node * > () = new Node("Object_Instantiation", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(new Node("ClassName", yystack_[2].value.as < std::string > (), yylineno)); // Store class name
            }
#line 1255 "parser.tab.cc"
    break;

  case 41: // expression: factor
#line 298 "parser.yy"
                     { yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); }
#line 1261 "parser.tab.cc"
    break;

  case 42: // expression_list: expression
#line 302 "parser.yy"
               { 
        yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); 
        yylhs.value.as < std::list<Node*> > ().push_back(yystack_[0].value.as < Node * > ());
    }
#line 1270 "parser.tab.cc"
    break;

  case 43: // expression_list: expression_list COMMA expression
#line 306 "parser.yy"
                                       { 
        yylhs.value.as < std::list<Node*> > () = yystack_[2].value.as < std::list<Node*> > (); 
        yylhs.value.as < std::list<Node*> > ().push_back(yystack_[0].value.as < Node * > ());
    }
#line 1279 "parser.tab.cc"
    break;

  case 44: // expression_sequence: expression_list
#line 313 "parser.yy"
                    { yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > (); }
#line 1285 "parser.tab.cc"
    break;

  case 45: // expression_sequence: %empty
#line 314 "parser.yy"
                  { yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); }
#line 1291 "parser.tab.cc"
    break;

  case 46: // MethodDeclaration_list: %empty
#line 320 "parser.yy"
                { 
        yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); // Create an empty list for no methods
      }
#line 1299 "parser.tab.cc"
    break;

  case 47: // MethodDeclaration_list: MethodDeclaration MethodDeclaration_list
#line 323 "parser.yy"
                                               { 
          yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > (); 
          yylhs.value.as < std::list<Node*> > ().insert(yylhs.value.as < std::list<Node*> > ().begin(), yystack_[1].value.as < Node * > ()); // Insert the new method before the rest
    }
#line 1308 "parser.tab.cc"
    break;

  case 48: // statement_list: statement
#line 331 "parser.yy"
             { 
          yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); 
          yylhs.value.as < std::list<Node*> > ().push_back(yystack_[0].value.as < Node * > ()); 
    }
#line 1317 "parser.tab.cc"
    break;

  case 49: // statement_list: statement statement_list
#line 335 "parser.yy"
                               { 
          yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > (); 
          yylhs.value.as < std::list<Node*> > ().insert(yylhs.value.as < std::list<Node*> > ().begin(), yystack_[1].value.as < Node * > ()); // Add statement before the rest
    }
#line 1326 "parser.tab.cc"
    break;

  case 50: // VarDeclaration: Type IDENTIFIER SEMICOLON
#line 342 "parser.yy"
                              {
        yylhs.value.as < Node * > () = new Node("VarDeclaration", "", yylineno);
        yylhs.value.as < Node * > ()->children.push_back(new Node("Type", yystack_[2].value.as < std::string > (), yylineno));
        yylhs.value.as < Node * > ()->children.push_back(new Node("Identifier", yystack_[1].value.as < std::string > (), yylineno));
    }
#line 1336 "parser.tab.cc"
    break;

  case 51: // variables: %empty
#line 351 "parser.yy"
                  { 
          yylhs.value.as < std::list<Node*> > () = std::list<Node*>(); // Create an empty list for no variables
      }
#line 1344 "parser.tab.cc"
    break;

  case 52: // variables: VarDeclaration variables
#line 354 "parser.yy"
                               { 
          yylhs.value.as < std::list<Node*> > () = yystack_[0].value.as < std::list<Node*> > (); 
          yylhs.value.as < std::list<Node*> > ().insert(yylhs.value.as < std::list<Node*> > ().begin(), yystack_[1].value.as < Node * > ()); // Insert the new variable before the rest
      }
#line 1353 "parser.tab.cc"
    break;

  case 53: // factor: INT
#line 360 "parser.yy"
                          { yylhs.value.as < Node * > () = new Node("Int", yystack_[0].value.as < std::string > (), yylineno); }
#line 1359 "parser.tab.cc"
    break;

  case 54: // factor: LP expression RP
#line 361 "parser.yy"
                               { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); }
#line 1365 "parser.tab.cc"
    break;

  case 55: // factor: IDENTIFIER
#line 362 "parser.yy"
                         { yylhs.value.as < Node * > () = new Node("Identifier", yystack_[0].value.as < std::string > (), yylineno); }
#line 1371 "parser.tab.cc"
    break;

  case 56: // factor: MINUSOP factor
#line 363 "parser.yy"
                             { 
                yylhs.value.as < Node * > () = new Node("Negate", "", yylineno); 
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ()); 
            }
#line 1380 "parser.tab.cc"
    break;

  case 57: // factor: NOT factor
#line 367 "parser.yy"
                         {
                yylhs.value.as < Node * > () = new Node("LogicalNot", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1389 "parser.tab.cc"
    break;

  case 58: // factor: TRUE
#line 371 "parser.yy"
                   { yylhs.value.as < Node * > () = new Node("Boolean", "true", yylineno); }
#line 1395 "parser.tab.cc"
    break;

  case 59: // factor: FALSE
#line 372 "parser.yy"
                    { yylhs.value.as < Node * > () = new Node("Boolean", "false", yylineno); }
#line 1401 "parser.tab.cc"
    break;

  case 60: // factor: THIS
#line 373 "parser.yy"
                   { yylhs.value.as < Node * > () = new Node("This", "this", yylineno); }
#line 1407 "parser.tab.cc"
    break;


#line 1411 "parser.tab.cc"

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


  const signed char parser::yypact_ninf_ = -63;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
       3,    12,    40,   -63,    39,    30,   -63,    32,   -63,    39,
      42,    52,   -63,    72,   -13,    69,   -63,   -63,    56,    59,
     -13,    76,    78,    61,    58,   -63,   -13,    76,    62,    55,
     -63,   -63,    75,   -63,   -63,    60,    63,    64,   -13,    81,
      82,   -63,    74,    65,    84,   -63,   -13,    96,   103,   -63,
     -63,    80,    23,   111,    95,    99,    50,   110,    -8,     0,
     -63,   -63,     0,    50,    50,   -15,   -63,   -63,   -63,   -63,
      54,    54,   -63,    50,   146,   -63,    50,    50,    50,    -8,
       0,   102,   114,    77,    92,   115,   123,   -63,   -63,   107,
      50,    50,    50,   129,    50,    -3,    50,    50,    50,    50,
      50,   122,   161,   182,   -63,   -63,   132,   133,     0,   116,
      50,   -63,    14,    14,    14,   -63,   197,   121,   -63,   263,
     263,    19,    19,   -21,     0,   136,   -63,   -63,   -63,   -63,
     -63,   212,   -63,    50,   159,    50,   -63,   248,   140,   130,
       0,   233,    50,   -63,   -63,   -63,   248
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     2,     4,     0,     1,     0,     3,     4,
       0,     0,     5,     0,    51,     0,     9,     7,     8,     0,
      51,    46,     0,     0,     0,    52,     0,    46,     0,     0,
       6,    50,     0,    47,    18,     0,     0,     0,    27,     0,
       0,    24,    26,     0,     0,    23,     0,     0,     0,    25,
      20,     0,     0,     0,     0,     0,     0,     0,     9,     0,
      22,    21,     0,     0,     0,     0,    60,    58,    59,    55,
       0,     0,    53,     0,     0,    41,     0,     0,     0,     0,
      48,     0,     0,     0,     0,     0,     0,    57,    56,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    49,    10,     0,     0,     0,     0,
       0,    54,    33,    34,    35,    19,     0,     0,    37,    31,
      32,    28,    29,    30,     0,     0,    15,    17,    14,    13,
      40,     0,    36,    45,    11,     0,    39,    42,    44,     0,
       0,     0,     0,    38,    12,    16,    43
  };

  const short
  parser::yypgoto_[] =
  {
     -63,   -63,   -63,   166,    13,   -52,   -63,   -63,   -63,   -63,
     131,   -63,   -63,   -62,   -63,   -63,   151,    -5,   138,   172,
     -58
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     2,     3,     8,    19,    80,     4,     9,    27,    52,
      41,    42,    43,    74,   138,   139,    28,    81,    20,    21,
      75
  };

  const unsigned char
  parser::yytable_[] =
  {
      60,    83,    84,    54,    55,    85,    94,    16,     1,    95,
      57,    89,    87,    88,   101,   102,   103,   117,     5,    77,
      79,    78,    17,    86,    59,    18,    54,    55,   112,   113,
     114,    56,   116,    57,   119,   120,   121,   122,   123,    32,
       6,    94,   118,    58,    95,     7,    94,    59,   131,    95,
      10,    40,    11,    98,    99,   100,   129,    82,    17,    40,
     100,    18,    65,    66,    67,    68,    13,    66,    67,    68,
      69,   137,   134,   141,    69,   104,    14,    15,    22,    24,
     146,    26,    70,    23,    31,    29,    70,    34,   144,    30,
      71,    35,    72,    73,    71,    36,    72,    73,    90,    91,
      92,    39,    45,    37,    94,    46,    38,    95,    44,    47,
      96,    97,    48,    90,    91,    92,    98,    99,   100,    94,
      50,   107,    95,    51,    53,    96,    97,   105,    90,    91,
      92,    98,    99,   100,    94,    62,   108,    95,    63,   106,
      96,    97,    64,    90,    91,    92,    98,    99,   100,    94,
     110,   111,    95,    76,   115,    96,    97,   127,   109,   128,
     130,    98,    99,   100,   133,   135,   124,    90,    91,    92,
     140,   142,    93,    94,   143,    12,    95,    49,    33,    96,
      97,     0,    90,    91,    92,    98,    99,   100,    94,   125,
      61,    95,    25,     0,    96,    97,     0,     0,     0,     0,
      98,    99,   100,    90,    91,    92,     0,     0,   126,    94,
       0,     0,    95,     0,     0,    96,    97,     0,    90,    91,
      92,    98,    99,   100,    94,   132,     0,    95,     0,     0,
      96,    97,     0,    90,    91,    92,    98,    99,   100,    94,
     136,     0,    95,     0,     0,    96,    97,     0,     0,     0,
       0,    98,    99,   100,    90,    91,    92,     0,     0,   145,
      94,     0,     0,    95,     0,     0,    96,    97,     0,    90,
      91,    92,    98,    99,   100,    94,     0,     0,    95,     0,
       0,    96,    97,     0,    90,    91,    92,    98,    99,   100,
      94,     0,     0,    95,     0,     0,     0,     0,     0,     0,
       0,     0,    98,    99,   100
  };

  const short
  parser::yycheck_[] =
  {
      52,    63,    64,     3,     4,    20,    27,    20,     5,    30,
      10,    73,    70,    71,    76,    77,    78,    20,     6,    27,
      20,    29,    35,    38,    24,    38,     3,     4,    90,    91,
      92,     8,    94,    10,    96,    97,    98,    99,   100,    26,
       0,    27,    45,    20,    30,     6,    27,    24,   110,    30,
      20,    38,    20,    39,    40,    41,   108,    62,    35,    46,
      41,    38,    12,    13,    14,    15,    24,    13,    14,    15,
      20,   133,   124,   135,    20,    80,    24,     5,     9,    20,
     142,     5,    32,    27,    26,     7,    32,    25,   140,    28,
      40,    36,    42,    43,    40,    20,    42,    43,    21,    22,
      23,    37,    20,    43,    27,    31,    43,    30,    27,    44,
      33,    34,    28,    21,    22,    23,    39,    40,    41,    27,
      24,    44,    30,    20,    44,    33,    34,    25,    21,    22,
      23,    39,    40,    41,    27,    24,    44,    30,    43,    25,
      33,    34,    43,    21,    22,    23,    39,    40,    41,    27,
      27,    44,    30,    43,    25,    33,    34,    25,    43,    26,
      44,    39,    40,    41,    43,    29,    44,    21,    22,    23,
      11,    31,    26,    27,    44,     9,    30,    46,    27,    33,
      34,    -1,    21,    22,    23,    39,    40,    41,    27,    28,
      52,    30,    20,    -1,    33,    34,    -1,    -1,    -1,    -1,
      39,    40,    41,    21,    22,    23,    -1,    -1,    26,    27,
      -1,    -1,    30,    -1,    -1,    33,    34,    -1,    21,    22,
      23,    39,    40,    41,    27,    28,    -1,    30,    -1,    -1,
      33,    34,    -1,    21,    22,    23,    39,    40,    41,    27,
      28,    -1,    30,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,    39,    40,    41,    21,    22,    23,    -1,    -1,    26,
      27,    -1,    -1,    30,    -1,    -1,    33,    34,    -1,    21,
      22,    23,    39,    40,    41,    27,    -1,    -1,    30,    -1,
      -1,    33,    34,    -1,    21,    22,    23,    39,    40,    41,
      27,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    40,    41
  };

  const signed char
  parser::yystos_[] =
  {
       0,     5,    47,    48,    52,     6,     0,     6,    49,    53,
      20,    20,    49,    24,    24,     5,    20,    35,    38,    50,
      64,    65,     9,    27,    20,    65,     5,    54,    62,     7,
      28,    26,    50,    62,    25,    36,    20,    43,    43,    37,
      50,    56,    57,    58,    27,    20,    31,    44,    28,    56,
      24,    20,    55,    44,     3,     4,     8,    10,    20,    24,
      51,    64,    24,    43,    43,    12,    13,    14,    15,    20,
      32,    40,    42,    43,    59,    66,    43,    27,    29,    20,
      51,    63,    63,    59,    59,    20,    38,    66,    66,    59,
      21,    22,    23,    26,    27,    30,    33,    34,    39,    40,
      41,    59,    59,    59,    63,    25,    25,    44,    44,    43,
      27,    44,    59,    59,    59,    25,    59,    20,    45,    59,
      59,    59,    59,    59,    44,    28,    26,    25,    26,    51,
      44,    59,    28,    43,    51,    29,    28,    59,    60,    61,
      11,    59,    31,    44,    51,    26,    59
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    46,    47,    48,    49,    49,    50,    50,    50,    50,
      51,    51,    51,    51,    51,    51,    51,    52,    53,    54,
      55,    55,    55,    56,    57,    57,    58,    58,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    60,    60,    61,    61,    62,    62,    63,    63,
      64,    65,    65,    66,    66,    66,    66,    66,    66,    66,
      66
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     0,     2,     3,     1,     1,     1,
       3,     5,     7,     5,     5,     4,     7,    18,     6,    12,
       0,     2,     2,     2,     1,     3,     1,     0,     3,     3,
       3,     3,     3,     3,     3,     3,     4,     3,     6,     5,
       4,     1,     1,     3,     1,     0,     0,     2,     1,     2,
       3,     0,     2,     1,     3,     1,     2,     2,     1,     1,
       1
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
  "ClassDeclaration_list", "Type", "statement", "MainClass",
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
       0,    58,    58,    62,    73,    74,    81,    82,    83,    84,
      90,    94,   100,   106,   111,   115,   119,   127,   158,   174,
     191,   192,   196,   203,   211,   215,   222,   223,   229,   234,
     239,   244,   249,   254,   259,   264,   269,   274,   278,   288,
     293,   298,   302,   306,   313,   314,   320,   323,   331,   335,
     342,   351,   354,   360,   361,   362,   363,   367,   371,   372,
     373
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
#line 2000 "parser.tab.cc"

