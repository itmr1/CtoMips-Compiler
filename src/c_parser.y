%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern const Expression *g_root; // A way of getting the AST out
  extern FILE *yyin;
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

%token TOK_BIT_AND TOK_BIT_OR TOK_EQ TOK_NEQ TOK_BIT_XOR TOK_LOGIC_AND TOK_LOGIC_OR TOK_LSHIFT TOK_RSHIFT TOK_LOGIC_NOT TOK_BIT_NOT
%token TOK_GE TOK_LE TOK_G TOK_L
%token TOK_IF TOK_WHILE TOK_ELSE TOK_FOR TOK_SWITCH TOK_CASE TOK_DEFAULT 
%token TOK_RETURN TOK_BREAK TOK_CONT
%token TOK_MUL TOK_DIVIDE TOK_PLUS TOK_MINUS TOK_MOD
%token TOK_LBRACKET TOK_RBRACKET TOK_SEMICOLON TOK_LCBRACKET TOK_RCBRACKET TOK_LSQBRACKET TOK_RSQBRACKET TOK_COMMA TOK_QMARK TOK_COLON
%token TOK_N TOK_VAR VARTYPE_INT
%token TOK_SUBASSIGN TOK_MULASSIGN TOK_DIVASSIGN TOK_ADDASSIGN TOK_EQASSIGN TOK_MODASSIGN TOK_ANDASSIGN TOK_ORASSIGN TOK_XORASSIGN TOK_INCR TOK_DECR


%type <expr> ROOT ARG_SINGLE SINGLE_DECL EXPR_SINGLE EXPR_TREE COND_EXPR ASSIGN_EXPR LOGIC_EXPR SWITCH_STATEMENT BIT_EXPR EQ_EXPR REL_EXPR SHIFT_EXPR ADD_EXPR MULT_EXPR UNARY FACTOR FUNCTION DECLARATION DECLARATOR ARRAY_DECLARATOR FUNC_ARGS FUNC_CALL_ARGS STATEMENT EXPR_STATEMENT FUNC_STATEMENT SELECT_STATEMENT ITER_STATEMENT JUMP_STATEMENT REC_STATEMENT REC_DECLARATION 
%type <number> TOK_N
%type <string> TOK_VAR VARTYPE_INT


%start ROOT

%%

ROOT  : EXPR_TREE       { g_root = $1; }
      ;

EXPR_TREE //: EXPR {$$ = $1 ;}
          : EXPR_SINGLE {$$ = $1;}
          | EXPR_TREE EXPR_SINGLE   { $$ = new RecExpr($1,$2);}
          ;

EXPR_SINGLE  : FUNCTION { $$ = $1; }
      | DECLARATION {$$= $1; }
      ;

FUNCTION : VARTYPE_INT DECLARATOR TOK_LBRACKET FUNC_ARGS TOK_RBRACKET FUNC_STATEMENT {$$ = new FuncWithArgs("int",$2,$4,$6);}
         | VARTYPE_INT DECLARATOR TOK_LBRACKET TOK_RBRACKET FUNC_STATEMENT {$$ = new FuncNoArgs("int", $2,$5);}
         | VARTYPE_INT DECLARATOR TOK_LBRACKET FUNC_ARGS TOK_RBRACKET TOK_SEMICOLON {$$ = new FuncInstance("int", $2, $4);}
         | VARTYPE_INT DECLARATOR TOK_LBRACKET TOK_RBRACKET TOK_SEMICOLON {$$ = new FuncInstance("int", $2);}
         ;

/*REC_FUNCTION : FUNCTION {$$=$1;}
             | REC_FUNCTION FUNCTION {$$ = new RecExpr($1, $2);}*/

REC_DECLARATION : DECLARATION {$$=$1;}
                | REC_DECLARATION DECLARATION {$$= new RecExpr($1, $2);}
                ;

DECLARATION : VARTYPE_INT DECLARATOR TOK_SEMICOLON { $$ = new DeclareVar("int", $2); }
         | VARTYPE_INT ARRAY_DECLARATOR TOK_SEMICOLON { $$ = new DeclareArray("int", $2);}
         | VARTYPE_INT DECLARATOR TOK_EQASSIGN ASSIGN_EXPR TOK_SEMICOLON {$$= new InitVar("int",$2,$4);}
         | VARTYPE_INT ARRAY_DECLARATOR TOK_EQASSIGN TOK_LCBRACKET TOK_RCBRACKET TOK_SEMICOLON {$$ = new InitZeroArray("int",$2);}
         | VARTYPE_INT ARRAY_DECLARATOR TOK_EQASSIGN TOK_LCBRACKET FUNC_CALL_ARGS TOK_RCBRACKET TOK_SEMICOLON {$$ = new InitArray("int",$2,$5);}
         ;
SINGLE_DECL : VARTYPE_INT DECLARATOR { $$ = new DeclareVar("int", $2); }
            ;

FUNC_ARGS: ARG_SINGLE { $$ = $1; }
         | FUNC_ARGS TOK_COMMA ARG_SINGLE {$$ = new RecExpr($1, $3);}
         ;

FUNC_CALL_ARGS: ARG_SINGLE {$$=$1;}
              | FUNC_CALL_ARGS TOK_COMMA ARG_SINGLE {$$ = new RecExpr($1, $3);}
              ;

DECLARATOR : TOK_VAR { $$ = new Variable(*$1);}
           ;
          
ARRAY_DECLARATOR : TOK_VAR TOK_LSQBRACKET LOGIC_EXPR TOK_RSQBRACKET {$$ = new Array(*$1, $3);} // int p[] = {}
           | TOK_VAR TOK_LSQBRACKET TOK_RSQBRACKET {$$ = new Array(*$1);}
           ;
ARG_SINGLE: SINGLE_DECL {$$ = new SingleExpr($1);}
          | ASSIGN_EXPR {$$ =new SingleExpr($1);}
          ;
ASSIGN_EXPR : COND_EXPR {$$ = $1;}
            | FACTOR TOK_EQASSIGN ASSIGN_EXPR {$$ = new AssignOperator($1,$3);}
            | FACTOR TOK_ADDASSIGN ASSIGN_EXPR {$$ = new AddAssignOperator($1,$3);}
            | FACTOR TOK_SUBASSIGN ASSIGN_EXPR {$$ = new SubAssignOperator($1,$3);}
            | FACTOR TOK_MULASSIGN ASSIGN_EXPR {$$ = new MulAssignOperator($1,$3);}
            | FACTOR TOK_DIVASSIGN ASSIGN_EXPR {$$ = new DivAssignOperator($1,$3);}
            | FACTOR TOK_MODASSIGN ASSIGN_EXPR {$$ = new ModAssignOperator($1,$3);}
            | FACTOR TOK_ANDASSIGN ASSIGN_EXPR {$$ = new AndAssignOperator($1,$3);}
            | FACTOR TOK_ORASSIGN ASSIGN_EXPR {$$ = new OrAssignOperator($1,$3);}
            | FACTOR TOK_XORASSIGN ASSIGN_EXPR {$$ = new XorAssignOperator($1,$3);}
            ;

COND_EXPR : LOGIC_EXPR {$$=$1;}
          | LOGIC_EXPR TOK_QMARK ASSIGN_EXPR TOK_COLON COND_EXPR {$$ = new MuxOperator($1,$3,$5);}
          ;

LOGIC_EXPR : BIT_EXPR {$$ = $1;}
            | LOGIC_EXPR TOK_LOGIC_AND BIT_EXPR {$$ = new LogicalAndOperator($1, $3);}
            | LOGIC_EXPR TOK_LOGIC_OR BIT_EXPR {$$ = new LogicalOrOperator($1, $3);}
            ;

BIT_EXPR : EQ_EXPR {$$ = $1;}
           | BIT_EXPR TOK_BIT_AND EQ_EXPR {$$ = new BitwiseAndOperator($1, $3);}
           | BIT_EXPR TOK_BIT_OR EQ_EXPR {$$ = new BitwiseOrOperator($1, $3);}
           | BIT_EXPR TOK_BIT_XOR EQ_EXPR {$$ = new BitwiseXorOperator($1, $3);}
           ;//Add ^ BXOR Logical OR || and Logical AND && and MUX 

EQ_EXPR : REL_EXPR {$$=$1;}
        | EQ_EXPR TOK_EQ REL_EXPR  {$$ = new EqOperator($1, $3);}
        | EQ_EXPR TOK_NEQ REL_EXPR {$$ = new NeqOperator($1, $3);}
        ;

REL_EXPR: SHIFT_EXPR {$$ = $1;}
        | REL_EXPR TOK_LE SHIFT_EXPR {$$ = new LessThanEqualOperator($1, $3);}
        | REL_EXPR TOK_GE SHIFT_EXPR {$$ = new GreaterThanEqualOperator($1, $3);}
        | REL_EXPR TOK_G SHIFT_EXPR {$$ = new GreaterThanOperator($1, $3);}
        | REL_EXPR TOK_L SHIFT_EXPR {$$ = new LessThanOperator($1, $3);}
        ;
//Add << and >>
SHIFT_EXPR: ADD_EXPR {$$ = $1;}
          | SHIFT_EXPR TOK_LSHIFT ADD_EXPR {$$ = new LeftShiftOperator($1, $3);}
          | SHIFT_EXPR TOK_RSHIFT ADD_EXPR {$$ = new RightShiftOperator($1, $3);}

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
      | TOK_LOGIC_NOT UNARY   { $$ = new LogicalNotOperator($2); }
      | TOK_BIT_NOT UNARY     { $$ = new BitNotOperator($2); }
      | TOK_INCR UNARY        {$$ = new IncrBeforeOperator($2);}
      | TOK_DECR UNARY        {$$ = new DecrBeforeOperator($2);}
      | UNARY TOK_INCR        {$$ = new IncrAfterOperator($1);}
      | UNARY TOK_DECR        {$$ = new DecrAfterOperator($1);}
      ;

FACTOR : TOK_N     { $$ = new Number( $1 ); }
       | TOK_VAR  { $$ = new Variable(*$1);}
       | TOK_LBRACKET ASSIGN_EXPR TOK_RBRACKET { $$ = $2; }
       | TOK_VAR TOK_LBRACKET TOK_RBRACKET {$$ = new FuncCall(*$1);}
       | TOK_VAR TOK_LBRACKET FUNC_CALL_ARGS TOK_RBRACKET {$$ = new FuncCall(*$1, $3);}
       | TOK_VAR TOK_LSQBRACKET ASSIGN_EXPR TOK_RSQBRACKET {$$ = new ArrayCall(*$1, $3);}
       ;

REC_STATEMENT : STATEMENT {$$ = $1;}
              | REC_STATEMENT STATEMENT {$$ = new RecExpr($1, $2);}
              ;

STATEMENT : EXPR_STATEMENT {$$=$1;}
          | ITER_STATEMENT {$$=$1;}
          | JUMP_STATEMENT {$$=$1;}
          | SELECT_STATEMENT {$$=$1;}
          | FUNC_STATEMENT {$$=$1;}
          | SWITCH_STATEMENT {$$=$1;}
          ;

SWITCH_STATEMENT : TOK_CASE COND_EXPR TOK_COLON STATEMENT {$$ = new CaseStatement($2, $4);}
                 | TOK_DEFAULT TOK_COLON STATEMENT {$$ = new DefaultStatement($3);}
                 ;

EXPR_STATEMENT : ASSIGN_EXPR TOK_SEMICOLON {$$=$1;} //TOK_SEMICOLON 
              // | ASSIGN_EXPR TOK_SEMICOLON {$$=$1;}
               ;

FUNC_STATEMENT : TOK_LCBRACKET TOK_RCBRACKET {$$ = new EmptyStatement();}
                   | TOK_LCBRACKET REC_STATEMENT TOK_RCBRACKET {$$ = $2;}
                   | TOK_LCBRACKET REC_DECLARATION TOK_RCBRACKET {$$ = $2;}
                   | TOK_LCBRACKET REC_DECLARATION REC_STATEMENT TOK_RCBRACKET {$$ = new RecExpr($2, $3);}
                   ;

SELECT_STATEMENT : TOK_IF TOK_LBRACKET LOGIC_EXPR TOK_RBRACKET STATEMENT   {$$ = new IfStatement($3, $5);} 
                 | TOK_IF TOK_LBRACKET LOGIC_EXPR TOK_RBRACKET STATEMENT TOK_ELSE STATEMENT {$$ = new IfElseStatement($3, $5, $7);} 
                 | TOK_SWITCH TOK_LBRACKET LOGIC_EXPR TOK_RBRACKET STATEMENT {$$ = new SwitchStatement($3, $5);}
                 ;

ITER_STATEMENT : TOK_WHILE TOK_LBRACKET ASSIGN_EXPR TOK_RBRACKET STATEMENT {$$ = new WhileStatement($3, $5);} 
               | TOK_FOR TOK_LBRACKET EXPR_STATEMENT EXPR_STATEMENT ASSIGN_EXPR TOK_RBRACKET STATEMENT {$$ = new ForStatement($3, $4, $5, $7);}
               ;

JUMP_STATEMENT : TOK_BREAK TOK_SEMICOLON {$$ = new BreakStatement();}
               | TOK_CONT TOK_SEMICOLON {$$ = new ContinueStatement();}
               | TOK_RETURN TOK_SEMICOLON {$$ = new ReturnStatement();}
               | TOK_RETURN FUNCTION TOK_SEMICOLON {$$ = new ReturnExprStatement($2);}
               | TOK_RETURN LOGIC_EXPR TOK_SEMICOLON {$$ = new ReturnExprStatement($2);}
               ;
%%

const Expression *g_root;

const Expression *parseAST(std::string file)
{
  yyin = fopen(file.c_str(), "r"); 
  g_root=0;
  yyparse();
  return g_root;
}
