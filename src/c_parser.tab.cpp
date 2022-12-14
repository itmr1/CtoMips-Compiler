/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1





# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 125 "src/c_parser.tab.cpp"

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
    TOK_FOR = 276,
    TOK_SWITCH = 277,
    TOK_CASE = 278,
    TOK_DEFAULT = 279,
    TOK_RETURN = 280,
    TOK_BREAK = 281,
    TOK_CONT = 282,
    TOK_MUL = 283,
    TOK_DIVIDE = 284,
    TOK_PLUS = 285,
    TOK_MINUS = 286,
    TOK_MOD = 287,
    TOK_LBRACKET = 288,
    TOK_RBRACKET = 289,
    TOK_SEMICOLON = 290,
    TOK_LCBRACKET = 291,
    TOK_RCBRACKET = 292,
    TOK_LSQBRACKET = 293,
    TOK_RSQBRACKET = 294,
    TOK_COMMA = 295,
    TOK_QMARK = 296,
    TOK_COLON = 297,
    TOK_N = 298,
    TOK_VAR = 299,
    VARTYPE_INT = 300,
    TOK_SUBASSIGN = 301,
    TOK_MULASSIGN = 302,
    TOK_DIVASSIGN = 303,
    TOK_ADDASSIGN = 304,
    TOK_EQASSIGN = 305,
    TOK_MODASSIGN = 306,
    TOK_ANDASSIGN = 307,
    TOK_ORASSIGN = 308,
    TOK_XORASSIGN = 309,
    TOK_INCR = 310,
    TOK_DECR = 311
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

#line 199 "src/c_parser.tab.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_C_PARSER_TAB_HPP_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   525

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  109
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  220

#define YYUNDEFTOK  2
#define YYMAXUTOK   311


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    42,    42,    46,    47,    50,    51,    54,    55,    56,
      57,    63,    64,    67,    68,    69,    70,    71,    72,    74,
      75,    78,    80,    81,    84,    85,    88,    94,    95,    97,
      98,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   112,   113,   116,   117,   118,   121,   122,   123,   124,
     127,   128,   129,   132,   133,   134,   135,   136,   139,   140,
     141,   143,   144,   145,   148,   149,   150,   151,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   166,   167,
     168,   169,   170,   171,   176,   177,   180,   181,   184,   185,
     186,   187,   188,   193,   194,   197,   201,   202,   203,   204,
     207,   208,   209,   212,   213,   216,   217,   218,   219,   220
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_BIT_AND", "TOK_BIT_OR", "TOK_EQ",
  "TOK_NEQ", "TOK_BIT_XOR", "TOK_LOGIC_AND", "TOK_LOGIC_OR", "TOK_LSHIFT",
  "TOK_RSHIFT", "TOK_LOGIC_NOT", "TOK_BIT_NOT", "TOK_GE", "TOK_LE",
  "TOK_G", "TOK_L", "TOK_IF", "TOK_WHILE", "TOK_ELSE", "TOK_FOR",
  "TOK_SWITCH", "TOK_CASE", "TOK_DEFAULT", "TOK_RETURN", "TOK_BREAK",
  "TOK_CONT", "TOK_MUL", "TOK_DIVIDE", "TOK_PLUS", "TOK_MINUS", "TOK_MOD",
  "TOK_LBRACKET", "TOK_RBRACKET", "TOK_SEMICOLON", "TOK_LCBRACKET",
  "TOK_RCBRACKET", "TOK_LSQBRACKET", "TOK_RSQBRACKET", "TOK_COMMA",
  "TOK_QMARK", "TOK_COLON", "TOK_N", "TOK_VAR", "VARTYPE_INT",
  "TOK_SUBASSIGN", "TOK_MULASSIGN", "TOK_DIVASSIGN", "TOK_ADDASSIGN",
  "TOK_EQASSIGN", "TOK_MODASSIGN", "TOK_ANDASSIGN", "TOK_ORASSIGN",
  "TOK_XORASSIGN", "TOK_INCR", "TOK_DECR", "$accept", "ROOT", "EXPR_TREE",
  "EXPR_SINGLE", "FUNCTION", "REC_DECLARATION", "DECLARATION",
  "SINGLE_DECL", "VARTYPE_INTSTAR", "FUNC_ARGS", "FUNC_CALL_ARGS",
  "DECLARATOR", "ARRAY_DECLARATOR", "ARG_SINGLE", "ASSIGN_EXPR",
  "COND_EXPR", "LOGIC_EXPR", "BIT_EXPR", "EQ_EXPR", "REL_EXPR",
  "SHIFT_EXPR", "ADD_EXPR", "MULT_EXPR", "UNARY", "FACTOR", "REC_CASE",
  "REC_STATEMENT", "STATEMENT", "SWITCH_STATEMENT", "EXPR_STATEMENT",
  "FUNC_STATEMENT", "SELECT_STATEMENT", "ITER_STATEMENT", "JUMP_STATEMENT", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311
};
# endif

#define YYPACT_NINF (-167)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -20,   -13,    83,   -20,  -167,  -167,  -167,     0,  -167,    49,
      47,    38,  -167,  -167,  -167,    48,   421,   347,  -167,   458,
    -167,    67,   458,   458,   458,   458,   458,   458,   458,  -167,
    -167,    52,   458,   458,    33,    92,    23,   109,   121,    45,
      72,    85,  -167,   113,    -9,  -167,     0,    -4,  -167,  -167,
    -167,     5,   469,    99,   376,   107,    85,    85,    85,    85,
      85,    73,   384,   458,    85,    85,   458,   458,  -167,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,  -167,  -167,  -167,   174,  -167,
    -167,  -167,   115,   450,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,  -167,   123,    65,  -167,  -167,  -167,
    -167,    -1,    81,    92,    92,    23,    23,    23,   109,   109,
     121,   121,   121,   121,    45,    45,    72,    72,    85,    85,
      85,   135,   139,   140,   141,   413,   143,   144,  -167,   -13,
     213,  -167,   146,   252,  -167,  -167,  -167,  -167,  -167,  -167,
    -167,  -167,  -167,   114,  -167,  -167,  -167,  -167,  -167,  -167,
    -167,  -167,  -167,  -167,   147,   450,  -167,  -167,   458,   458,
     458,   458,  -167,     0,   148,    12,  -167,  -167,    44,  -167,
    -167,   291,  -167,  -167,  -167,   458,  -167,  -167,    18,   142,
     458,    40,   152,  -167,  -167,  -167,  -167,   330,   330,   458,
     153,   155,  -167,   154,   138,   330,   330,   458,   156,    69,
    -167,  -167,  -167,   161,   330,  -167,  -167,   330,   330,   330
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     3,     5,     6,     0,    21,    26,
       0,     0,     1,     4,    26,     0,     0,     0,    13,     0,
      14,     0,     0,     0,     0,     0,     0,     0,     0,    28,
      78,    79,     0,     0,     0,    43,    46,    50,    53,    58,
      61,    64,    68,     0,     0,    29,     0,     0,    22,    30,
      31,    41,    64,     0,     0,     0,    76,    70,    71,    77,
      69,     0,     0,     0,    72,    73,     0,     0,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    74,    75,    10,     0,     8,
      19,    20,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    16,     0,     0,    24,    15,    80,
      81,     0,     0,    44,    45,    47,    48,    49,    51,    52,
      55,    54,    56,    57,    59,    60,    62,    63,    65,    66,
      67,     0,     0,     0,     0,     0,     0,     0,    96,     0,
       0,    11,     0,     0,    86,    88,    92,    91,    89,    90,
       9,     7,    23,     0,    34,    35,    36,    33,    32,    37,
      38,    39,    40,    17,     0,     0,    82,    83,     0,     0,
       0,     0,   107,     0,     0,     0,   105,   106,     0,    98,
      12,     0,    95,    97,    87,     0,    18,    25,     0,     0,
       0,     0,     0,   108,   109,    99,    42,     0,     0,     0,
       0,   100,   103,     0,     0,     0,     0,     0,     0,     0,
      84,   101,   104,     0,     0,   102,    85,     0,    94,    93
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -167,  -167,  -167,   187,    59,  -167,   -70,  -167,     3,  -167,
     150,    -6,  -167,   -12,    15,  -162,   -14,    78,    66,    91,
      53,    87,    90,   -16,  -167,  -167,  -128,   -59,    -5,  -166,
     -21,  -167,  -167,  -167
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,   140,     6,    45,    46,    47,
     106,    10,    11,   107,   142,    50,    51,    35,    36,    37,
      38,    39,    40,    52,    42,   209,   143,   144,   210,   145,
     146,   147,   148,   149
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      41,    15,    34,     7,   190,    48,     7,    56,    57,    58,
      59,    60,   181,    66,    67,     8,    64,    65,   141,     8,
      66,    67,    89,   196,   199,     1,    66,    67,    72,    73,
      92,     9,    49,   166,    53,    14,    93,    55,    90,   165,
      91,    66,    67,    61,    14,   213,    94,   194,    66,    67,
      41,    41,   197,    41,    41,    41,    41,    41,    41,    41,
      41,    41,    41,    41,    41,    41,   128,   129,   130,    49,
     180,   151,    68,    20,   200,    80,    81,    49,   112,    18,
      17,   152,    18,    12,   184,    62,   218,    16,    21,   219,
      63,     7,   207,   208,    19,    69,    70,    19,    22,    71,
      82,    83,   164,    54,    84,   165,   215,   109,    49,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,    41,
     167,   175,   184,    74,    75,    76,    77,   120,   121,   122,
     123,    78,    79,   178,   104,   115,   116,   117,   201,   202,
      85,    86,   108,     7,   113,   114,   211,   212,    87,    88,
     150,    88,    41,   187,   188,    41,   185,   191,   163,   184,
     184,   207,   208,   118,   119,   124,   125,   192,   168,    41,
     126,   127,   169,   170,   171,   205,   198,    23,   176,   177,
      49,   182,   186,   193,   189,    17,    24,    25,   206,   204,
      13,    41,   131,   132,   174,   133,   134,     0,   214,   135,
     136,   137,    26,   217,   216,    27,     0,    28,     0,     0,
      88,   138,   111,     0,   203,     0,    23,    30,    31,   139,
       0,     0,     0,     0,     0,    24,    25,     0,     0,    32,
      33,   131,   132,     0,   133,   134,     0,     0,   135,   136,
     137,    26,     0,     0,    27,     0,    28,     0,     0,    88,
     179,     0,     0,     0,     0,    23,    30,    31,   139,     0,
       0,     0,     0,     0,    24,    25,     0,     0,    32,    33,
     131,   132,     0,   133,   134,     0,     0,   135,   136,   137,
      26,     0,     0,    27,     0,    28,     0,     0,    88,   183,
       0,     0,     0,     0,    23,    30,    31,     0,     0,     0,
       0,     0,     0,    24,    25,     0,     0,    32,    33,   131,
     132,     0,   133,   134,     0,     0,   135,   136,   137,    26,
       0,     0,    27,     0,    28,     0,     0,    88,   195,     0,
       0,     0,     0,    23,    30,    31,     0,     0,     0,     0,
       0,     0,    24,    25,     0,     0,    32,    33,   131,   132,
      23,   133,   134,     0,     0,   135,   136,   137,    26,    24,
      25,    27,     0,    28,     0,     0,    88,     0,     0,     0,
       0,     0,     0,    30,    31,    26,     0,     0,    27,    23,
      28,    43,     0,     0,     0,    32,    33,    23,    24,    25,
      30,    31,    44,     0,     0,     0,    24,    25,     0,     0,
       0,     0,    32,    33,    26,     0,     0,    27,     0,    28,
       0,     0,    26,   105,     0,    27,    23,    28,   110,    30,
      31,    44,     0,     0,    23,    24,    25,    30,    31,    44,
       0,    32,    33,    24,    25,     0,     0,     0,     0,    32,
      33,    26,     0,     0,    27,     0,    28,     0,   172,    26,
       0,     0,    27,    23,    28,     0,    30,    31,   173,     0,
      29,    23,    24,    25,    30,    31,     0,     0,    32,    33,
      24,    25,     0,     0,     0,     0,    32,    33,    26,     0,
       0,    27,     0,    28,     0,     0,    26,     0,     0,    27,
       0,    28,     0,    30,    31,    44,     0,     0,     0,     0,
       0,    30,    31,     0,     0,    32,    33,     0,     0,     0,
       0,     0,     0,    32,    33,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    85,    86
};

static const yytype_int16 yycheck[] =
{
      16,     7,    16,     0,   170,    17,     3,    23,    24,    25,
      26,    27,   140,     8,     9,    28,    32,    33,    88,    28,
       8,     9,    43,   185,   190,    45,     8,     9,     5,     6,
      34,    44,    17,    34,    19,    44,    40,    22,    44,    40,
      46,     8,     9,    28,    44,   207,    41,    35,     8,     9,
      66,    67,    34,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    54,
     140,    92,    39,    35,    34,    30,    31,    62,    63,    35,
      33,    93,    35,     0,   143,    33,   214,    38,    50,   217,
      38,    88,    23,    24,    50,     3,     4,    50,    50,     7,
      28,    29,    37,    36,    32,    40,    37,    34,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   135,
      39,   135,   181,    14,    15,    16,    17,    74,    75,    76,
      77,    10,    11,   139,    35,    69,    70,    71,   197,   198,
      55,    56,    35,   140,    66,    67,   205,   206,    35,    36,
      35,    36,   168,   165,   168,   171,    42,   171,    35,   218,
     219,    23,    24,    72,    73,    78,    79,   173,    33,   185,
      80,    81,    33,    33,    33,    20,    34,     3,    35,    35,
     165,    35,    35,    35,   169,    33,    12,    13,    34,    36,
       3,   207,    18,    19,   135,    21,    22,    -1,    42,    25,
      26,    27,    28,    42,   209,    31,    -1,    33,    -1,    -1,
      36,    37,    62,    -1,   199,    -1,     3,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    12,    13,    -1,    -1,    55,
      56,    18,    19,    -1,    21,    22,    -1,    -1,    25,    26,
      27,    28,    -1,    -1,    31,    -1,    33,    -1,    -1,    36,
      37,    -1,    -1,    -1,    -1,     3,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    12,    13,    -1,    -1,    55,    56,
      18,    19,    -1,    21,    22,    -1,    -1,    25,    26,    27,
      28,    -1,    -1,    31,    -1,    33,    -1,    -1,    36,    37,
      -1,    -1,    -1,    -1,     3,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    12,    13,    -1,    -1,    55,    56,    18,
      19,    -1,    21,    22,    -1,    -1,    25,    26,    27,    28,
      -1,    -1,    31,    -1,    33,    -1,    -1,    36,    37,    -1,
      -1,    -1,    -1,     3,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    13,    -1,    -1,    55,    56,    18,    19,
       3,    21,    22,    -1,    -1,    25,    26,    27,    28,    12,
      13,    31,    -1,    33,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    28,    -1,    -1,    31,     3,
      33,    34,    -1,    -1,    -1,    55,    56,     3,    12,    13,
      43,    44,    45,    -1,    -1,    -1,    12,    13,    -1,    -1,
      -1,    -1,    55,    56,    28,    -1,    -1,    31,    -1,    33,
      -1,    -1,    28,    37,    -1,    31,     3,    33,    34,    43,
      44,    45,    -1,    -1,     3,    12,    13,    43,    44,    45,
      -1,    55,    56,    12,    13,    -1,    -1,    -1,    -1,    55,
      56,    28,    -1,    -1,    31,    -1,    33,    -1,    35,    28,
      -1,    -1,    31,     3,    33,    -1,    43,    44,    45,    -1,
      39,     3,    12,    13,    43,    44,    -1,    -1,    55,    56,
      12,    13,    -1,    -1,    -1,    -1,    55,    56,    28,    -1,
      -1,    31,    -1,    33,    -1,    -1,    28,    -1,    -1,    31,
      -1,    33,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    43,    44,    -1,    -1,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    56,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    45,    58,    59,    60,    61,    63,    65,    28,    44,
      68,    69,     0,    60,    44,    68,    38,    33,    35,    50,
      35,    50,    50,     3,    12,    13,    28,    31,    33,    39,
      43,    44,    55,    56,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    34,    45,    64,    65,    66,    70,    71,
      72,    73,    80,    71,    36,    71,    80,    80,    80,    80,
      80,    71,    33,    38,    80,    80,     8,     9,    39,     3,
       4,     7,     5,     6,    14,    15,    16,    17,    10,    11,
      30,    31,    28,    29,    32,    55,    56,    35,    36,    87,
      68,    68,    34,    40,    41,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    35,    37,    67,    70,    35,    34,
      34,    67,    71,    74,    74,    75,    75,    75,    76,    76,
      77,    77,    77,    77,    78,    78,    79,    79,    80,    80,
      80,    18,    19,    21,    22,    25,    26,    27,    37,    45,
      62,    63,    71,    83,    84,    86,    87,    88,    89,    90,
      35,    87,    70,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    35,    37,    40,    34,    39,    33,    33,
      33,    33,    35,    45,    61,    73,    35,    35,    68,    37,
      63,    83,    35,    37,    84,    42,    35,    70,    73,    71,
      86,    73,    68,    35,    35,    37,    72,    34,    34,    86,
      34,    84,    84,    71,    36,    20,    34,    23,    24,    82,
      85,    84,    84,    72,    42,    37,    85,    42,    83,    83
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    57,    58,    59,    59,    60,    60,    61,    61,    61,
      61,    62,    62,    63,    63,    63,    63,    63,    63,    64,
      64,    65,    66,    66,    67,    67,    68,    69,    69,    70,
      70,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    72,    72,    73,    73,    73,    74,    74,    74,    74,
      75,    75,    75,    76,    76,    76,    76,    76,    77,    77,
      77,    78,    78,    78,    79,    79,    79,    79,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    81,    81,
      81,    81,    81,    81,    82,    82,    83,    83,    84,    84,
      84,    84,    84,    85,    85,    86,    87,    87,    87,    87,
      88,    88,    88,    89,    89,    90,    90,    90,    90,    90
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     6,     5,     6,
       5,     1,     2,     3,     3,     5,     5,     6,     7,     2,
       2,     2,     1,     3,     1,     3,     1,     4,     3,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     5,     1,     3,     3,     1,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     1,     1,
       3,     3,     4,     4,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     4,     3,     2,     2,     3,     3,     4,
       5,     7,     7,     5,     7,     2,     2,     2,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 42 "src/c_parser.y"
                        { g_root = (yyvsp[0].expr); }
#line 1592 "src/c_parser.tab.cpp"
    break;

  case 3:
#line 46 "src/c_parser.y"
                        {(yyval.expr) = (yyvsp[0].expr);}
#line 1598 "src/c_parser.tab.cpp"
    break;

  case 4:
#line 47 "src/c_parser.y"
                                    { (yyval.expr) = new RecExpr((yyvsp[-1].expr),(yyvsp[0].expr));}
#line 1604 "src/c_parser.tab.cpp"
    break;

  case 5:
#line 50 "src/c_parser.y"
                        { (yyval.expr) = (yyvsp[0].expr); }
#line 1610 "src/c_parser.tab.cpp"
    break;

  case 6:
#line 51 "src/c_parser.y"
                    {(yyval.expr)= (yyvsp[0].expr); }
#line 1616 "src/c_parser.tab.cpp"
    break;

  case 7:
#line 54 "src/c_parser.y"
                                                                                     {(yyval.expr) = new FuncWithArgs("int",(yyvsp[-4].expr),(yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1622 "src/c_parser.tab.cpp"
    break;

  case 8:
#line 55 "src/c_parser.y"
                                                                           {(yyval.expr) = new FuncNoArgs("int", (yyvsp[-3].expr),(yyvsp[0].expr));}
#line 1628 "src/c_parser.tab.cpp"
    break;

  case 9:
#line 56 "src/c_parser.y"
                                                                                    {(yyval.expr) = new FuncInstance("int", (yyvsp[-4].expr), (yyvsp[-2].expr));}
#line 1634 "src/c_parser.tab.cpp"
    break;

  case 10:
#line 57 "src/c_parser.y"
                                                                          {(yyval.expr) = new FuncInstance("int", (yyvsp[-3].expr));}
#line 1640 "src/c_parser.tab.cpp"
    break;

  case 11:
#line 63 "src/c_parser.y"
                              {(yyval.expr)=(yyvsp[0].expr);}
#line 1646 "src/c_parser.tab.cpp"
    break;

  case 12:
#line 64 "src/c_parser.y"
                                              {(yyval.expr)= new RecExpr((yyvsp[-1].expr), (yyvsp[0].expr));}
#line 1652 "src/c_parser.tab.cpp"
    break;

  case 13:
#line 67 "src/c_parser.y"
                                                   { (yyval.expr) = new DeclareVar("int", (yyvsp[-1].expr)); }
#line 1658 "src/c_parser.tab.cpp"
    break;

  case 14:
#line 68 "src/c_parser.y"
                                                      { (yyval.expr) = new DeclareArray("int", (yyvsp[-1].expr));}
#line 1664 "src/c_parser.tab.cpp"
    break;

  case 15:
#line 69 "src/c_parser.y"
                                                                             {(yyval.expr) = new InitMemory("int*", (yyvsp[-3].expr), (yyvsp[-1].expr));}
#line 1670 "src/c_parser.tab.cpp"
    break;

  case 16:
#line 70 "src/c_parser.y"
                                                                         {(yyval.expr)= new InitVar("int",(yyvsp[-3].expr),(yyvsp[-1].expr));}
#line 1676 "src/c_parser.tab.cpp"
    break;

  case 17:
#line 71 "src/c_parser.y"
                                                                                               {(yyval.expr) = new InitZeroArray("int",(yyvsp[-4].expr));}
#line 1682 "src/c_parser.tab.cpp"
    break;

  case 18:
#line 72 "src/c_parser.y"
                                                                                                              {(yyval.expr) = new InitArray("int",(yyvsp[-5].expr),(yyvsp[-2].expr));}
#line 1688 "src/c_parser.tab.cpp"
    break;

  case 19:
#line 74 "src/c_parser.y"
                                     { (yyval.expr) = new DeclareVar("int", (yyvsp[0].expr)); }
#line 1694 "src/c_parser.tab.cpp"
    break;

  case 20:
#line 75 "src/c_parser.y"
                                         {(yyval.expr) = new DeclareMemory("int*", (yyvsp[0].expr));}
#line 1700 "src/c_parser.tab.cpp"
    break;

  case 22:
#line 80 "src/c_parser.y"
                      { (yyval.expr) = (yyvsp[0].expr); }
#line 1706 "src/c_parser.tab.cpp"
    break;

  case 23:
#line 81 "src/c_parser.y"
                                          {(yyval.expr) = new RecExpr((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1712 "src/c_parser.tab.cpp"
    break;

  case 24:
#line 84 "src/c_parser.y"
                           {(yyval.expr)=(yyvsp[0].expr);}
#line 1718 "src/c_parser.tab.cpp"
    break;

  case 25:
#line 85 "src/c_parser.y"
                                                    {(yyval.expr) = new RecExpr((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1724 "src/c_parser.tab.cpp"
    break;

  case 26:
#line 88 "src/c_parser.y"
                     { (yyval.expr) = new Variable(*(yyvsp[0].string));}
#line 1730 "src/c_parser.tab.cpp"
    break;

  case 27:
#line 94 "src/c_parser.y"
                                                                    {(yyval.expr) = new Array(*(yyvsp[-3].string), (yyvsp[-1].expr));}
#line 1736 "src/c_parser.tab.cpp"
    break;

  case 28:
#line 95 "src/c_parser.y"
                                                   {(yyval.expr) = new Array(*(yyvsp[-2].string));}
#line 1742 "src/c_parser.tab.cpp"
    break;

  case 29:
#line 97 "src/c_parser.y"
                        {(yyval.expr) = new SingleExpr((yyvsp[0].expr));}
#line 1748 "src/c_parser.tab.cpp"
    break;

  case 30:
#line 98 "src/c_parser.y"
                        {(yyval.expr) =new SingleExpr((yyvsp[0].expr));}
#line 1754 "src/c_parser.tab.cpp"
    break;

  case 31:
#line 100 "src/c_parser.y"
                        {(yyval.expr) = (yyvsp[0].expr);}
#line 1760 "src/c_parser.tab.cpp"
    break;

  case 32:
#line 101 "src/c_parser.y"
                                             {(yyval.expr) = new AssignOperator((yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1766 "src/c_parser.tab.cpp"
    break;

  case 33:
#line 102 "src/c_parser.y"
                                              {(yyval.expr) = new AddAssignOperator((yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1772 "src/c_parser.tab.cpp"
    break;

  case 34:
#line 103 "src/c_parser.y"
                                              {(yyval.expr) = new SubAssignOperator((yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1778 "src/c_parser.tab.cpp"
    break;

  case 35:
#line 104 "src/c_parser.y"
                                              {(yyval.expr) = new MulAssignOperator((yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1784 "src/c_parser.tab.cpp"
    break;

  case 36:
#line 105 "src/c_parser.y"
                                              {(yyval.expr) = new DivAssignOperator((yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1790 "src/c_parser.tab.cpp"
    break;

  case 37:
#line 106 "src/c_parser.y"
                                              {(yyval.expr) = new ModAssignOperator((yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1796 "src/c_parser.tab.cpp"
    break;

  case 38:
#line 107 "src/c_parser.y"
                                              {(yyval.expr) = new AndAssignOperator((yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1802 "src/c_parser.tab.cpp"
    break;

  case 39:
#line 108 "src/c_parser.y"
                                             {(yyval.expr) = new OrAssignOperator((yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1808 "src/c_parser.tab.cpp"
    break;

  case 40:
#line 109 "src/c_parser.y"
                                              {(yyval.expr) = new XorAssignOperator((yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1814 "src/c_parser.tab.cpp"
    break;

  case 41:
#line 112 "src/c_parser.y"
                       {(yyval.expr)=(yyvsp[0].expr);}
#line 1820 "src/c_parser.tab.cpp"
    break;

  case 42:
#line 113 "src/c_parser.y"
                                                                 {(yyval.expr) = new MuxOperator((yyvsp[-4].expr),(yyvsp[-2].expr),(yyvsp[0].expr));}
#line 1826 "src/c_parser.tab.cpp"
    break;

  case 43:
#line 116 "src/c_parser.y"
                      {(yyval.expr) = (yyvsp[0].expr);}
#line 1832 "src/c_parser.tab.cpp"
    break;

  case 44:
#line 117 "src/c_parser.y"
                                                {(yyval.expr) = new LogicalAndOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1838 "src/c_parser.tab.cpp"
    break;

  case 45:
#line 118 "src/c_parser.y"
                                               {(yyval.expr) = new LogicalOrOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1844 "src/c_parser.tab.cpp"
    break;

  case 46:
#line 121 "src/c_parser.y"
                   {(yyval.expr) = (yyvsp[0].expr);}
#line 1850 "src/c_parser.tab.cpp"
    break;

  case 47:
#line 122 "src/c_parser.y"
                                          {(yyval.expr) = new BitwiseAndOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1856 "src/c_parser.tab.cpp"
    break;

  case 48:
#line 123 "src/c_parser.y"
                                         {(yyval.expr) = new BitwiseOrOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1862 "src/c_parser.tab.cpp"
    break;

  case 49:
#line 124 "src/c_parser.y"
                                          {(yyval.expr) = new BitwiseXorOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1868 "src/c_parser.tab.cpp"
    break;

  case 50:
#line 127 "src/c_parser.y"
                   {(yyval.expr)=(yyvsp[0].expr);}
#line 1874 "src/c_parser.tab.cpp"
    break;

  case 51:
#line 128 "src/c_parser.y"
                                   {(yyval.expr) = new EqOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1880 "src/c_parser.tab.cpp"
    break;

  case 52:
#line 129 "src/c_parser.y"
                                   {(yyval.expr) = new NeqOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1886 "src/c_parser.tab.cpp"
    break;

  case 53:
#line 132 "src/c_parser.y"
                     {(yyval.expr) = (yyvsp[0].expr);}
#line 1892 "src/c_parser.tab.cpp"
    break;

  case 54:
#line 133 "src/c_parser.y"
                                     {(yyval.expr) = new LessThanEqualOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1898 "src/c_parser.tab.cpp"
    break;

  case 55:
#line 134 "src/c_parser.y"
                                     {(yyval.expr) = new GreaterThanEqualOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1904 "src/c_parser.tab.cpp"
    break;

  case 56:
#line 135 "src/c_parser.y"
                                    {(yyval.expr) = new GreaterThanOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1910 "src/c_parser.tab.cpp"
    break;

  case 57:
#line 136 "src/c_parser.y"
                                    {(yyval.expr) = new LessThanOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1916 "src/c_parser.tab.cpp"
    break;

  case 58:
#line 139 "src/c_parser.y"
                     {(yyval.expr) = (yyvsp[0].expr);}
#line 1922 "src/c_parser.tab.cpp"
    break;

  case 59:
#line 140 "src/c_parser.y"
                                           {(yyval.expr) = new LeftShiftOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1928 "src/c_parser.tab.cpp"
    break;

  case 60:
#line 141 "src/c_parser.y"
                                           {(yyval.expr) = new RightShiftOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1934 "src/c_parser.tab.cpp"
    break;

  case 61:
#line 143 "src/c_parser.y"
                     {(yyval.expr) = (yyvsp[0].expr);}
#line 1940 "src/c_parser.tab.cpp"
    break;

  case 62:
#line 144 "src/c_parser.y"
                                       {(yyval.expr) = new AddOperator((yyvsp[-2].expr), (yyvsp[0].expr)) ; }
#line 1946 "src/c_parser.tab.cpp"
    break;

  case 63:
#line 145 "src/c_parser.y"
                                         {(yyval.expr) = new SubOperator((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1952 "src/c_parser.tab.cpp"
    break;

  case 64:
#line 148 "src/c_parser.y"
                  {(yyval.expr) = (yyvsp[0].expr);}
#line 1958 "src/c_parser.tab.cpp"
    break;

  case 65:
#line 149 "src/c_parser.y"
                                    {(yyval.expr) = new MulOperator((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1964 "src/c_parser.tab.cpp"
    break;

  case 66:
#line 150 "src/c_parser.y"
                                       { (yyval.expr) = new DivOperator((yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1970 "src/c_parser.tab.cpp"
    break;

  case 67:
#line 151 "src/c_parser.y"
                                    {(yyval.expr) = new ModOperator((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1976 "src/c_parser.tab.cpp"
    break;

  case 68:
#line 154 "src/c_parser.y"
                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1982 "src/c_parser.tab.cpp"
    break;

  case 69:
#line 155 "src/c_parser.y"
                          { (yyval.expr) = new NegOperator((yyvsp[0].expr));}
#line 1988 "src/c_parser.tab.cpp"
    break;

  case 70:
#line 156 "src/c_parser.y"
                              { (yyval.expr) = new LogicalNotOperator((yyvsp[0].expr)); }
#line 1994 "src/c_parser.tab.cpp"
    break;

  case 71:
#line 157 "src/c_parser.y"
                              { (yyval.expr) = new BitNotOperator((yyvsp[0].expr)); }
#line 2000 "src/c_parser.tab.cpp"
    break;

  case 72:
#line 158 "src/c_parser.y"
                              {(yyval.expr) = new IncrBeforeOperator((yyvsp[0].expr));}
#line 2006 "src/c_parser.tab.cpp"
    break;

  case 73:
#line 159 "src/c_parser.y"
                              {(yyval.expr) = new DecrBeforeOperator((yyvsp[0].expr));}
#line 2012 "src/c_parser.tab.cpp"
    break;

  case 74:
#line 160 "src/c_parser.y"
                              {(yyval.expr) = new IncrAfterOperator((yyvsp[-1].expr));}
#line 2018 "src/c_parser.tab.cpp"
    break;

  case 75:
#line 161 "src/c_parser.y"
                              {(yyval.expr) = new DecrAfterOperator((yyvsp[-1].expr));}
#line 2024 "src/c_parser.tab.cpp"
    break;

  case 76:
#line 162 "src/c_parser.y"
                             {(yyval.expr) = new MemoryOperator((yyvsp[0].expr));}
#line 2030 "src/c_parser.tab.cpp"
    break;

  case 77:
#line 163 "src/c_parser.y"
                       {(yyval.expr) = new DereferenceOperator((yyvsp[0].expr));}
#line 2036 "src/c_parser.tab.cpp"
    break;

  case 78:
#line 166 "src/c_parser.y"
                   { (yyval.expr) = new Number( (yyvsp[0].number) ); }
#line 2042 "src/c_parser.tab.cpp"
    break;

  case 79:
#line 167 "src/c_parser.y"
                  { (yyval.expr) = new Variable(*(yyvsp[0].string));}
#line 2048 "src/c_parser.tab.cpp"
    break;

  case 80:
#line 168 "src/c_parser.y"
                                               { (yyval.expr) = (yyvsp[-1].expr); }
#line 2054 "src/c_parser.tab.cpp"
    break;

  case 81:
#line 169 "src/c_parser.y"
                                           {(yyval.expr) = new FuncCall(*(yyvsp[-2].string));}
#line 2060 "src/c_parser.tab.cpp"
    break;

  case 82:
#line 170 "src/c_parser.y"
                                                          {(yyval.expr) = new FuncCall(*(yyvsp[-3].string), (yyvsp[-1].expr));}
#line 2066 "src/c_parser.tab.cpp"
    break;

  case 83:
#line 171 "src/c_parser.y"
                                                           {(yyval.expr) = new ArrayCall(*(yyvsp[-3].string), (yyvsp[-1].expr));}
#line 2072 "src/c_parser.tab.cpp"
    break;

  case 84:
#line 176 "src/c_parser.y"
                            {(yyval.expr)=(yyvsp[0].expr);}
#line 2078 "src/c_parser.tab.cpp"
    break;

  case 85:
#line 177 "src/c_parser.y"
                                     {(yyval.expr)= new RecExpr((yyvsp[-1].expr), (yyvsp[0].expr));}
#line 2084 "src/c_parser.tab.cpp"
    break;

  case 86:
#line 180 "src/c_parser.y"
                          {(yyval.expr) = (yyvsp[0].expr);}
#line 2090 "src/c_parser.tab.cpp"
    break;

  case 87:
#line 181 "src/c_parser.y"
                                        {(yyval.expr) = new RecExpr((yyvsp[-1].expr), (yyvsp[0].expr));}
#line 2096 "src/c_parser.tab.cpp"
    break;

  case 88:
#line 184 "src/c_parser.y"
                           {(yyval.expr)=(yyvsp[0].expr);}
#line 2102 "src/c_parser.tab.cpp"
    break;

  case 89:
#line 185 "src/c_parser.y"
                           {(yyval.expr)=(yyvsp[0].expr);}
#line 2108 "src/c_parser.tab.cpp"
    break;

  case 90:
#line 186 "src/c_parser.y"
                           {(yyval.expr)=new SingleExpr((yyvsp[0].expr));}
#line 2114 "src/c_parser.tab.cpp"
    break;

  case 91:
#line 187 "src/c_parser.y"
                             {(yyval.expr)=(yyvsp[0].expr);}
#line 2120 "src/c_parser.tab.cpp"
    break;

  case 92:
#line 188 "src/c_parser.y"
                           {(yyval.expr)=(yyvsp[0].expr);}
#line 2126 "src/c_parser.tab.cpp"
    break;

  case 93:
#line 193 "src/c_parser.y"
                                                              {(yyval.expr) = new CaseStatement((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2132 "src/c_parser.tab.cpp"
    break;

  case 94:
#line 194 "src/c_parser.y"
                                                       {(yyval.expr) = new DefaultStatement((yyvsp[0].expr));}
#line 2138 "src/c_parser.tab.cpp"
    break;

  case 95:
#line 197 "src/c_parser.y"
                                           {(yyval.expr)= new SingleExpr((yyvsp[-1].expr));}
#line 2144 "src/c_parser.tab.cpp"
    break;

  case 96:
#line 201 "src/c_parser.y"
                                             {(yyval.expr) = new EmptyStatement();}
#line 2150 "src/c_parser.tab.cpp"
    break;

  case 97:
#line 202 "src/c_parser.y"
                                                               {(yyval.expr) = (yyvsp[-1].expr);}
#line 2156 "src/c_parser.tab.cpp"
    break;

  case 98:
#line 203 "src/c_parser.y"
                                                                 {(yyval.expr) = (yyvsp[-1].expr);}
#line 2162 "src/c_parser.tab.cpp"
    break;

  case 99:
#line 204 "src/c_parser.y"
                                                                               {(yyval.expr) = new RecExpr((yyvsp[-2].expr), (yyvsp[-1].expr));}
#line 2168 "src/c_parser.tab.cpp"
    break;

  case 100:
#line 207 "src/c_parser.y"
                                                                           {(yyval.expr) = new IfStatement((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2174 "src/c_parser.tab.cpp"
    break;

  case 101:
#line 208 "src/c_parser.y"
                                                                                            {(yyval.expr) = new IfElseStatement((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2180 "src/c_parser.tab.cpp"
    break;

  case 102:
#line 209 "src/c_parser.y"
                                                                                                        {(yyval.expr)= new SwitchStatement((yyvsp[-4].expr), (yyvsp[-1].expr));}
#line 2186 "src/c_parser.tab.cpp"
    break;

  case 103:
#line 212 "src/c_parser.y"
                                                                           {(yyval.expr) = new WhileStatement((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2192 "src/c_parser.tab.cpp"
    break;

  case 104:
#line 213 "src/c_parser.y"
                                                                                                       {(yyval.expr) = new ForStatement((yyvsp[-4].expr), (yyvsp[-3].expr), (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2198 "src/c_parser.tab.cpp"
    break;

  case 105:
#line 216 "src/c_parser.y"
                                         {(yyval.expr) = new BreakStatement();}
#line 2204 "src/c_parser.tab.cpp"
    break;

  case 106:
#line 217 "src/c_parser.y"
                                        {(yyval.expr) = new ContinueStatement();}
#line 2210 "src/c_parser.tab.cpp"
    break;

  case 107:
#line 218 "src/c_parser.y"
                                          {(yyval.expr) = new ReturnStatement();}
#line 2216 "src/c_parser.tab.cpp"
    break;

  case 108:
#line 219 "src/c_parser.y"
                                                   {(yyval.expr) = new ReturnExprStatement((yyvsp[-1].expr));}
#line 2222 "src/c_parser.tab.cpp"
    break;

  case 109:
#line 220 "src/c_parser.y"
                                                     {(yyval.expr) = new ReturnExprStatement((yyvsp[-1].expr));}
#line 2228 "src/c_parser.tab.cpp"
    break;


#line 2232 "src/c_parser.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 222 "src/c_parser.y"


const Expression *g_root;

const Expression *parseAST(std::string file)
{
  yyin = fopen(file.c_str(), "r"); 
  g_root=0;
  yyparse();
  return g_root;
}
