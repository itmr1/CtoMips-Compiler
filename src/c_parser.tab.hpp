/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_SRC_C_PARSER_TAB_HPP_INCLUDED
# define YY_YY_SRC_C_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/c_parser.y"

  #include "ast.hpp"

  #include <cassert>

  extern const Expression *g_root; // A way of getting the AST out
  extern FILE *yyin;
  // ! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);

#line 62 "src/c_parser.tab.hpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_BIT_AND = 258,
    TOK_BIT_OR = 259,
    TOK_EQ = 260,
    TOK_NEQ = 261,
    TOK_BIT_XOR = 262,
    TOK_LOGIC_AND = 263,
    TOK_LOGIC_OR = 264,
    TOK_LSHIFT = 265,
    TOK_RSHIFT = 266,
    TOK_LOGIC_NOT = 267,
    TOK_BIT_NOT = 268,
    TOK_GE = 269,
    TOK_LE = 270,
    TOK_G = 271,
    TOK_L = 272,
    TOK_IF = 273,
    TOK_WHILE = 274,
    TOK_ELSE = 275,
    TOK_RETURN = 276,
    TOK_BREAK = 277,
    TOK_CONT = 278,
    TOK_MUL = 279,
    TOK_DIVIDE = 280,
    TOK_PLUS = 281,
    TOK_MINUS = 282,
    TOK_MOD = 283,
    TOK_LBRACKET = 284,
    TOK_RBRACKET = 285,
    TOK_SEMICOLON = 286,
    TOK_LCBRACKET = 287,
    TOK_RCBRACKET = 288,
    TOK_LSQBRACKET = 289,
    TOK_RSQBRACKET = 290,
    TOK_COMMA = 291,
    TOK_N = 292,
    TOK_VAR = 293,
    VARTYPE_INT = 294,
    TOK_SUBASSIGN = 295,
    TOK_MULASSIGN = 296,
    TOK_DIVASSIGN = 297,
    TOK_ADDASSIGN = 298,
    TOK_EQASSIGN = 299,
    TOK_MODASSIGN = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "src/c_parser.y"

  const Expression *expr;
  double number;
  std::string *string;

#line 125 "src/c_parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_C_PARSER_TAB_HPP_INCLUDED  */
