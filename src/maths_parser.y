%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern const Expression *g_root; // A way of getting the AST out

  // ! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  const Expression *expr;
  double number;
  std::string *string;
}
%token TOK_BIT_AND TOK_BIT_OR TOK_EQ TOK_NEQ
%token TOK_GE TOK_LE TOK_G TOK_L
%token TOK_IF TOK_WHILE TOK_ELSE
%token TOK_RETURN TOK_BREAK
%token TOK_MUL TOK_DIVIDE TOK_PLUS TOK_MINUS TOK_MOD
%token TOK_LBRACKET TOK_RBRACKET TOK_SEMICOLON TOK_LCBRACKET TOK_RCBRACKET
%token TOK_N TOK_VAR VARTYPE_INT
%token TOK_SUBASSIGN TOK_MULASSIGN TOK_DIVASSIGN TOK_ADDASSIGN TOK_EQASSIGN

%type <expr> EXPR VAR_INIT ASSIGN_EXPR LOGIC_EXPR EQ_EXPR REL_EXPR ADD_EXPR MULT_EXPR UNARY FACTOR
%type <number> TOK_N
%type <string> TOK_VAR

%start ROOT

%%

ROOT  : EXPR              { g_root = $1; }
      
EXPR  : VAR_INIT { $$ = $1; }
      ;

ASSIGN_OP : TOK_SUBASSIGN //  -=
          | TOK_MULASSIGN //  *=
          | TOK_DIVASSIGN //  /=
          | TOK_ADDASSIGN //  +=
          ;
VAR_INIT : ASSIGN_EXPR
         | VARTYPE_INT TOK_VAR TOK_SEMICOLON { $$ = new Variable(*$2); }
         | VARTYPE_INT TOK_VAR TOK_EQASSIGN ASSIGN_EXPR //Create an ast for printing this
         ;
ASSIGN_EXPR : LOGIC_EXPR {$$ = $1;}
            | TOK_VAR TOK_EQASSIGN ASSIGN_EXPR {$$ = new AssignOperator(*$1,$3);}
            ;
LOGIC_EXPR : EQ_EXPR {$$ = $1;}
           | LOGIC_EXPR TOK_BIT_AND EQ_EXPR {$$ = new BitwiseAndOperator($1, $3);}
           | LOGIC_EXPR TOK_BIT_OR EQ_EXPR {$$ = new BitwiseOrOperator($1, $3);}
           ;

EQ_EXPR : REL_EXPR {$$=$1;}
        | EQ_EXPR TOK_EQ ADD_EXPR  {$$ = new EqOperator($1, $3);}
        | EQ_EXPR TOK_NEQ ADD_EXPR {$$ = new NeqOperator($1, $3);}
        ;

REL_EXPR: ADD_EXPR {$$ = $1;}
        | REL_EXPR TOK_LE ADD_EXPR {$$ = new LessThanEqualOperator($1, $3);}
        | REL_EXPR TOK_GE ADD_EXPR {$$ = new GreaterThanEqualOperator($1, $3);}
        | REL_EXPR TOK_G ADD_EXPR {$$ = new GreaterThanOperator($1, $3);}
        | REL_EXPR TOK_L ADD_EXPR {$$ = new LessThanOperator($1, $3);}
        ;

ADD_EXPR : MULT_EXPR {$$ = $1;}
         | ADD_EXPR TOK_PLUS MULT_EXPR {$$ = new AddOperator($1, $3) ; }
         | ADD_EXPR TOK_MINUS MULT_EXPR  {$$ = new SubOperator($1, $3); }
         ;

MULT_EXPR : UNARY {$$ = $1;}
          | MULT_EXPR TOK_MUL UNARY {$$ = new MulOperator($1, $3); }
          | MULT_EXPR TOK_DIVIDE UNARY { $$ = new DivOperator($1, $3); }
          | MULT_EXPR TOK_MOD UNARY {$$ = new ModOperator($1, $3);} // 
          ; 

UNARY : FACTOR      { $$ = $1; }
      | TOK_MINUS UNARY   { $$ = new NegOperator($2);}
      ;

FACTOR : TOK_N     { $$ = new Number( $1 ); }
       | TOK_VAR  { $$ = new Variable(*$1);}
       | TOK_LBRACKET EXPR TOK_RBRACKET { $$ = $2; }
       ;

STATEMENT : SELECT_STATEMENT
          | ITER_STATEMENT
          | JUMP_STATEMENT
          | EXPR_STATEMENT
          | COMPOUND_STATEMENT
          ;

EXPR_STATEMENT : TOK_SEMICOLON
               | EXPR TOK_SEMICOLON
               ;

COMPOUND_STATEMENT : TOK_LCBRACKET TOK_RCBRACKET
                   | TOK_LCBRACKET STATEMENT TOK_RBRACKET

SELECT_STATEMENT : TOK_IF TOK_LBRACKET EXPR TOK_RBRACKET STATEMENT 
                 | TOK_IF TOK_LBRACKET EXPR TOK_RBRACKET STATEMENT TOK_ELSE STATEMENT
                 ;

ITER_STATEMENT : TOK_WHILE TOK_LBRACKET EXPR TOK_RBRACKET STATEMENT
               ;

JUMP_STATEMENT : TOK_BREAK TOK_SEMICOLON
               | TOK_RETURN TOK_SEMICOLON
               | TOK_RETURN EXPR TOK_SEMICOLON
%%

const Expression *g_root;

const Expression *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
