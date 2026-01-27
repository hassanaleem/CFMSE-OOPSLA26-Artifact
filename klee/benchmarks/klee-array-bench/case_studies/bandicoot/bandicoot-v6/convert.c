/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         conv_parse
#define yylex           conv_lex
#define yyerror         conv_error
#define yydebug         conv_debug
#define yynerrs         conv_nerrs

#define yylval          conv_lval
#define yychar          conv_char

/* Copy the first part of user declarations.  */
#line 18 "convert.y" /* yacc.c:339  */

#include "config.h"
#include "string.h"
#include "system.h"
#include "memory.h"

extern void conv_error(const char *, ...);
extern int conv_lex();
extern char *cat(char *fmt, ...);

#line 85 "convert.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "convert.h".  */
#ifndef YY_CONV_CONVERT_H_INCLUDED
# define YY_CONV_CONVERT_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int conv_debug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_NAME = 258,
    TK_INT_VAL = 259,
    TK_LONG_VAL = 260,
    TK_REAL_VAL = 261,
    TK_STRING_VAL = 262,
    TK_REL = 263,
    TK_FN = 264,
    TK_RETURN = 265,
    TK_INT = 266,
    TK_LONG = 267,
    TK_REAL = 268,
    TK_STRING = 269,
    TK_PROJECT = 270,
    TK_RENAME = 271,
    TK_SELECT = 272,
    TK_EXTEND = 273,
    TK_SUMMARY = 274,
    TK_EQ = 275,
    TK_NEQ = 276,
    TK_AND = 277,
    TK_OR = 278,
    TK_LTE = 279,
    TK_GTE = 280
  };
#endif
/* Tokens.  */
#define TK_NAME 258
#define TK_INT_VAL 259
#define TK_LONG_VAL 260
#define TK_REAL_VAL 261
#define TK_STRING_VAL 262
#define TK_REL 263
#define TK_FN 264
#define TK_RETURN 265
#define TK_INT 266
#define TK_LONG 267
#define TK_REAL 268
#define TK_STRING 269
#define TK_PROJECT 270
#define TK_RENAME 271
#define TK_SELECT 272
#define TK_EXTEND 273
#define TK_SUMMARY 274
#define TK_EQ 275
#define TK_NEQ 276
#define TK_AND 277
#define TK_OR 278
#define TK_LTE 279
#define TK_GTE 280

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 29 "convert.y" /* yacc.c:355  */

    char *val;

#line 179 "convert.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE conv_lval;

int conv_parse (void);

#endif /* !YY_CONV_CONVERT_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 194 "convert.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   237

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  101
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  214

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   280

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,     2,     2,     2,     2,     2,
      34,    35,    28,    27,    40,    26,     2,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    38,    39,
      30,    42,    31,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    37,     2,    36,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    32,     2,    33,     2,     2,     2,     2,
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
      25
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    58,    58,    59,    60,    61,    65,    69,    70,    74,
      75,    79,    80,    84,    85,    86,    87,    91,    92,    96,
     101,   105,   106,   107,   111,   112,   113,   117,   118,   119,
     123,   124,   125,   126,   130,   134,   135,   139,   141,   143,
     145,   147,   152,   153,   157,   159,   161,   163,   165,   167,
     169,   174,   175,   179,   180,   181,   185,   186,   190,   194,
     195,   199,   203,   204,   208,   212,   213,   217,   221,   223,
     228,   229,   230,   231,   235,   237,   239,   241,   243,   245,
     250,   251,   255,   256,   257,   258,   262,   263,   264,   268,
     269,   270,   274,   276,   278,   280,   282,   284,   286,   291,
     293,   295
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_NAME", "TK_INT_VAL", "TK_LONG_VAL",
  "TK_REAL_VAL", "TK_STRING_VAL", "TK_REL", "TK_FN", "TK_RETURN", "TK_INT",
  "TK_LONG", "TK_REAL", "TK_STRING", "TK_PROJECT", "TK_RENAME",
  "TK_SELECT", "TK_EXTEND", "TK_SUMMARY", "TK_EQ", "TK_NEQ", "TK_AND",
  "TK_OR", "TK_LTE", "TK_GTE", "'-'", "'+'", "'*'", "'/'", "'<'", "'>'",
  "'{'", "'}'", "'('", "')'", "']'", "'['", "':'", "';'", "','", "'!'",
  "'='", "$accept", "program", "rel_decl", "rel_head", "rel_attrs",
  "rel_attrs_names", "rel_attr", "relvar_decl", "func_decl", "func_name",
  "func_res", "func_params", "func_param", "func_body", "stmt_return",
  "stmt_assigns", "stmt_assign", "rel_prim_expr", "rel_post_expr",
  "rel_mul_expr", "rel_expr", "project_attrs", "project_attr",
  "rename_attrs", "rename_attr", "extend_attrs", "extend_attr",
  "sum_attrs", "sum_attr", "sum_func", "prim_const_expr",
  "prim_simple_expr", "prim_top_expr", "prim_unary_expr", "prim_mul_expr",
  "prim_add_expr", "prim_bool_cmp_expr", "prim_expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,    45,    43,    42,    47,
      60,    62,   123,   125,    40,    41,    93,    91,    58,    59,
      44,    33,    61
};
# endif

#define YYPACT_NINF -126

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-126)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -126,   154,  -126,    19,    60,    63,  -126,  -126,  -126,    12,
      57,  -126,    76,    67,    57,   105,  -126,   105,  -126,    73,
    -126,     2,    37,  -126,    41,  -126,   -19,  -126,  -126,  -126,
       6,   172,   111,   133,    78,   105,  -126,  -126,  -126,  -126,
    -126,  -126,  -126,  -126,    57,    35,   108,  -126,  -126,  -126,
      57,    75,  -126,    46,    16,    95,  -126,    75,  -126,    90,
      92,   153,   155,    16,  -126,    16,  -126,   163,   168,    -9,
    -126,  -126,  -126,    16,    16,    16,    16,    25,    43,   103,
     164,   165,   166,   167,   169,    16,    16,    16,  -126,    68,
      70,    72,    74,  -126,    16,  -126,   199,   201,     0,   202,
     203,   163,   168,   168,  -126,  -126,  -126,  -126,    52,  -126,
     115,  -126,   170,   116,  -126,   173,  -126,  -126,  -126,  -126,
     174,   175,   176,    42,    42,     0,     0,  -126,  -126,  -126,
    -126,   114,   134,   128,    80,   171,   135,  -126,   177,   136,
    -126,   192,  -126,   199,   211,  -126,   201,     0,     0,     0,
       0,   173,  -126,  -126,    82,  -126,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -126,     0,
    -126,   202,   212,  -126,   203,   182,  -126,  -126,  -126,    96,
      98,   100,   102,  -126,  -126,  -126,   114,   114,   134,   134,
     134,   134,   134,   134,   128,   128,   151,  -126,   183,  -126,
    -126,   203,  -126,  -126,  -126,  -126,     5,   137,   178,  -126,
    -126,     0,   104,  -126
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     0,     1,     0,     0,     0,     2,     3,     4,     0,
       0,    20,     0,     0,     0,     0,     6,    26,    17,     0,
      11,     0,     0,     9,     0,    27,     0,    24,    18,     7,
       0,     0,     0,     0,    23,     0,     8,    10,    13,    14,
      15,    16,    12,    28,     0,     0,     0,    25,    29,    21,
       0,    33,    22,     0,     0,     0,    30,    31,    35,     0,
       0,     0,     0,     0,    42,     0,    44,    51,    53,     0,
      19,    32,    36,     0,     0,     0,     0,     0,    51,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,     0,
       0,     0,     0,    37,     0,    43,     0,     0,     0,     0,
       0,    52,    55,    54,    39,    38,    40,    41,     0,    58,
       0,    56,     0,     0,    59,    81,    70,    71,    72,    73,
       0,     0,     0,     0,     0,     0,     0,    74,    80,    82,
      86,    89,    92,    99,     0,     0,     0,    62,     0,     0,
      65,     0,    45,     0,     0,    46,     0,     0,     0,     0,
       0,     0,    84,    85,     0,    83,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    47,     0,
      48,     0,     0,    49,     0,     0,    57,    61,    60,     0,
       0,     0,     0,    75,    87,    88,    91,    90,    93,    94,
      97,    98,    96,    95,   100,   101,    64,    63,     0,    67,
      66,     0,    79,    76,    78,    77,     0,     0,     0,    68,
      50,     0,     0,    69
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -126,  -126,  -126,   -13,  -126,    -7,    -1,  -126,  -126,  -126,
    -126,  -126,   185,  -126,   179,  -126,   180,  -126,   -29,   101,
      17,  -126,    79,  -126,    77,  -126,    50,    23,    51,  -126,
    -126,    66,  -126,  -124,    33,     4,    27,  -125
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     6,    16,    21,    22,    25,     7,     8,    12,
      46,    26,    27,    55,    56,    57,    58,    66,    67,    68,
      69,   110,   111,   113,   114,   136,   137,   139,   140,   199,
     127,   128,   129,   130,   131,   132,   133,   134
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     154,    19,   155,   115,   116,   117,   118,   119,   208,    20,
      24,   120,   121,   122,    23,    13,    34,    86,    87,    64,
      14,    35,   179,   180,   181,   182,   123,   124,    24,    37,
      88,    48,   184,   185,   125,    29,    78,    52,    49,    36,
     209,   126,    30,    50,   196,   151,   116,   117,   118,   119,
      65,    86,    87,   120,   121,   122,   101,     9,    80,    81,
      82,    83,    84,    10,    93,   108,    11,    80,    81,    82,
      83,    84,    59,    60,    61,    31,   125,    32,    53,    33,
      77,    32,    79,    94,    62,    54,   212,   141,    63,    15,
      89,    90,    91,    92,    86,    87,    86,    87,    86,    87,
      86,    87,   166,   167,   166,   167,    18,   104,    20,   105,
      17,   106,    28,   107,    42,   168,    45,   183,   166,   167,
     166,   167,   166,   167,   166,   167,   166,   167,    70,    86,
      87,   202,    73,   203,    74,   204,    43,   205,    95,   213,
      51,    44,   156,   157,    38,    39,    40,    41,   160,   161,
     142,   145,   162,   163,     2,   143,   146,     3,   164,   165,
     158,   159,     4,     5,   188,   189,   190,   191,   192,   193,
     170,   173,   210,   166,   167,   171,   174,   174,    80,    81,
      82,    83,    84,    38,    39,    40,    41,   102,   103,   152,
     153,   186,   187,   194,   195,    75,    85,    76,    96,    97,
      98,    99,   109,   100,   112,   135,   138,   147,   148,   149,
     150,   175,   144,   169,   177,   198,   201,   206,   211,   172,
      47,   197,   176,   178,   207,   200,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    71,    72
};

static const yytype_int16 yycheck[] =
{
     125,    14,   126,     3,     4,     5,     6,     7,     3,     3,
      17,    11,    12,    13,    15,     3,    35,    26,    27,     3,
       8,    40,   147,   148,   149,   150,    26,    27,    35,    30,
      39,    44,   156,   157,    34,    33,    65,    50,     3,    33,
      35,    41,    40,     8,   169,     3,     4,     5,     6,     7,
      34,    26,    27,    11,    12,    13,    85,    38,    15,    16,
      17,    18,    19,     3,    39,    94,     3,    15,    16,    17,
      18,    19,    26,    27,    28,    38,    34,    40,     3,    38,
      63,    40,    65,    40,    38,    10,   211,    35,    42,    32,
      73,    74,    75,    76,    26,    27,    26,    27,    26,    27,
      26,    27,    22,    23,    22,    23,    39,    39,     3,    39,
      34,    39,    39,    39,     3,    35,    38,    35,    22,    23,
      22,    23,    22,    23,    22,    23,    22,    23,    33,    26,
      27,    35,    42,    35,    42,    35,     3,    35,    35,    35,
      32,     8,    28,    29,    11,    12,    13,    14,    20,    21,
      35,    35,    24,    25,     0,    40,    40,     3,    30,    31,
      26,    27,     8,     9,   160,   161,   162,   163,   164,   165,
      35,    35,    35,    22,    23,    40,    40,    40,    15,    16,
      17,    18,    19,    11,    12,    13,    14,    86,    87,   123,
     124,   158,   159,   166,   167,    42,    28,    42,    34,    34,
      34,    34,     3,    34,     3,     3,     3,    34,    34,    34,
      34,    19,    42,    42,     3,     3,    34,    34,    40,    42,
      35,   171,   143,   146,   201,   174,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    57
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    44,     0,     3,     8,     9,    45,    50,    51,    38,
       3,     3,    52,     3,     8,    32,    46,    34,    39,    46,
       3,    47,    48,    49,    48,    49,    54,    55,    39,    33,
      40,    38,    40,    38,    35,    40,    33,    49,    11,    12,
      13,    14,     3,     3,     8,    38,    53,    55,    46,     3,
       8,    32,    46,     3,    10,    56,    57,    58,    59,    26,
      27,    28,    38,    42,     3,    34,    60,    61,    62,    63,
      33,    57,    59,    42,    42,    42,    42,    63,    61,    63,
      15,    16,    17,    18,    19,    28,    26,    27,    39,    63,
      63,    63,    63,    39,    40,    35,    34,    34,    34,    34,
      34,    61,    62,    62,    39,    39,    39,    39,    61,     3,
      64,    65,     3,    66,    67,     3,     4,     5,     6,     7,
      11,    12,    13,    26,    27,    34,    41,    73,    74,    75,
      76,    77,    78,    79,    80,     3,    68,    69,     3,    70,
      71,    35,    35,    40,    42,    35,    40,    34,    34,    34,
      34,     3,    74,    74,    80,    76,    28,    29,    26,    27,
      20,    21,    24,    25,    30,    31,    22,    23,    35,    42,
      35,    40,    42,    35,    40,    19,    65,     3,    67,    80,
      80,    80,    80,    35,    76,    76,    77,    77,    78,    78,
      78,    78,    78,    78,    79,    79,    80,    69,     3,    72,
      71,    34,    35,    35,    35,    35,    34,    70,     3,    35,
      35,    40,    80,    35
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    44,    44,    44,    45,    46,    46,    47,
      47,    48,    48,    49,    49,    49,    49,    50,    50,    51,
      52,    53,    53,    53,    54,    54,    54,    55,    55,    55,
      56,    56,    56,    56,    57,    58,    58,    59,    59,    59,
      59,    59,    60,    60,    61,    61,    61,    61,    61,    61,
      61,    62,    62,    63,    63,    63,    64,    64,    65,    66,
      66,    67,    68,    68,    69,    70,    70,    71,    72,    72,
      73,    73,    73,    73,    74,    74,    74,    74,    74,    74,
      75,    75,    76,    76,    76,    76,    77,    77,    77,    78,
      78,    78,    79,    79,    79,    79,    79,    79,    79,    80,
      80,    80
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     0,     3,     3,     4,     1,
       3,     1,     3,     3,     3,     3,     3,     4,     5,     9,
       1,     2,     3,     0,     1,     3,     0,     1,     3,     4,
       1,     1,     2,     0,     3,     1,     2,     4,     5,     5,
       5,     5,     1,     3,     1,     5,     5,     5,     5,     5,
       9,     1,     3,     1,     3,     3,     1,     3,     1,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     6,
       1,     1,     1,     1,     1,     3,     4,     4,     4,     4,
       1,     1,     1,     2,     2,     2,     1,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     3,     3,     1,
       3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
#line 58 "convert.y" /* yacc.c:1646  */
    { sys_print("%s\n\n", (yyvsp[0].val)); mem_free((yyvsp[0].val)); }
#line 1424 "convert.c" /* yacc.c:1646  */
    break;

  case 3:
#line 59 "convert.y" /* yacc.c:1646  */
    { sys_print("%s\n\n", (yyvsp[0].val)); mem_free((yyvsp[0].val)); }
#line 1430 "convert.c" /* yacc.c:1646  */
    break;

  case 4:
#line 60 "convert.y" /* yacc.c:1646  */
    { sys_print("%s\n\n", (yyvsp[0].val)); mem_free((yyvsp[0].val)); }
#line 1436 "convert.c" /* yacc.c:1646  */
    break;

  case 6:
#line 65 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("type %s %s", (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1442 "convert.c" /* yacc.c:1646  */
    break;

  case 7:
#line 69 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s%s%s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1448 "convert.c" /* yacc.c:1646  */
    break;

  case 8:
#line 70 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s%s%s", (yyvsp[-3].val), (yyvsp[-2].val), (yyvsp[0].val)); }
#line 1454 "convert.c" /* yacc.c:1646  */
    break;

  case 9:
#line 74 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1460 "convert.c" /* yacc.c:1646  */
    break;

  case 10:
#line 75 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s%s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1466 "convert.c" /* yacc.c:1646  */
    break;

  case 11:
#line 79 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1472 "convert.c" /* yacc.c:1646  */
    break;

  case 12:
#line 80 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s", (yyvsp[-2].val), (yyvsp[0].val)); }
#line 1478 "convert.c" /* yacc.c:1646  */
    break;

  case 13:
#line 84 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s", (yyvsp[-2].val), (yyvsp[0].val)); }
#line 1484 "convert.c" /* yacc.c:1646  */
    break;

  case 14:
#line 85 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s", (yyvsp[-2].val), (yyvsp[0].val)); }
#line 1490 "convert.c" /* yacc.c:1646  */
    break;

  case 15:
#line 86 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s", (yyvsp[-2].val), (yyvsp[0].val)); }
#line 1496 "convert.c" /* yacc.c:1646  */
    break;

  case 16:
#line 87 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s", (yyvsp[-2].val), (yyvsp[0].val)); }
#line 1502 "convert.c" /* yacc.c:1646  */
    break;

  case 17:
#line 91 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("var %s %s%s", (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1508 "convert.c" /* yacc.c:1646  */
    break;

  case 18:
#line 92 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("var %s %s%s", (yyvsp[-4].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1514 "convert.c" /* yacc.c:1646  */
    break;

  case 19:
#line 97 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s%s%s%s %s\n%s%s%s", (yyvsp[-8].val), (yyvsp[-7].val), (yyvsp[-6].val), (yyvsp[-5].val), (yyvsp[-4].val), (yyvsp[-3].val), (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1520 "convert.c" /* yacc.c:1646  */
    break;

  case 20:
#line 101 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1526 "convert.c" /* yacc.c:1646  */
    break;

  case 21:
#line 105 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1532 "convert.c" /* yacc.c:1646  */
    break;

  case 22:
#line 106 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1538 "convert.c" /* yacc.c:1646  */
    break;

  case 23:
#line 107 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("void"); }
#line 1544 "convert.c" /* yacc.c:1646  */
    break;

  case 24:
#line 111 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1550 "convert.c" /* yacc.c:1646  */
    break;

  case 25:
#line 112 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s%s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1556 "convert.c" /* yacc.c:1646  */
    break;

  case 26:
#line 113 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat(""); }
#line 1562 "convert.c" /* yacc.c:1646  */
    break;

  case 27:
#line 117 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1568 "convert.c" /* yacc.c:1646  */
    break;

  case 28:
#line 118 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s", (yyvsp[-2].val), (yyvsp[0].val)); }
#line 1574 "convert.c" /* yacc.c:1646  */
    break;

  case 29:
#line 119 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s", (yyvsp[-3].val), (yyvsp[0].val)); }
#line 1580 "convert.c" /* yacc.c:1646  */
    break;

  case 30:
#line 123 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("\n%s\n", (yyvsp[0].val)); }
#line 1586 "convert.c" /* yacc.c:1646  */
    break;

  case 31:
#line 124 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("\n%s\n", (yyvsp[0].val)); }
#line 1592 "convert.c" /* yacc.c:1646  */
    break;

  case 32:
#line 125 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("\n%s\n\n%s\n", (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1598 "convert.c" /* yacc.c:1646  */
    break;

  case 33:
#line 126 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat(""); }
#line 1604 "convert.c" /* yacc.c:1646  */
    break;

  case 34:
#line 130 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("\t%s %s%s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1610 "convert.c" /* yacc.c:1646  */
    break;

  case 35:
#line 134 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1616 "convert.c" /* yacc.c:1646  */
    break;

  case 36:
#line 135 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s\n%s", (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1622 "convert.c" /* yacc.c:1646  */
    break;

  case 37:
#line 140 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("\t%s %s %s%s", (yyvsp[-3].val), (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1628 "convert.c" /* yacc.c:1646  */
    break;

  case 38:
#line 142 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("\t%s %s%s %s%s", (yyvsp[-4].val), (yyvsp[-3].val), (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1634 "convert.c" /* yacc.c:1646  */
    break;

  case 39:
#line 144 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("\t%s %s%s %s%s", (yyvsp[-4].val), (yyvsp[-3].val), (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1640 "convert.c" /* yacc.c:1646  */
    break;

  case 40:
#line 146 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("\t%s %s%s %s%s", (yyvsp[-4].val), (yyvsp[-3].val), (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1646 "convert.c" /* yacc.c:1646  */
    break;

  case 41:
#line 148 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("\tvar %s %s %s%s", (yyvsp[-4].val), (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1652 "convert.c" /* yacc.c:1646  */
    break;

  case 42:
#line 152 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1658 "convert.c" /* yacc.c:1646  */
    break;

  case 43:
#line 153 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[-1].val)); }
#line 1664 "convert.c" /* yacc.c:1646  */
    break;

  case 44:
#line 158 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1670 "convert.c" /* yacc.c:1646  */
    break;

  case 45:
#line 160 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("(%s %s %s)", (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[-4].val)); }
#line 1676 "convert.c" /* yacc.c:1646  */
    break;

  case 46:
#line 162 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("(%s %s %s)", (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[-4].val)); }
#line 1682 "convert.c" /* yacc.c:1646  */
    break;

  case 47:
#line 164 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("(%s %s %s)", (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[-4].val)); }
#line 1688 "convert.c" /* yacc.c:1646  */
    break;

  case 48:
#line 166 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("(%s %s %s)", (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[-4].val)); }
#line 1694 "convert.c" /* yacc.c:1646  */
    break;

  case 49:
#line 168 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("(%s %s %s)", (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[-4].val)); }
#line 1700 "convert.c" /* yacc.c:1646  */
    break;

  case 50:
#line 170 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("(%s %s %s %s)", (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[-7].val), (yyvsp[-5].val)); }
#line 1706 "convert.c" /* yacc.c:1646  */
    break;

  case 51:
#line 174 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1712 "convert.c" /* yacc.c:1646  */
    break;

  case 52:
#line 175 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("(join %s %s)", (yyvsp[-2].val), (yyvsp[0].val)); }
#line 1718 "convert.c" /* yacc.c:1646  */
    break;

  case 53:
#line 179 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1724 "convert.c" /* yacc.c:1646  */
    break;

  case 54:
#line 180 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("(union %s %s)", (yyvsp[-2].val), (yyvsp[0].val)); }
#line 1730 "convert.c" /* yacc.c:1646  */
    break;

  case 55:
#line 181 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("(minus %s %s)", (yyvsp[-2].val), (yyvsp[0].val)); }
#line 1736 "convert.c" /* yacc.c:1646  */
    break;

  case 56:
#line 185 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1742 "convert.c" /* yacc.c:1646  */
    break;

  case 57:
#line 186 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s%s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1748 "convert.c" /* yacc.c:1646  */
    break;

  case 58:
#line 190 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1754 "convert.c" /* yacc.c:1646  */
    break;

  case 59:
#line 194 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1760 "convert.c" /* yacc.c:1646  */
    break;

  case 60:
#line 195 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s%s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1766 "convert.c" /* yacc.c:1646  */
    break;

  case 61:
#line 199 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1772 "convert.c" /* yacc.c:1646  */
    break;

  case 62:
#line 203 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1778 "convert.c" /* yacc.c:1646  */
    break;

  case 63:
#line 204 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s%s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1784 "convert.c" /* yacc.c:1646  */
    break;

  case 64:
#line 208 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1790 "convert.c" /* yacc.c:1646  */
    break;

  case 65:
#line 212 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1796 "convert.c" /* yacc.c:1646  */
    break;

  case 66:
#line 213 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s%s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1802 "convert.c" /* yacc.c:1646  */
    break;

  case 67:
#line 217 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1808 "convert.c" /* yacc.c:1646  */
    break;

  case 68:
#line 222 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[-2].val)); }
#line 1814 "convert.c" /* yacc.c:1646  */
    break;

  case 69:
#line 224 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s%s %s %s%s", (yyvsp[-4].val), (yyvsp[-5].val), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1820 "convert.c" /* yacc.c:1646  */
    break;

  case 70:
#line 228 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1826 "convert.c" /* yacc.c:1646  */
    break;

  case 71:
#line 229 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1832 "convert.c" /* yacc.c:1646  */
    break;

  case 72:
#line 230 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1838 "convert.c" /* yacc.c:1646  */
    break;

  case 73:
#line 231 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1844 "convert.c" /* yacc.c:1646  */
    break;

  case 74:
#line 236 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1850 "convert.c" /* yacc.c:1646  */
    break;

  case 75:
#line 238 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s%s%s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1856 "convert.c" /* yacc.c:1646  */
    break;

  case 76:
#line 240 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s%s %s%s", (yyvsp[-2].val), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1862 "convert.c" /* yacc.c:1646  */
    break;

  case 77:
#line 242 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s%s %s%s", (yyvsp[-2].val), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1868 "convert.c" /* yacc.c:1646  */
    break;

  case 78:
#line 244 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s%s %s%s", (yyvsp[-2].val), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1874 "convert.c" /* yacc.c:1646  */
    break;

  case 79:
#line 246 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s%s %s%s", (yyvsp[-2].val), (yyvsp[-3].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1880 "convert.c" /* yacc.c:1646  */
    break;

  case 80:
#line 250 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1886 "convert.c" /* yacc.c:1646  */
    break;

  case 81:
#line 251 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1892 "convert.c" /* yacc.c:1646  */
    break;

  case 82:
#line 255 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1898 "convert.c" /* yacc.c:1646  */
    break;

  case 83:
#line 256 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s%s", (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1904 "convert.c" /* yacc.c:1646  */
    break;

  case 84:
#line 257 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s%s", (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1910 "convert.c" /* yacc.c:1646  */
    break;

  case 85:
#line 258 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s%s", (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1916 "convert.c" /* yacc.c:1646  */
    break;

  case 86:
#line 262 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1922 "convert.c" /* yacc.c:1646  */
    break;

  case 87:
#line 263 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1928 "convert.c" /* yacc.c:1646  */
    break;

  case 88:
#line 264 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1934 "convert.c" /* yacc.c:1646  */
    break;

  case 89:
#line 268 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1940 "convert.c" /* yacc.c:1646  */
    break;

  case 90:
#line 269 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1946 "convert.c" /* yacc.c:1646  */
    break;

  case 91:
#line 270 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1952 "convert.c" /* yacc.c:1646  */
    break;

  case 92:
#line 275 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 1958 "convert.c" /* yacc.c:1646  */
    break;

  case 93:
#line 277 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1964 "convert.c" /* yacc.c:1646  */
    break;

  case 94:
#line 279 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1970 "convert.c" /* yacc.c:1646  */
    break;

  case 95:
#line 281 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1976 "convert.c" /* yacc.c:1646  */
    break;

  case 96:
#line 283 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1982 "convert.c" /* yacc.c:1646  */
    break;

  case 97:
#line 285 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1988 "convert.c" /* yacc.c:1646  */
    break;

  case 98:
#line 287 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 1994 "convert.c" /* yacc.c:1646  */
    break;

  case 99:
#line 292 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s", (yyvsp[0].val)); }
#line 2000 "convert.c" /* yacc.c:1646  */
    break;

  case 100:
#line 294 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 2006 "convert.c" /* yacc.c:1646  */
    break;

  case 101:
#line 296 "convert.y" /* yacc.c:1646  */
    { (yyval.val) = cat("%s %s %s", (yyvsp[-2].val), (yyvsp[-1].val), (yyvsp[0].val)); }
#line 2012 "convert.c" /* yacc.c:1646  */
    break;


#line 2016 "convert.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
                  yystos[*yyssp], yyvsp);
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
#line 299 "convert.y" /* yacc.c:1906  */

