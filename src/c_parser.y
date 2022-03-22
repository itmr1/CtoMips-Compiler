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
%token TOK_RETURN TOK_BREAK TOK_CONT
%token TOK_MUL TOK_DIVIDE TOK_PLUS TOK_MINUS TOK_MOD
%token TOK_LBRACKET TOK_RBRACKET TOK_SEMICOLON TOK_LCBRACKET TOK_RCBRACKET TOK_LSQBRACKET TOK_RSQBRACKET TOK_COMMA
%token TOK_N TOK_VAR VARTYPE_INT
%token TOK_SUBASSIGN TOK_MULASSIGN TOK_DIVASSIGN TOK_ADDASSIGN TOK_EQASSIGN TOK_MODASSIGN

%type <expr> ROOT EXPR_TREE EXPR ASSIGN_EXPR LOGIC_EXPR EQ_EXPR REL_EXPR ADD_EXPR MULT_EXPR UNARY FACTOR FUNCTION DECLARATION DECLARATOR FUNC_ARGS STATEMENT EXPR_STATEMENT FUNC_STATEMENT SELECT_STATEMENT ITER_STATEMENT JUMP_STATEMENT REC_STATEMENT REC_DECLARATION 
%type <number> TOK_N
%type <string> TOK_VAR VARTYPE_INT


%start ROOT

%%

ROOT  : EXPR_TREE       { g_root = $1; }
      ;

EXPR_TREE : EXPR {$$ = $1;}
          | EXPR_TREE EXPR   { $$ = new RecExpr($1,$2);}
          ;

EXPR  : FUNCTION { $$ = $1; }
      | DECLARATION {$$= $1; }
      ;

FUNCTION : VARTYPE_INT DECLARATOR TOK_LBRACKET FUNC_ARGS TOK_RBRACKET FUNC_STATEMENT {$$ = new FuncWithArgs("int",$2,$4,$6);}
         | VARTYPE_INT DECLARATOR TOK_LBRACKET TOK_RBRACKET FUNC_STATEMENT {$$ = new FuncNoArgs("int", $2,$5);}
         ;

/*REC_FUNCTION : FUNCTION {$$=$1;}
             | REC_FUNCTION FUNCTION {$$ = new RecExpr($1, $2);}*/

REC_DECLARATION : DECLARATION {$$=$1;}
                | REC_DECLARATION DECLARATION {$$= new RecExpr($1, $2);}
                ;

DECLARATION : VARTYPE_INT DECLARATOR TOK_SEMICOLON { $$ = new DeclareVar("int", $2); }
         | VARTYPE_INT DECLARATOR TOK_EQASSIGN ASSIGN_EXPR TOK_SEMICOLON {$$= new InitVar("int",$2,$4);}
         ;

FUNC_ARGS: VARTYPE_INT DECLARATOR { $$ = new DeclareVar("int", $2); }
         | FUNC_ARGS TOK_COMMA VARTYPE_INT DECLARATOR {$$ = new RecExpr($1, $4);}
         ;

DECLARATOR : TOK_VAR { $$ = new Variable(*$1);}
           | TOK_VAR TOK_LSQBRACKET LOGIC_EXPR TOK_RSQBRACKET {$$ = new Array(*$1, $3);}
           | TOK_VAR TOK_LSQBRACKET TOK_RSQBRACKET {$$ = new Array(*$1);}
           ;

ASSIGN_EXPR : LOGIC_EXPR {$$ = $1;}
            | TOK_VAR TOK_EQASSIGN ASSIGN_EXPR {$$ = new AssignOperator(*$1,$3);}
            | TOK_VAR TOK_ADDASSIGN ASSIGN_EXPR {$$ = new AddAssignOperator(*$1,$3);}
            | TOK_VAR TOK_SUBASSIGN ASSIGN_EXPR {$$ = new SubAssignOperator(*$1,$3);}
            | TOK_VAR TOK_MULASSIGN ASSIGN_EXPR {$$ = new MulAssignOperator(*$1,$3);}
            | TOK_VAR TOK_DIVASSIGN ASSIGN_EXPR {$$ = new DivAssignOperator(*$1,$3);}
            | TOK_VAR TOK_MODASSIGN ASSIGN_EXPR {$$ = new ModAssignOperator(*$1,$3);}
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
          | MULT_EXPR TOK_MOD UNARY {$$ = new ModOperator($1, $3);}  
          ; 

UNARY : FACTOR      { $$ = $1; }
      | TOK_MINUS UNARY   { $$ = new NegOperator($2);}
      ;

FACTOR : TOK_N     { $$ = new Number( $1 ); }
       | TOK_VAR  { $$ = new Variable(*$1);}
       | TOK_LBRACKET ASSIGN_EXPR TOK_RBRACKET { $$ = $2; }
       ;

REC_STATEMENT : STATEMENT {$$ = $1;}
              | REC_STATEMENT STATEMENT {$$ = new RecExpr($1, $2);}
              ;

STATEMENT : EXPR_STATEMENT {$$=$1;}
          | ITER_STATEMENT {$$=$1;}
          | JUMP_STATEMENT {$$=$1;}
          | SELECT_STATEMENT {$$=$1;}
          | FUNC_STATEMENT {$$=$1;}
          ;

EXPR_STATEMENT : TOK_SEMICOLON 
               | ASSIGN_EXPR TOK_SEMICOLON {$$=$1;}
               ;

FUNC_STATEMENT : TOK_LCBRACKET TOK_RCBRACKET
                   | TOK_LCBRACKET REC_STATEMENT TOK_RCBRACKET {$$ = $2;}
                   | TOK_LCBRACKET REC_DECLARATION TOK_RCBRACKET {$$ = $2;}
                   | TOK_LCBRACKET REC_DECLARATION REC_STATEMENT TOK_RCBRACKET {$$ = new RecExpr($2, $3);}

SELECT_STATEMENT : TOK_IF TOK_LBRACKET LOGIC_EXPR TOK_RBRACKET STATEMENT   {$$ = new IfStatement($3, $5, "if");} 
                 | TOK_IF TOK_LBRACKET LOGIC_EXPR TOK_RBRACKET STATEMENT TOK_ELSE STATEMENT {$$ = new IfElseStatement($3, $5, $7);}
                 ;

ITER_STATEMENT : TOK_WHILE TOK_LBRACKET LOGIC_EXPR TOK_RBRACKET STATEMENT {$$ = new WhileStatement($3, $5,"while");}
               ;

JUMP_STATEMENT : TOK_BREAK TOK_SEMICOLON {$$ = new BreakStatement("break");}
               | TOK_CONT TOK_SEMICOLON {$$ = new ContinueStatement("continue");}
               | TOK_RETURN TOK_SEMICOLON {$$ = new ReturnStatement("return");}
               | TOK_RETURN FUNCTION TOK_SEMICOLON {$$ = new ReturnExprStatement($2);}
               | TOK_RETURN LOGIC_EXPR TOK_SEMICOLON {$$ = new ReturnExprStatement($2);}
               ;
%%

const Expression *g_root;

const Expression *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
