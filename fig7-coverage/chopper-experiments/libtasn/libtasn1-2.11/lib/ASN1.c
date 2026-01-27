/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         _asn1_yyparse
#define yylex           _asn1_yylex
#define yyerror         _asn1_yyerror
#define yydebug         _asn1_yydebug
#define yynerrs         _asn1_yynerrs
#define yylval          _asn1_yylval
#define yychar          _asn1_yychar

/* First part of user prologue.  */
#line 1 "libtasn1-2.11//lib/ASN1.y"

/*
 * Copyright (C) 2001, 2002, 2004, 2005, 2006, 2008, 2009, 2010, 2011
 * Free Software Foundation, Inc.
 *
 * This file is part of LIBTASN1.
 *
 * The LIBTASN1 library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA
 */

/*****************************************************/
/* File: x509_ASN.y                                  */
/* Description: input file for 'bison' program.      */
/*   The output file is a parser (in C language) for */
/*   ASN.1 syntax                                    */
/*****************************************************/

#include <int.h>
#include <parser_aux.h>
#include <structure.h>

static FILE *file_asn1;			/* Pointer to file to parse */
static asn1_retCode result_parse;	/* result of the parser
					   algorithm */
static ASN1_TYPE p_tree;		/* pointer to the root of the
					   structure created by the
					   parser*/
static unsigned long lineNumber;	/* line number describing the
					   parser position inside the
					   file */
static char lastToken[ASN1_MAX_NAME_SIZE+1];	/* last token find in the file
					   to parse before the 'parse
					   error' */
extern char _asn1_identifierMissing[];
static const char *fileName;		/* file to parse */

static int _asn1_yyerror (const char *);
static int _asn1_yylex(void);


#line 132 "y.tab.c"

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


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int _asn1_yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ASSIG = 258,                   /* "::="  */
    NUM = 259,                     /* NUM  */
    IDENTIFIER = 260,              /* IDENTIFIER  */
    OPTIONAL = 261,                /* OPTIONAL  */
    INTEGER = 262,                 /* INTEGER  */
    SIZE = 263,                    /* SIZE  */
    OCTET = 264,                   /* OCTET  */
    STRING = 265,                  /* STRING  */
    SEQUENCE = 266,                /* SEQUENCE  */
    BIT = 267,                     /* BIT  */
    UNIVERSAL = 268,               /* UNIVERSAL  */
    PRIVATE = 269,                 /* PRIVATE  */
    APPLICATION = 270,             /* APPLICATION  */
    DEFAULT = 271,                 /* DEFAULT  */
    CHOICE = 272,                  /* CHOICE  */
    OF = 273,                      /* OF  */
    OBJECT = 274,                  /* OBJECT  */
    STR_IDENTIFIER = 275,          /* STR_IDENTIFIER  */
    BOOLEAN = 276,                 /* BOOLEAN  */
    ASN1_TRUE = 277,               /* ASN1_TRUE  */
    ASN1_FALSE = 278,              /* ASN1_FALSE  */
    TOKEN_NULL = 279,              /* TOKEN_NULL  */
    ANY = 280,                     /* ANY  */
    DEFINED = 281,                 /* DEFINED  */
    BY = 282,                      /* BY  */
    SET = 283,                     /* SET  */
    EXPLICIT = 284,                /* EXPLICIT  */
    IMPLICIT = 285,                /* IMPLICIT  */
    DEFINITIONS = 286,             /* DEFINITIONS  */
    TAGS = 287,                    /* TAGS  */
    BEGIN = 288,                   /* BEGIN  */
    END = 289,                     /* END  */
    UTCTime = 290,                 /* UTCTime  */
    GeneralizedTime = 291,         /* GeneralizedTime  */
    GeneralString = 292,           /* GeneralString  */
    FROM = 293,                    /* FROM  */
    IMPORTS = 294,                 /* IMPORTS  */
    ENUMERATED = 295               /* ENUMERATED  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ASSIG 258
#define NUM 259
#define IDENTIFIER 260
#define OPTIONAL 261
#define INTEGER 262
#define SIZE 263
#define OCTET 264
#define STRING 265
#define SEQUENCE 266
#define BIT 267
#define UNIVERSAL 268
#define PRIVATE 269
#define APPLICATION 270
#define DEFAULT 271
#define CHOICE 272
#define OF 273
#define OBJECT 274
#define STR_IDENTIFIER 275
#define BOOLEAN 276
#define ASN1_TRUE 277
#define ASN1_FALSE 278
#define TOKEN_NULL 279
#define ANY 280
#define DEFINED 281
#define BY 282
#define SET 283
#define EXPLICIT 284
#define IMPLICIT 285
#define DEFINITIONS 286
#define TAGS 287
#define BEGIN 288
#define END 289
#define UTCTime 290
#define GeneralizedTime 291
#define GeneralString 292
#define FROM 293
#define IMPORTS 294
#define ENUMERATED 295

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 58 "libtasn1-2.11//lib/ASN1.y"

  unsigned int constant;
  char str[ASN1_MAX_NAME_SIZE+1];
  ASN1_TYPE node;

#line 268 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE _asn1_yylval;


int _asn1_yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ASSIG = 3,                      /* "::="  */
  YYSYMBOL_NUM = 4,                        /* NUM  */
  YYSYMBOL_IDENTIFIER = 5,                 /* IDENTIFIER  */
  YYSYMBOL_OPTIONAL = 6,                   /* OPTIONAL  */
  YYSYMBOL_INTEGER = 7,                    /* INTEGER  */
  YYSYMBOL_SIZE = 8,                       /* SIZE  */
  YYSYMBOL_OCTET = 9,                      /* OCTET  */
  YYSYMBOL_STRING = 10,                    /* STRING  */
  YYSYMBOL_SEQUENCE = 11,                  /* SEQUENCE  */
  YYSYMBOL_BIT = 12,                       /* BIT  */
  YYSYMBOL_UNIVERSAL = 13,                 /* UNIVERSAL  */
  YYSYMBOL_PRIVATE = 14,                   /* PRIVATE  */
  YYSYMBOL_APPLICATION = 15,               /* APPLICATION  */
  YYSYMBOL_DEFAULT = 16,                   /* DEFAULT  */
  YYSYMBOL_CHOICE = 17,                    /* CHOICE  */
  YYSYMBOL_OF = 18,                        /* OF  */
  YYSYMBOL_OBJECT = 19,                    /* OBJECT  */
  YYSYMBOL_STR_IDENTIFIER = 20,            /* STR_IDENTIFIER  */
  YYSYMBOL_BOOLEAN = 21,                   /* BOOLEAN  */
  YYSYMBOL_ASN1_TRUE = 22,                 /* ASN1_TRUE  */
  YYSYMBOL_ASN1_FALSE = 23,                /* ASN1_FALSE  */
  YYSYMBOL_TOKEN_NULL = 24,                /* TOKEN_NULL  */
  YYSYMBOL_ANY = 25,                       /* ANY  */
  YYSYMBOL_DEFINED = 26,                   /* DEFINED  */
  YYSYMBOL_BY = 27,                        /* BY  */
  YYSYMBOL_SET = 28,                       /* SET  */
  YYSYMBOL_EXPLICIT = 29,                  /* EXPLICIT  */
  YYSYMBOL_IMPLICIT = 30,                  /* IMPLICIT  */
  YYSYMBOL_DEFINITIONS = 31,               /* DEFINITIONS  */
  YYSYMBOL_TAGS = 32,                      /* TAGS  */
  YYSYMBOL_BEGIN = 33,                     /* BEGIN  */
  YYSYMBOL_END = 34,                       /* END  */
  YYSYMBOL_UTCTime = 35,                   /* UTCTime  */
  YYSYMBOL_GeneralizedTime = 36,           /* GeneralizedTime  */
  YYSYMBOL_GeneralString = 37,             /* GeneralString  */
  YYSYMBOL_FROM = 38,                      /* FROM  */
  YYSYMBOL_IMPORTS = 39,                   /* IMPORTS  */
  YYSYMBOL_ENUMERATED = 40,                /* ENUMERATED  */
  YYSYMBOL_41_ = 41,                       /* '+'  */
  YYSYMBOL_42_ = 42,                       /* '-'  */
  YYSYMBOL_43_ = 43,                       /* '('  */
  YYSYMBOL_44_ = 44,                       /* ')'  */
  YYSYMBOL_45_ = 45,                       /* ','  */
  YYSYMBOL_46_ = 46,                       /* '['  */
  YYSYMBOL_47_ = 47,                       /* ']'  */
  YYSYMBOL_48_ = 48,                       /* '|'  */
  YYSYMBOL_49_ = 49,                       /* '{'  */
  YYSYMBOL_50_ = 50,                       /* '}'  */
  YYSYMBOL_51_ = 51,                       /* '.'  */
  YYSYMBOL_YYACCEPT = 52,                  /* $accept  */
  YYSYMBOL_definitions = 53,               /* definitions  */
  YYSYMBOL_pos_num = 54,                   /* pos_num  */
  YYSYMBOL_neg_num = 55,                   /* neg_num  */
  YYSYMBOL_pos_neg_num = 56,               /* pos_neg_num  */
  YYSYMBOL_num_identifier = 57,            /* num_identifier  */
  YYSYMBOL_pos_neg_identifier = 58,        /* pos_neg_identifier  */
  YYSYMBOL_constant = 59,                  /* constant  */
  YYSYMBOL_constant_list = 60,             /* constant_list  */
  YYSYMBOL_obj_constant = 61,              /* obj_constant  */
  YYSYMBOL_obj_constant_list = 62,         /* obj_constant_list  */
  YYSYMBOL_class = 63,                     /* class  */
  YYSYMBOL_tag_type = 64,                  /* tag_type  */
  YYSYMBOL_tag = 65,                       /* tag  */
  YYSYMBOL_default = 66,                   /* default  */
  YYSYMBOL_pos_neg_list = 67,              /* pos_neg_list  */
  YYSYMBOL_integer_def = 68,               /* integer_def  */
  YYSYMBOL_boolean_def = 69,               /* boolean_def  */
  YYSYMBOL_Time = 70,                      /* Time  */
  YYSYMBOL_size_def2 = 71,                 /* size_def2  */
  YYSYMBOL_size_def = 72,                  /* size_def  */
  YYSYMBOL_generalstring_def = 73,         /* generalstring_def  */
  YYSYMBOL_octet_string_def = 74,          /* octet_string_def  */
  YYSYMBOL_bit_element = 75,               /* bit_element  */
  YYSYMBOL_bit_element_list = 76,          /* bit_element_list  */
  YYSYMBOL_bit_string_def = 77,            /* bit_string_def  */
  YYSYMBOL_enumerated_def = 78,            /* enumerated_def  */
  YYSYMBOL_object_def = 79,                /* object_def  */
  YYSYMBOL_type_assig_right = 80,          /* type_assig_right  */
  YYSYMBOL_type_assig_right_tag = 81,      /* type_assig_right_tag  */
  YYSYMBOL_type_assig_right_tag_default = 82, /* type_assig_right_tag_default  */
  YYSYMBOL_type_assig = 83,                /* type_assig  */
  YYSYMBOL_type_assig_list = 84,           /* type_assig_list  */
  YYSYMBOL_sequence_def = 85,              /* sequence_def  */
  YYSYMBOL_set_def = 86,                   /* set_def  */
  YYSYMBOL_choise_def = 87,                /* choise_def  */
  YYSYMBOL_any_def = 88,                   /* any_def  */
  YYSYMBOL_type_def = 89,                  /* type_def  */
  YYSYMBOL_constant_def = 90,              /* constant_def  */
  YYSYMBOL_type_constant = 91,             /* type_constant  */
  YYSYMBOL_type_constant_list = 92,        /* type_constant_list  */
  YYSYMBOL_definitions_id = 93,            /* definitions_id  */
  YYSYMBOL_explicit_implicit = 94          /* explicit_implicit  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   192

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  190

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      43,    44,     2,    41,    45,    42,    51,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    46,     2,    47,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,    48,    50,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   119,   119,   132,   133,   136,   140,   141,   144,   145,
     148,   149,   152,   154,   159,   160,   164,   166,   171,   172,
     176,   177,   178,   181,   183,   187,   188,   189,   192,   194,
     195,   199,   200,   204,   205,   207,   208,   215,   218,   219,
     222,   224,   230,   231,   234,   235,   239,   240,   244,   249,
     250,   254,   255,   256,   261,   267,   270,   272,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   290,   291,   296,   297,   300,   303,   306,   307,   311,
     313,   315,   320,   322,   324,   329,   333,   334,   339,   342,
     346,   351,   357,   358,   361,   362,   366,   369,   393,   394
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "\"::=\"", "NUM",
  "IDENTIFIER", "OPTIONAL", "INTEGER", "SIZE", "OCTET", "STRING",
  "SEQUENCE", "BIT", "UNIVERSAL", "PRIVATE", "APPLICATION", "DEFAULT",
  "CHOICE", "OF", "OBJECT", "STR_IDENTIFIER", "BOOLEAN", "ASN1_TRUE",
  "ASN1_FALSE", "TOKEN_NULL", "ANY", "DEFINED", "BY", "SET", "EXPLICIT",
  "IMPLICIT", "DEFINITIONS", "TAGS", "BEGIN", "END", "UTCTime",
  "GeneralizedTime", "GeneralString", "FROM", "IMPORTS", "ENUMERATED",
  "'+'", "'-'", "'('", "')'", "','", "'['", "']'", "'|'", "'{'", "'}'",
  "'.'", "$accept", "definitions", "pos_num", "neg_num", "pos_neg_num",
  "num_identifier", "pos_neg_identifier", "constant", "constant_list",
  "obj_constant", "obj_constant_list", "class", "tag_type", "tag",
  "default", "pos_neg_list", "integer_def", "boolean_def", "Time",
  "size_def2", "size_def", "generalstring_def", "octet_string_def",
  "bit_element", "bit_element_list", "bit_string_def", "enumerated_def",
  "object_def", "type_assig_right", "type_assig_right_tag",
  "type_assig_right_tag_default", "type_assig", "type_assig_list",
  "sequence_def", "set_def", "choise_def", "any_def", "type_def",
  "constant_def", "type_constant", "type_constant_list", "definitions_id",
  "explicit_implicit", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-96)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-9)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      24,   -14,    48,    56,     0,   -96,   -10,   -96,    -2,   -96,
     -96,   -96,     2,   -96,   -96,    71,   111,   -96,   -96,   117,
      83,    96,   -96,   127,    42,   -96,   -96,   -96,    10,    77,
     130,   131,   115,   -96,   -96,     8,    90,   132,    13,   135,
      92,   126,   -96,   -96,   122,    15,   -96,   -96,     8,   100,
      93,    49,   119,    94,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   102,    28,   149,
     110,   150,   -96,   -96,    17,     8,   119,   152,   142,    22,
     152,   -96,   134,   119,   152,   144,   -96,   158,   118,   -96,
     -96,   -96,   160,   -96,   -96,   -96,    35,    88,   -96,   162,
     163,   -96,   -96,   -96,   120,   114,   124,   128,    28,   -96,
      -8,   -96,   -96,    77,   -96,    -7,   119,   158,   -96,    18,
     165,   -96,    50,   119,   129,   -96,    54,   -96,   133,   123,
     -96,   -96,   125,    37,     4,   -96,   -96,    88,   -27,   -96,
      28,   137,    17,   -96,    20,   -96,   152,   -96,   -96,    66,
     -96,   -96,   -96,   -96,   169,   158,   -96,   -96,   136,   -96,
      28,   -96,     7,   -96,   138,   139,   -96,   -96,   -96,    68,
     -96,   -96,   -96,   140,   -96,   114,   -96,   -96,   114,   -96,
     -96,   -96,   -96,   -96,   -96,   -96,   141,   146,   -96,   -96
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     1,     0,     8,     9,    97,
      16,    18,     0,    98,    99,     0,     0,    96,    19,     0,
       0,     0,    17,     0,     0,    92,    93,    94,     0,     0,
       0,     0,     0,     2,    95,    56,    33,     0,     0,     0,
       0,     0,    37,    70,    86,     0,    38,    39,    44,     0,
       0,    25,     0,    58,    60,    61,    64,    62,    63,    59,
      66,    71,    88,    65,    69,    67,    68,     0,     0,     0,
       0,     0,    42,    57,     0,    46,     0,     0,     0,    51,
       0,    55,     0,     0,     0,     0,    45,     0,     0,    20,
      21,    22,     0,    26,    27,    72,     0,     0,     3,     0,
       0,     6,     7,    91,     0,     0,     0,     0,     0,    14,
       0,    47,    80,     0,    77,     0,     0,     0,    52,     0,
       0,    83,     0,     0,     0,    49,     0,    23,     0,     3,
       9,    31,     0,     0,     0,     4,     5,     0,     0,    43,
       0,     0,     0,    34,    73,    76,     0,    79,    81,     0,
      85,    87,    82,    84,     0,     0,    54,    24,     0,    35,
       0,    90,     0,    40,     0,     0,    12,    15,    75,     0,
      74,    78,    53,     0,    50,     0,    32,    89,     0,    13,
      11,    29,    30,    10,    28,    48,     0,     0,    36,    41
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -96,   -96,   -96,   -96,   -94,   -95,   -96,    33,   -96,   -12,
     -84,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   106,
     -20,   -96,   -96,    23,    62,   -96,   -96,   -96,   -49,    69,
     -96,    40,    41,   -96,   -96,   -96,   -96,   -96,   -96,   164,
     -96,   -96,   -96
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,   101,   102,   103,    10,   184,   109,   110,    11,
      12,    92,    51,    52,   170,   133,    53,    54,    55,    72,
      73,    56,    57,   125,   126,    58,    59,    60,    61,    62,
     145,   114,   115,    63,    64,    65,    66,    25,    26,    27,
      28,     3,    15
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      18,   132,   131,    95,     7,     8,     7,     8,     7,     8,
     138,     7,     8,   134,   141,    24,    70,   163,    78,    13,
      14,    70,   107,    70,   164,    85,   168,   112,    86,     1,
      70,    76,    98,    83,   121,     4,   169,   142,   146,   129,
     130,    16,   143,   147,    33,    29,   165,    30,     5,    31,
       9,    71,    17,   162,   161,   111,    71,   177,    71,   118,
     108,    32,    77,   146,    84,    71,   176,   148,   150,    99,
     100,   117,    98,   180,   153,   183,    99,   100,    93,    94,
     186,   159,    35,   187,    36,   160,    37,     6,    38,    39,
     181,   182,     7,     8,    40,   146,    41,    88,    42,   155,
     152,    43,    44,    19,   156,    45,    89,    90,    91,    99,
     100,   155,    46,    47,    48,    20,   172,    49,     7,   130,
      21,   119,    18,    50,    35,   122,    36,    22,    37,    23,
      38,    39,    24,    67,    68,    69,    40,    96,    41,    74,
      42,    80,    75,    43,    44,    79,    81,    45,    82,    87,
      18,    97,   104,   105,    46,    47,    48,   113,    70,    49,
     116,   120,   123,   124,   128,   127,   135,   136,   139,   137,
     151,   140,   154,   173,    -8,   167,   158,   106,   174,   149,
     157,   166,   144,   179,   185,   188,   171,   175,     0,   178,
     189,     0,    34
};

static const yytype_int16 yycheck[] =
{
      12,    96,    96,    52,     4,     5,     4,     5,     4,     5,
     105,     4,     5,    97,   108,     5,     8,    44,    38,    29,
      30,     8,     5,     8,    51,    45,     6,    76,    48,     5,
       8,    18,     4,    18,    83,    49,    16,    45,    45,     4,
       5,    43,    50,    50,    34,     3,   140,     5,     0,     7,
      50,    43,    50,   137,    50,    75,    43,    50,    43,    79,
      43,    19,    49,    45,    49,    43,   160,   116,    50,    41,
      42,    49,     4,     5,   123,   169,    41,    42,    29,    30,
     175,    44,     5,   178,     7,    48,     9,    31,    11,    12,
      22,    23,     4,     5,    17,    45,    19,     4,    21,    45,
      50,    24,    25,    32,    50,    28,    13,    14,    15,    41,
      42,    45,    35,    36,    37,     4,    50,    40,     4,     5,
       3,    80,   134,    46,     5,    84,     7,    44,     9,    33,
      11,    12,     5,     3,     3,    20,    17,    43,    19,    49,
      21,    49,    10,    24,    25,    10,    20,    28,    26,    49,
     162,    49,     3,    43,    35,    36,    37,     5,     8,    40,
      18,    27,    18,     5,     4,    47,     4,     4,    44,    49,
       5,    43,    43,     4,    51,   142,    51,    71,   155,   117,
      47,    44,   113,    44,    44,    44,   146,    51,    -1,    51,
      44,    -1,    28
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,    53,    93,    49,     0,    31,     4,     5,    50,
      57,    61,    62,    29,    30,    94,    43,    50,    61,    32,
       4,     3,    44,    33,     5,    89,    90,    91,    92,     3,
       5,     7,    19,    34,    91,     5,     7,     9,    11,    12,
      17,    19,    21,    24,    25,    28,    35,    36,    37,    40,
      46,    64,    65,    68,    69,    70,    73,    74,    77,    78,
      79,    80,    81,    85,    86,    87,    88,     3,     3,    20,
       8,    43,    71,    72,    49,    10,    18,    49,    72,    10,
      49,    20,    26,    18,    49,    72,    72,    49,     4,    13,
      14,    15,    63,    29,    30,    80,    43,    49,     4,    41,
      42,    54,    55,    56,     3,    43,    71,     5,    43,    59,
      60,    72,    80,     5,    83,    84,    18,    49,    72,    84,
      27,    80,    84,    18,     5,    75,    76,    47,     4,     4,
       5,    56,    57,    67,    62,     4,     4,    49,    57,    44,
      43,    56,    45,    50,    81,    82,    45,    50,    80,    76,
      50,     5,    50,    80,    43,    45,    50,    47,    51,    44,
      48,    50,    62,    44,    51,    56,    44,    59,     6,    16,
      66,    83,    50,     4,    75,    51,    56,    50,    51,    44,
       5,    22,    23,    56,    58,    44,    57,    57,    44,    44
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    52,    53,    54,    54,    55,    56,    56,    57,    57,
      58,    58,    59,    59,    60,    60,    61,    61,    62,    62,
      63,    63,    63,    64,    64,    65,    65,    65,    66,    66,
      66,    67,    67,    68,    68,    68,    68,    69,    70,    70,
      71,    71,    72,    72,    73,    73,    74,    74,    75,    76,
      76,    77,    77,    77,    78,    79,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    81,    81,    82,    82,    82,    83,    84,    84,    85,
      85,    85,    86,    86,    86,    87,    88,    88,    89,    90,
      90,    90,    91,    91,    92,    92,    93,    93,    94,    94
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     8,     1,     2,     2,     1,     1,     1,     1,
       1,     1,     3,     4,     1,     3,     1,     4,     1,     2,
       1,     1,     1,     3,     4,     1,     2,     2,     2,     2,
       2,     1,     3,     1,     4,     4,     7,     1,     1,     1,
       4,     7,     1,     3,     1,     2,     2,     3,     4,     1,
       3,     2,     3,     5,     4,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     2,     2,     1,     3,     4,
       3,     4,     4,     3,     4,     4,     1,     4,     3,     7,
       6,     4,     1,     1,     1,     2,     4,     3,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* definitions: definitions_id DEFINITIONS explicit_implicit TAGS "::=" BEGIN type_constant_list END  */
#line 122 "libtasn1-2.11//lib/ASN1.y"
                   {(yyval.node)=_asn1_add_node(TYPE_DEFINITIONS|(yyvsp[-5].constant));
                    _asn1_set_name((yyval.node),_asn1_get_name((yyvsp[-7].node)));
                    _asn1_set_name((yyvsp[-7].node),"");
                    _asn1_set_right((yyvsp[-7].node),(yyvsp[-1].node));
                    _asn1_set_down((yyval.node),(yyvsp[-7].node));

		    p_tree=(yyval.node);
		    }
#line 1482 "y.tab.c"
    break;

  case 3: /* pos_num: NUM  */
#line 132 "libtasn1-2.11//lib/ASN1.y"
                      {strcpy((yyval.str),(yyvsp[0].str));}
#line 1488 "y.tab.c"
    break;

  case 4: /* pos_num: '+' NUM  */
#line 133 "libtasn1-2.11//lib/ASN1.y"
                      {strcpy((yyval.str),(yyvsp[0].str));}
#line 1494 "y.tab.c"
    break;

  case 5: /* neg_num: '-' NUM  */
#line 136 "libtasn1-2.11//lib/ASN1.y"
                      {strcpy((yyval.str),"-");
                       strcat((yyval.str),(yyvsp[0].str));}
#line 1501 "y.tab.c"
    break;

  case 6: /* pos_neg_num: pos_num  */
#line 140 "libtasn1-2.11//lib/ASN1.y"
                        {strcpy((yyval.str),(yyvsp[0].str));}
#line 1507 "y.tab.c"
    break;

  case 7: /* pos_neg_num: neg_num  */
#line 141 "libtasn1-2.11//lib/ASN1.y"
                        {strcpy((yyval.str),(yyvsp[0].str));}
#line 1513 "y.tab.c"
    break;

  case 8: /* num_identifier: NUM  */
#line 144 "libtasn1-2.11//lib/ASN1.y"
                                 {strcpy((yyval.str),(yyvsp[0].str));}
#line 1519 "y.tab.c"
    break;

  case 9: /* num_identifier: IDENTIFIER  */
#line 145 "libtasn1-2.11//lib/ASN1.y"
                                 {strcpy((yyval.str),(yyvsp[0].str));}
#line 1525 "y.tab.c"
    break;

  case 10: /* pos_neg_identifier: pos_neg_num  */
#line 148 "libtasn1-2.11//lib/ASN1.y"
                                     {strcpy((yyval.str),(yyvsp[0].str));}
#line 1531 "y.tab.c"
    break;

  case 11: /* pos_neg_identifier: IDENTIFIER  */
#line 149 "libtasn1-2.11//lib/ASN1.y"
                                     {strcpy((yyval.str),(yyvsp[0].str));}
#line 1537 "y.tab.c"
    break;

  case 12: /* constant: '(' pos_neg_num ')'  */
#line 152 "libtasn1-2.11//lib/ASN1.y"
                                      {(yyval.node)=_asn1_add_node(TYPE_CONSTANT);
                                       _asn1_set_value((yyval.node),(yyvsp[-1].str),strlen((yyvsp[-1].str))+1);}
#line 1544 "y.tab.c"
    break;

  case 13: /* constant: IDENTIFIER '(' pos_neg_num ')'  */
#line 154 "libtasn1-2.11//lib/ASN1.y"
                                      {(yyval.node)=_asn1_add_node(TYPE_CONSTANT);
	                               _asn1_set_name((yyval.node),(yyvsp[-3].str));
                                       _asn1_set_value((yyval.node),(yyvsp[-1].str),strlen((yyvsp[-1].str))+1);}
#line 1552 "y.tab.c"
    break;

  case 14: /* constant_list: constant  */
#line 159 "libtasn1-2.11//lib/ASN1.y"
                                           {(yyval.node)=(yyvsp[0].node);}
#line 1558 "y.tab.c"
    break;

  case 15: /* constant_list: constant_list ',' constant  */
#line 160 "libtasn1-2.11//lib/ASN1.y"
                                           {(yyval.node)=(yyvsp[-2].node);
                                            _asn1_set_right(_asn1_get_last_right((yyvsp[-2].node)),(yyvsp[0].node));}
#line 1565 "y.tab.c"
    break;

  case 16: /* obj_constant: num_identifier  */
#line 164 "libtasn1-2.11//lib/ASN1.y"
                                  {(yyval.node)=_asn1_add_node(TYPE_CONSTANT);
                                   _asn1_set_value((yyval.node),(yyvsp[0].str),strlen((yyvsp[0].str))+1);}
#line 1572 "y.tab.c"
    break;

  case 17: /* obj_constant: IDENTIFIER '(' NUM ')'  */
#line 166 "libtasn1-2.11//lib/ASN1.y"
                                   {(yyval.node)=_asn1_add_node(TYPE_CONSTANT);
	                            _asn1_set_name((yyval.node),(yyvsp[-3].str));
                                    _asn1_set_value((yyval.node),(yyvsp[-1].str),strlen((yyvsp[-1].str))+1);}
#line 1580 "y.tab.c"
    break;

  case 18: /* obj_constant_list: obj_constant  */
#line 171 "libtasn1-2.11//lib/ASN1.y"
                                                   {(yyval.node)=(yyvsp[0].node);}
#line 1586 "y.tab.c"
    break;

  case 19: /* obj_constant_list: obj_constant_list obj_constant  */
#line 172 "libtasn1-2.11//lib/ASN1.y"
                                                   {(yyval.node)=(yyvsp[-1].node);
                                                    _asn1_set_right(_asn1_get_last_right((yyvsp[-1].node)),(yyvsp[0].node));}
#line 1593 "y.tab.c"
    break;

  case 20: /* class: UNIVERSAL  */
#line 176 "libtasn1-2.11//lib/ASN1.y"
                      {(yyval.constant)=CONST_UNIVERSAL;}
#line 1599 "y.tab.c"
    break;

  case 21: /* class: PRIVATE  */
#line 177 "libtasn1-2.11//lib/ASN1.y"
                      {(yyval.constant)=CONST_PRIVATE;}
#line 1605 "y.tab.c"
    break;

  case 22: /* class: APPLICATION  */
#line 178 "libtasn1-2.11//lib/ASN1.y"
                      {(yyval.constant)=CONST_APPLICATION;}
#line 1611 "y.tab.c"
    break;

  case 23: /* tag_type: '[' NUM ']'  */
#line 181 "libtasn1-2.11//lib/ASN1.y"
                           {(yyval.node)=_asn1_add_node(TYPE_TAG);
                            _asn1_set_value((yyval.node),(yyvsp[-1].str),strlen((yyvsp[-1].str))+1);}
#line 1618 "y.tab.c"
    break;

  case 24: /* tag_type: '[' class NUM ']'  */
#line 183 "libtasn1-2.11//lib/ASN1.y"
                               {(yyval.node)=_asn1_add_node(TYPE_TAG | (yyvsp[-2].constant));
                                _asn1_set_value((yyval.node),(yyvsp[-1].str),strlen((yyvsp[-1].str))+1);}
#line 1625 "y.tab.c"
    break;

  case 25: /* tag: tag_type  */
#line 187 "libtasn1-2.11//lib/ASN1.y"
                          {(yyval.node)=(yyvsp[0].node);}
#line 1631 "y.tab.c"
    break;

  case 26: /* tag: tag_type EXPLICIT  */
#line 188 "libtasn1-2.11//lib/ASN1.y"
                          {(yyval.node)=_asn1_mod_type((yyvsp[-1].node),CONST_EXPLICIT);}
#line 1637 "y.tab.c"
    break;

  case 27: /* tag: tag_type IMPLICIT  */
#line 189 "libtasn1-2.11//lib/ASN1.y"
                          {(yyval.node)=_asn1_mod_type((yyvsp[-1].node),CONST_IMPLICIT);}
#line 1643 "y.tab.c"
    break;

  case 28: /* default: DEFAULT pos_neg_identifier  */
#line 192 "libtasn1-2.11//lib/ASN1.y"
                                      {(yyval.node)=_asn1_add_node(TYPE_DEFAULT);
                                       _asn1_set_value((yyval.node),(yyvsp[0].str),strlen((yyvsp[0].str))+1);}
#line 1650 "y.tab.c"
    break;

  case 29: /* default: DEFAULT ASN1_TRUE  */
#line 194 "libtasn1-2.11//lib/ASN1.y"
                                       {(yyval.node)=_asn1_add_node(TYPE_DEFAULT|CONST_TRUE);}
#line 1656 "y.tab.c"
    break;

  case 30: /* default: DEFAULT ASN1_FALSE  */
#line 195 "libtasn1-2.11//lib/ASN1.y"
                                       {(yyval.node)=_asn1_add_node(TYPE_DEFAULT|CONST_FALSE);}
#line 1662 "y.tab.c"
    break;

  case 33: /* integer_def: INTEGER  */
#line 204 "libtasn1-2.11//lib/ASN1.y"
                                        {(yyval.node)=_asn1_add_node(TYPE_INTEGER);}
#line 1668 "y.tab.c"
    break;

  case 34: /* integer_def: INTEGER '{' constant_list '}'  */
#line 205 "libtasn1-2.11//lib/ASN1.y"
                                        {(yyval.node)=_asn1_add_node(TYPE_INTEGER|CONST_LIST);
	                                 _asn1_set_down((yyval.node),(yyvsp[-1].node));}
#line 1675 "y.tab.c"
    break;

  case 35: /* integer_def: integer_def '(' pos_neg_list ')'  */
#line 207 "libtasn1-2.11//lib/ASN1.y"
                                             {(yyval.node)=_asn1_add_node(TYPE_INTEGER);}
#line 1681 "y.tab.c"
    break;

  case 36: /* integer_def: integer_def '(' num_identifier '.' '.' num_identifier ')'  */
#line 209 "libtasn1-2.11//lib/ASN1.y"
                                        {(yyval.node)=_asn1_add_node(TYPE_INTEGER|CONST_MIN_MAX);
                                         _asn1_set_down((yyval.node),_asn1_add_node(TYPE_SIZE));
                                         _asn1_set_value(_asn1_get_down((yyval.node)),(yyvsp[-1].str),strlen((yyvsp[-1].str))+1);
                                         _asn1_set_name(_asn1_get_down((yyval.node)),(yyvsp[-4].str));}
#line 1690 "y.tab.c"
    break;

  case 37: /* boolean_def: BOOLEAN  */
#line 215 "libtasn1-2.11//lib/ASN1.y"
                       {(yyval.node)=_asn1_add_node(TYPE_BOOLEAN);}
#line 1696 "y.tab.c"
    break;

  case 38: /* Time: UTCTime  */
#line 218 "libtasn1-2.11//lib/ASN1.y"
                         {(yyval.node)=_asn1_add_node(TYPE_TIME|CONST_UTC);}
#line 1702 "y.tab.c"
    break;

  case 39: /* Time: GeneralizedTime  */
#line 219 "libtasn1-2.11//lib/ASN1.y"
                         {(yyval.node)=_asn1_add_node(TYPE_TIME|CONST_GENERALIZED);}
#line 1708 "y.tab.c"
    break;

  case 40: /* size_def2: SIZE '(' num_identifier ')'  */
#line 222 "libtasn1-2.11//lib/ASN1.y"
                                     {(yyval.node)=_asn1_add_node(TYPE_SIZE|CONST_1_PARAM);
	                              _asn1_set_value((yyval.node),(yyvsp[-1].str),strlen((yyvsp[-1].str))+1);}
#line 1715 "y.tab.c"
    break;

  case 41: /* size_def2: SIZE '(' num_identifier '.' '.' num_identifier ')'  */
#line 225 "libtasn1-2.11//lib/ASN1.y"
                                     {(yyval.node)=_asn1_add_node(TYPE_SIZE|CONST_MIN_MAX);
	                              _asn1_set_value((yyval.node),(yyvsp[-4].str),strlen((yyvsp[-4].str))+1);
                                      _asn1_set_name((yyval.node),(yyvsp[-1].str));}
#line 1723 "y.tab.c"
    break;

  case 42: /* size_def: size_def2  */
#line 230 "libtasn1-2.11//lib/ASN1.y"
                               {(yyval.node)=(yyvsp[0].node);}
#line 1729 "y.tab.c"
    break;

  case 43: /* size_def: '(' size_def2 ')'  */
#line 231 "libtasn1-2.11//lib/ASN1.y"
                               {(yyval.node)=(yyvsp[-1].node);}
#line 1735 "y.tab.c"
    break;

  case 44: /* generalstring_def: GeneralString  */
#line 234 "libtasn1-2.11//lib/ASN1.y"
                                 {(yyval.node)=_asn1_add_node(TYPE_GENERALSTRING);}
#line 1741 "y.tab.c"
    break;

  case 45: /* generalstring_def: GeneralString size_def  */
#line 235 "libtasn1-2.11//lib/ASN1.y"
                                         {(yyval.node)=_asn1_add_node(TYPE_GENERALSTRING|CONST_SIZE);
					  _asn1_set_down((yyval.node),(yyvsp[0].node));}
#line 1748 "y.tab.c"
    break;

  case 46: /* octet_string_def: OCTET STRING  */
#line 239 "libtasn1-2.11//lib/ASN1.y"
                                          {(yyval.node)=_asn1_add_node(TYPE_OCTET_STRING);}
#line 1754 "y.tab.c"
    break;

  case 47: /* octet_string_def: OCTET STRING size_def  */
#line 240 "libtasn1-2.11//lib/ASN1.y"
                                          {(yyval.node)=_asn1_add_node(TYPE_OCTET_STRING|CONST_SIZE);
                                           _asn1_set_down((yyval.node),(yyvsp[0].node));}
#line 1761 "y.tab.c"
    break;

  case 48: /* bit_element: IDENTIFIER '(' NUM ')'  */
#line 244 "libtasn1-2.11//lib/ASN1.y"
                                   {(yyval.node)=_asn1_add_node(TYPE_CONSTANT);
	                           _asn1_set_name((yyval.node),(yyvsp[-3].str));
                                    _asn1_set_value((yyval.node),(yyvsp[-1].str),strlen((yyvsp[-1].str))+1);}
#line 1769 "y.tab.c"
    break;

  case 49: /* bit_element_list: bit_element  */
#line 249 "libtasn1-2.11//lib/ASN1.y"
                                  {(yyval.node)=(yyvsp[0].node);}
#line 1775 "y.tab.c"
    break;

  case 50: /* bit_element_list: bit_element_list ',' bit_element  */
#line 250 "libtasn1-2.11//lib/ASN1.y"
                                                      {(yyval.node)=(yyvsp[-2].node);
                                                       _asn1_set_right(_asn1_get_last_right((yyvsp[-2].node)),(yyvsp[0].node));}
#line 1782 "y.tab.c"
    break;

  case 51: /* bit_string_def: BIT STRING  */
#line 254 "libtasn1-2.11//lib/ASN1.y"
                               {(yyval.node)=_asn1_add_node(TYPE_BIT_STRING);}
#line 1788 "y.tab.c"
    break;

  case 52: /* bit_string_def: BIT STRING size_def  */
#line 255 "libtasn1-2.11//lib/ASN1.y"
                                     {(yyval.node)=_asn1_add_node(TYPE_BIT_STRING|CONST_SIZE);}
#line 1794 "y.tab.c"
    break;

  case 53: /* bit_string_def: BIT STRING '{' bit_element_list '}'  */
#line 257 "libtasn1-2.11//lib/ASN1.y"
                               {(yyval.node)=_asn1_add_node(TYPE_BIT_STRING|CONST_LIST);
                                _asn1_set_down((yyval.node),(yyvsp[-1].node));}
#line 1801 "y.tab.c"
    break;

  case 54: /* enumerated_def: ENUMERATED '{' bit_element_list '}'  */
#line 262 "libtasn1-2.11//lib/ASN1.y"
                               {(yyval.node)=_asn1_add_node(TYPE_ENUMERATED|CONST_LIST);
                                _asn1_set_down((yyval.node),(yyvsp[-1].node));}
#line 1808 "y.tab.c"
    break;

  case 55: /* object_def: OBJECT STR_IDENTIFIER  */
#line 267 "libtasn1-2.11//lib/ASN1.y"
                                    {(yyval.node)=_asn1_add_node(TYPE_OBJECT_ID);}
#line 1814 "y.tab.c"
    break;

  case 56: /* type_assig_right: IDENTIFIER  */
#line 270 "libtasn1-2.11//lib/ASN1.y"
                                      {(yyval.node)=_asn1_add_node(TYPE_IDENTIFIER);
                                       _asn1_set_value((yyval.node),(yyvsp[0].str),strlen((yyvsp[0].str))+1);}
#line 1821 "y.tab.c"
    break;

  case 57: /* type_assig_right: IDENTIFIER size_def  */
#line 272 "libtasn1-2.11//lib/ASN1.y"
                                      {(yyval.node)=_asn1_add_node(TYPE_IDENTIFIER|CONST_SIZE);
                                       _asn1_set_value((yyval.node),(yyvsp[-1].str),strlen((yyvsp[-1].str))+1);
                                       _asn1_set_down((yyval.node),(yyvsp[0].node));}
#line 1829 "y.tab.c"
    break;

  case 58: /* type_assig_right: integer_def  */
#line 275 "libtasn1-2.11//lib/ASN1.y"
                                      {(yyval.node)=(yyvsp[0].node);}
#line 1835 "y.tab.c"
    break;

  case 59: /* type_assig_right: enumerated_def  */
#line 276 "libtasn1-2.11//lib/ASN1.y"
                                      {(yyval.node)=(yyvsp[0].node);}
#line 1841 "y.tab.c"
    break;

  case 60: /* type_assig_right: boolean_def  */
#line 277 "libtasn1-2.11//lib/ASN1.y"
                                      {(yyval.node)=(yyvsp[0].node);}
#line 1847 "y.tab.c"
    break;

  case 62: /* type_assig_right: octet_string_def  */
#line 279 "libtasn1-2.11//lib/ASN1.y"
                                      {(yyval.node)=(yyvsp[0].node);}
#line 1853 "y.tab.c"
    break;

  case 63: /* type_assig_right: bit_string_def  */
#line 280 "libtasn1-2.11//lib/ASN1.y"
                                      {(yyval.node)=(yyvsp[0].node);}
#line 1859 "y.tab.c"
    break;

  case 64: /* type_assig_right: generalstring_def  */
#line 281 "libtasn1-2.11//lib/ASN1.y"
                                      {(yyval.node)=(yyvsp[0].node);}
#line 1865 "y.tab.c"
    break;

  case 65: /* type_assig_right: sequence_def  */
#line 282 "libtasn1-2.11//lib/ASN1.y"
                                      {(yyval.node)=(yyvsp[0].node);}
#line 1871 "y.tab.c"
    break;

  case 66: /* type_assig_right: object_def  */
#line 283 "libtasn1-2.11//lib/ASN1.y"
                                      {(yyval.node)=(yyvsp[0].node);}
#line 1877 "y.tab.c"
    break;

  case 67: /* type_assig_right: choise_def  */
#line 284 "libtasn1-2.11//lib/ASN1.y"
                                      {(yyval.node)=(yyvsp[0].node);}
#line 1883 "y.tab.c"
    break;

  case 68: /* type_assig_right: any_def  */
#line 285 "libtasn1-2.11//lib/ASN1.y"
                                      {(yyval.node)=(yyvsp[0].node);}
#line 1889 "y.tab.c"
    break;

  case 69: /* type_assig_right: set_def  */
#line 286 "libtasn1-2.11//lib/ASN1.y"
                                      {(yyval.node)=(yyvsp[0].node);}
#line 1895 "y.tab.c"
    break;

  case 70: /* type_assig_right: TOKEN_NULL  */
#line 287 "libtasn1-2.11//lib/ASN1.y"
                                      {(yyval.node)=_asn1_add_node(TYPE_NULL);}
#line 1901 "y.tab.c"
    break;

  case 71: /* type_assig_right_tag: type_assig_right  */
#line 290 "libtasn1-2.11//lib/ASN1.y"
                                              {(yyval.node)=(yyvsp[0].node);}
#line 1907 "y.tab.c"
    break;

  case 72: /* type_assig_right_tag: tag type_assig_right  */
#line 291 "libtasn1-2.11//lib/ASN1.y"
                                              {(yyval.node)=_asn1_mod_type((yyvsp[0].node),CONST_TAG);
                                               _asn1_set_right((yyvsp[-1].node),_asn1_get_down((yyval.node)));
                                               _asn1_set_down((yyval.node),(yyvsp[-1].node));}
#line 1915 "y.tab.c"
    break;

  case 73: /* type_assig_right_tag_default: type_assig_right_tag  */
#line 296 "libtasn1-2.11//lib/ASN1.y"
                                                      {(yyval.node)=(yyvsp[0].node);}
#line 1921 "y.tab.c"
    break;

  case 74: /* type_assig_right_tag_default: type_assig_right_tag default  */
#line 297 "libtasn1-2.11//lib/ASN1.y"
                                                      {(yyval.node)=_asn1_mod_type((yyvsp[-1].node),CONST_DEFAULT);
                                                       _asn1_set_right((yyvsp[0].node),_asn1_get_down((yyval.node)));
						       _asn1_set_down((yyval.node),(yyvsp[0].node));}
#line 1929 "y.tab.c"
    break;

  case 75: /* type_assig_right_tag_default: type_assig_right_tag OPTIONAL  */
#line 300 "libtasn1-2.11//lib/ASN1.y"
                                                      {(yyval.node)=_asn1_mod_type((yyvsp[-1].node),CONST_OPTION);}
#line 1935 "y.tab.c"
    break;

  case 76: /* type_assig: IDENTIFIER type_assig_right_tag_default  */
#line 303 "libtasn1-2.11//lib/ASN1.y"
                                                      {(yyval.node)=_asn1_set_name((yyvsp[0].node),(yyvsp[-1].str));}
#line 1941 "y.tab.c"
    break;

  case 77: /* type_assig_list: type_assig  */
#line 306 "libtasn1-2.11//lib/ASN1.y"
                                               {(yyval.node)=(yyvsp[0].node);}
#line 1947 "y.tab.c"
    break;

  case 78: /* type_assig_list: type_assig_list ',' type_assig  */
#line 307 "libtasn1-2.11//lib/ASN1.y"
                                               {(yyval.node)=(yyvsp[-2].node);
                                                _asn1_set_right(_asn1_get_last_right((yyvsp[-2].node)),(yyvsp[0].node));}
#line 1954 "y.tab.c"
    break;

  case 79: /* sequence_def: SEQUENCE '{' type_assig_list '}'  */
#line 311 "libtasn1-2.11//lib/ASN1.y"
                                             {(yyval.node)=_asn1_add_node(TYPE_SEQUENCE);
                                              _asn1_set_down((yyval.node),(yyvsp[-1].node));}
#line 1961 "y.tab.c"
    break;

  case 80: /* sequence_def: SEQUENCE OF type_assig_right  */
#line 313 "libtasn1-2.11//lib/ASN1.y"
                                             {(yyval.node)=_asn1_add_node(TYPE_SEQUENCE_OF);
                                              _asn1_set_down((yyval.node),(yyvsp[0].node));}
#line 1968 "y.tab.c"
    break;

  case 81: /* sequence_def: SEQUENCE size_def OF type_assig_right  */
#line 315 "libtasn1-2.11//lib/ASN1.y"
                                           {(yyval.node)=_asn1_add_node(TYPE_SEQUENCE_OF|CONST_SIZE);
                                            _asn1_set_right((yyvsp[-2].node),(yyvsp[0].node));
                                            _asn1_set_down((yyval.node),(yyvsp[-2].node));}
#line 1976 "y.tab.c"
    break;

  case 82: /* set_def: SET '{' type_assig_list '}'  */
#line 320 "libtasn1-2.11//lib/ASN1.y"
                                    {(yyval.node)=_asn1_add_node(TYPE_SET);
                                     _asn1_set_down((yyval.node),(yyvsp[-1].node));}
#line 1983 "y.tab.c"
    break;

  case 83: /* set_def: SET OF type_assig_right  */
#line 322 "libtasn1-2.11//lib/ASN1.y"
                                    {(yyval.node)=_asn1_add_node(TYPE_SET_OF);
                                     _asn1_set_down((yyval.node),(yyvsp[0].node));}
#line 1990 "y.tab.c"
    break;

  case 84: /* set_def: SET size_def OF type_assig_right  */
#line 324 "libtasn1-2.11//lib/ASN1.y"
                                      {(yyval.node)=_asn1_add_node(TYPE_SET_OF|CONST_SIZE);
                                       _asn1_set_right((yyvsp[-2].node),(yyvsp[0].node));
                                       _asn1_set_down((yyval.node),(yyvsp[-2].node));}
#line 1998 "y.tab.c"
    break;

  case 85: /* choise_def: CHOICE '{' type_assig_list '}'  */
#line 329 "libtasn1-2.11//lib/ASN1.y"
                                            {(yyval.node)=_asn1_add_node(TYPE_CHOICE);
                                             _asn1_set_down((yyval.node),(yyvsp[-1].node));}
#line 2005 "y.tab.c"
    break;

  case 86: /* any_def: ANY  */
#line 333 "libtasn1-2.11//lib/ASN1.y"
                                       {(yyval.node)=_asn1_add_node(TYPE_ANY);}
#line 2011 "y.tab.c"
    break;

  case 87: /* any_def: ANY DEFINED BY IDENTIFIER  */
#line 334 "libtasn1-2.11//lib/ASN1.y"
                                       {(yyval.node)=_asn1_add_node(TYPE_ANY|CONST_DEFINED_BY);
                                        _asn1_set_down((yyval.node),_asn1_add_node(TYPE_CONSTANT));
	                                _asn1_set_name(_asn1_get_down((yyval.node)),(yyvsp[0].str));}
#line 2019 "y.tab.c"
    break;

  case 88: /* type_def: IDENTIFIER "::=" type_assig_right_tag  */
#line 339 "libtasn1-2.11//lib/ASN1.y"
                                                  {(yyval.node)=_asn1_set_name((yyvsp[0].node),(yyvsp[-2].str));}
#line 2025 "y.tab.c"
    break;

  case 89: /* constant_def: IDENTIFIER OBJECT STR_IDENTIFIER "::=" '{' obj_constant_list '}'  */
#line 343 "libtasn1-2.11//lib/ASN1.y"
                        {(yyval.node)=_asn1_add_node(TYPE_OBJECT_ID|CONST_ASSIGN);
                         _asn1_set_name((yyval.node),(yyvsp[-6].str));
                         _asn1_set_down((yyval.node),(yyvsp[-1].node));}
#line 2033 "y.tab.c"
    break;

  case 90: /* constant_def: IDENTIFIER IDENTIFIER "::=" '{' obj_constant_list '}'  */
#line 347 "libtasn1-2.11//lib/ASN1.y"
                        {(yyval.node)=_asn1_add_node(TYPE_OBJECT_ID|CONST_ASSIGN|CONST_1_PARAM);
                         _asn1_set_name((yyval.node),(yyvsp[-5].str));
                         _asn1_set_value((yyval.node),(yyvsp[-4].str),strlen((yyvsp[-4].str))+1);
                         _asn1_set_down((yyval.node),(yyvsp[-1].node));}
#line 2042 "y.tab.c"
    break;

  case 91: /* constant_def: IDENTIFIER INTEGER "::=" pos_neg_num  */
#line 352 "libtasn1-2.11//lib/ASN1.y"
                        {(yyval.node)=_asn1_add_node(TYPE_INTEGER|CONST_ASSIGN);
                         _asn1_set_name((yyval.node),(yyvsp[-3].str));
                         _asn1_set_value((yyval.node),(yyvsp[0].str),strlen((yyvsp[0].str))+1);}
#line 2050 "y.tab.c"
    break;

  case 92: /* type_constant: type_def  */
#line 357 "libtasn1-2.11//lib/ASN1.y"
                              {(yyval.node)=(yyvsp[0].node);}
#line 2056 "y.tab.c"
    break;

  case 93: /* type_constant: constant_def  */
#line 358 "libtasn1-2.11//lib/ASN1.y"
                              {(yyval.node)=(yyvsp[0].node);}
#line 2062 "y.tab.c"
    break;

  case 94: /* type_constant_list: type_constant  */
#line 361 "libtasn1-2.11//lib/ASN1.y"
                                        {(yyval.node)=(yyvsp[0].node);}
#line 2068 "y.tab.c"
    break;

  case 95: /* type_constant_list: type_constant_list type_constant  */
#line 362 "libtasn1-2.11//lib/ASN1.y"
                                                         {(yyval.node)=(yyvsp[-1].node);
                                                          _asn1_set_right(_asn1_get_last_right((yyvsp[-1].node)),(yyvsp[0].node));}
#line 2075 "y.tab.c"
    break;

  case 96: /* definitions_id: IDENTIFIER '{' obj_constant_list '}'  */
#line 366 "libtasn1-2.11//lib/ASN1.y"
                                                         {(yyval.node)=_asn1_add_node(TYPE_OBJECT_ID);
                                                          _asn1_set_down((yyval.node),(yyvsp[-1].node));
                                                          _asn1_set_name((yyval.node),(yyvsp[-3].str));}
#line 2083 "y.tab.c"
    break;

  case 97: /* definitions_id: IDENTIFIER '{' '}'  */
#line 369 "libtasn1-2.11//lib/ASN1.y"
                                                         {(yyval.node)=_asn1_add_node(TYPE_OBJECT_ID);
                                                          _asn1_set_name((yyval.node),(yyvsp[-2].str));}
#line 2090 "y.tab.c"
    break;

  case 98: /* explicit_implicit: EXPLICIT  */
#line 393 "libtasn1-2.11//lib/ASN1.y"
                               {(yyval.constant)=CONST_EXPLICIT;}
#line 2096 "y.tab.c"
    break;

  case 99: /* explicit_implicit: IMPLICIT  */
#line 394 "libtasn1-2.11//lib/ASN1.y"
                               {(yyval.constant)=CONST_IMPLICIT;}
#line 2102 "y.tab.c"
    break;


#line 2106 "y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 398 "libtasn1-2.11//lib/ASN1.y"




static const char *key_word[] = {
  "::=","OPTIONAL","INTEGER","SIZE","OCTET","STRING"
  ,"SEQUENCE","BIT","UNIVERSAL","PRIVATE","OPTIONAL"
  ,"DEFAULT","CHOICE","OF","OBJECT","IDENTIFIER"
  ,"BOOLEAN","TRUE","FALSE","APPLICATION","ANY","DEFINED"
  ,"SET","BY","EXPLICIT","IMPLICIT","DEFINITIONS","TAGS"
  ,"BEGIN","END","UTCTime","GeneralizedTime"
  ,"GeneralString","FROM","IMPORTS","NULL","ENUMERATED"};
static const int key_word_token[] = {
  ASSIG,OPTIONAL,INTEGER,SIZE,OCTET,STRING
  ,SEQUENCE,BIT,UNIVERSAL,PRIVATE,OPTIONAL
  ,DEFAULT,CHOICE,OF,OBJECT,STR_IDENTIFIER
  ,BOOLEAN,ASN1_TRUE,ASN1_FALSE,APPLICATION,ANY,DEFINED
  ,SET,BY,EXPLICIT,IMPLICIT,DEFINITIONS,TAGS
  ,BEGIN,END,UTCTime,GeneralizedTime
  ,GeneralString,FROM,IMPORTS,TOKEN_NULL,ENUMERATED};

/*************************************************************/
/*  Function: _asn1_yylex                                    */
/*  Description: looks for tokens in file_asn1 pointer file. */
/*  Return: int                                              */
/*    Token identifier or ASCII code or 0(zero: End Of File) */
/*************************************************************/
static int
_asn1_yylex()
{
  int c,counter=0,k,lastc;
  char string[ASN1_MAX_NAME_SIZE+1]; /* will contain the next token */
  size_t i;

  while(1)
    {
    while((c=fgetc(file_asn1))==' ' || c=='\t' || c=='\n')
      if(c=='\n') lineNumber++;

    if(c==EOF){
      strcpy(lastToken,"End Of File");
      return 0;
    }

    if(c=='(' || c==')' || c=='[' || c==']' ||
       c=='{' || c=='}' || c==',' || c=='.' ||
       c=='+' || c=='|'){
      lastToken[0]=c;lastToken[1]=0;
      return c;
    }
    if(c=='-'){  /* Maybe the first '-' of a comment */
      if((c=fgetc(file_asn1))!='-'){
	ungetc(c,file_asn1);
	lastToken[0]='-';lastToken[1]=0;
	return '-';
      }
      else{ /* Comments */
	lastc=0;
	counter=0;
	/* A comment finishes at the next double hypen or the end of line */
	while((c=fgetc(file_asn1))!=EOF && c!='\n' &&
	      (lastc!='-' || (lastc=='-' && c!='-')))
	  lastc=c;
	if(c==EOF){
	  strcpy(lastToken,"End Of File");
	  return 0;
	}
	else{
	  if(c=='\n') lineNumber++;
	  continue; /* next char, please! (repeat the search) */
	}
      }
    }
    string[counter++]=c;
    /* Till the end of the token */
    while(!((c=fgetc(file_asn1))==EOF || c==' '|| c=='\t' || c=='\n' ||
	     c=='(' || c==')' || c=='[' || c==']' ||
	     c=='{' || c=='}' || c==',' || c=='.'))
      {
	if(counter>=ASN1_MAX_NAME_SIZE){
	  result_parse=ASN1_NAME_TOO_LONG;
	  return 0;
	}
	string[counter++]=c;
      }
    ungetc(c,file_asn1);
    string[counter]=0;
    strcpy(lastToken,string);

    /* Is STRING a number? */
    for(k=0;k<counter;k++)
      if(!isdigit(string[k])) break;
    if(k>=counter)
      {
      strcpy(yylval.str,string);
      return NUM; /* return the number */
      }

    /* Is STRING a keyword? */
    for(i=0;i<(sizeof(key_word)/sizeof(char*));i++)
      if(!strcmp(string,key_word[i])) return key_word_token[i];

    /* STRING is an IDENTIFIER */
    strcpy(yylval.str,string);
    return IDENTIFIER;
    }
}

/*************************************************************/
/*  Function: _asn1_create_errorDescription                  */
/*  Description: creates a string with the description of the*/
/*    error.                                                 */
/*  Parameters:                                              */
/*    error : error to describe.                             */
/*    errorDescription: string that will contain the         */
/*                      description.                         */
/*************************************************************/
static void
_asn1_create_errorDescription(int error,char *errorDescription)
{
  switch(error){
  case ASN1_SUCCESS: case ASN1_FILE_NOT_FOUND:
    if (errorDescription!=NULL) errorDescription[0]=0;
    break;
  case ASN1_SYNTAX_ERROR:
    if (errorDescription!=NULL) {
	strcpy(errorDescription,fileName);
	strcat(errorDescription,":");
	_asn1_ltostr(lineNumber,errorDescription+strlen(fileName)+1);
	strcat(errorDescription,": parse error near '");
	strcat(errorDescription,lastToken);
	strcat(errorDescription,"'");
    }
    break;
  case ASN1_NAME_TOO_LONG:
    if (errorDescription!=NULL) {
       strcpy(errorDescription,fileName);
       strcat(errorDescription,":");
       _asn1_ltostr(lineNumber,errorDescription+strlen(fileName)+1);
       strcat(errorDescription,": name too long (more than ");
       _asn1_ltostr(ASN1_MAX_NAME_SIZE,errorDescription+strlen(errorDescription));
       strcat(errorDescription," characters)");
    }
    break;
  case ASN1_IDENTIFIER_NOT_FOUND:
    if (errorDescription!=NULL) {
       strcpy(errorDescription,fileName);
       strcat(errorDescription,":");
       strcat(errorDescription,": identifier '");
       strcat(errorDescription,_asn1_identifierMissing);
       strcat(errorDescription,"' not found");
    }
    break;
  default:
    if (errorDescription!=NULL) errorDescription[0]=0;
    break;
  }

}

/**
 * asn1_parser2tree:
 * @file_name: specify the path and the name of file that contains
 *   ASN.1 declarations.
 * @definitions: return the pointer to the structure created from
 *   "file_name" ASN.1 declarations.
 * @errorDescription: return the error description or an empty
 * string if success.
 *
 * Function used to start the parse algorithm.  Creates the structures
 * needed to manage the definitions included in @file_name file.
 *
 * Returns: %ASN1_SUCCESS if the file has a correct syntax and every
 *   identifier is known, %ASN1_ELEMENT_NOT_EMPTY if @definitions not
 *   %ASN1_TYPE_EMPTY, %ASN1_FILE_NOT_FOUND if an error occured while
 *   opening @file_name, %ASN1_SYNTAX_ERROR if the syntax is not
 *   correct, %ASN1_IDENTIFIER_NOT_FOUND if in the file there is an
 *   identifier that is not defined, %ASN1_NAME_TOO_LONG if in the
 *   file there is an identifier whith more than %ASN1_MAX_NAME_SIZE
 *   characters.
 **/
asn1_retCode
asn1_parser2tree(const char *file_name, ASN1_TYPE *definitions,
		 char *errorDescription){

  p_tree=ASN1_TYPE_EMPTY;

  if(*definitions != ASN1_TYPE_EMPTY)
    return ASN1_ELEMENT_NOT_EMPTY;

  *definitions=ASN1_TYPE_EMPTY;

  fileName = file_name;

  /* open the file to parse */
  file_asn1=fopen(file_name,"r");

  if(file_asn1==NULL){
    result_parse=ASN1_FILE_NOT_FOUND;
  }
  else{
    result_parse=ASN1_SUCCESS;

    lineNumber=1;
    yyparse();

    fclose(file_asn1);

    if(result_parse==ASN1_SUCCESS){ /* syntax OK */
      /* set IMPLICIT or EXPLICIT property */
      _asn1_set_default_tag(p_tree);
      /* set CONST_SET and CONST_NOT_USED */
      _asn1_type_set_config(p_tree);
      /* check the identifier definitions */
      result_parse=_asn1_check_identifier(p_tree);
      if(result_parse==ASN1_SUCCESS){ /* all identifier defined */
	/* Delete the list and keep the ASN1 structure */
	_asn1_delete_list();
	/* Convert into DER coding the value assign to INTEGER constants */
	_asn1_change_integer_value(p_tree);
	/* Expand the IDs of OBJECT IDENTIFIER constants */
	_asn1_expand_object_id(p_tree);

	*definitions=p_tree;
      }
      else /* some identifiers not defined */
	/* Delete the list and the ASN1 structure */
	_asn1_delete_list_and_nodes();
    }
    else  /* syntax error */
      /* Delete the list and the ASN1 structure */
      _asn1_delete_list_and_nodes();
  }

  if (errorDescription!=NULL)
	_asn1_create_errorDescription(result_parse,errorDescription);

  return result_parse;
}

/**
 * asn1_parser2array:
 * @inputFileName: specify the path and the name of file that
 *   contains ASN.1 declarations.
 * @outputFileName: specify the path and the name of file that will
 *   contain the C vector definition.
 * @vectorName: specify the name of the C vector.
 * @errorDescription : return the error description or an empty
 *   string if success.
 *
 * Function that generates a C structure from an ASN1 file.  Creates a
 * file containing a C vector to use to manage the definitions
 * included in @inputFileName file. If @inputFileName is
 * "/aa/bb/xx.yy" and @outputFileName is %NULL, the file created is
 * "/aa/bb/xx_asn1_tab.c".  If @vectorName is %NULL the vector name
 * will be "xx_asn1_tab".
 *
 * Returns: %ASN1_SUCCESS if the file has a correct syntax and every
 *   identifier is known, %ASN1_FILE_NOT_FOUND if an error occured
 *   while opening @inputFileName, %ASN1_SYNTAX_ERROR if the syntax is
 *   not correct, %ASN1_IDENTIFIER_NOT_FOUND if in the file there is
 *   an identifier that is not defined, %ASN1_NAME_TOO_LONG if in the
 *   file there is an identifier whith more than %ASN1_MAX_NAME_SIZE
 *   characters.
 **/
int asn1_parser2array(const char *inputFileName,const char *outputFileName,
		      const char *vectorName,char *errorDescription){
  char *file_out_name=NULL;
  char *vector_name=NULL;
  const char *char_p,*slash_p,*dot_p;

  p_tree=NULL;

  fileName = inputFileName;

  /* open the file to parse */
  file_asn1=fopen(inputFileName,"r");

  if(file_asn1==NULL)
    result_parse=ASN1_FILE_NOT_FOUND;
  else{
    result_parse=ASN1_SUCCESS;

    lineNumber=1;
    yyparse();

    fclose(file_asn1);

    if(result_parse==ASN1_SUCCESS){ /* syntax OK */
      /* set IMPLICIT or EXPLICIT property */
      _asn1_set_default_tag(p_tree);
      /* set CONST_SET and CONST_NOT_USED */
      _asn1_type_set_config(p_tree);
      /* check the identifier definitions */
      result_parse=_asn1_check_identifier(p_tree);

      if(result_parse==ASN1_SUCCESS){ /* all identifier defined */

	/* searching the last '/' and '.' in inputFileName */
	char_p=inputFileName;
	slash_p=inputFileName;
	while((char_p=strchr(char_p,'/'))){
	  char_p++;
	  slash_p=char_p;
	}

	char_p=slash_p;
	dot_p=inputFileName+strlen(inputFileName);

	while((char_p=strchr(char_p,'.'))){
	  dot_p=char_p;
	  char_p++;
	}

	if(outputFileName == NULL){
	  /* file_out_name = inputFileName + _asn1_tab.c */
	  file_out_name=(char *)malloc(dot_p-inputFileName+1+
				       strlen("_asn1_tab.c"));
	  memcpy(file_out_name,inputFileName,dot_p-inputFileName);
	  file_out_name[dot_p-inputFileName]=0;
	  strcat(file_out_name,"_asn1_tab.c");
	}
	else{
	  /* file_out_name = inputFileName */
	  file_out_name=(char *)malloc(strlen(outputFileName)+1);
	  strcpy(file_out_name,outputFileName);
	}

	if(vectorName == NULL){
	  /* vector_name = file name + _asn1_tab */
	  vector_name=(char *)malloc(dot_p-slash_p+1+
				     strlen("_asn1_tab"));
	  memcpy(vector_name,slash_p,dot_p-slash_p);
	  vector_name[dot_p-slash_p]=0;
	  strcat(vector_name,"_asn1_tab");
	}
	else{
	  /* vector_name = vectorName */
	  vector_name=(char *)malloc(strlen(vectorName)+1);
	  strcpy(vector_name,vectorName);
	}

	/* Save structure in a file */
	_asn1_create_static_structure(p_tree,
				      file_out_name,vector_name);

	free(file_out_name);
	free(vector_name);
      } /* result == OK */
    }   /* result == OK */

    /* Delete the list and the ASN1 structure */
    _asn1_delete_list_and_nodes();
  } /* inputFile exist */

  if (errorDescription!=NULL)
	_asn1_create_errorDescription(result_parse,errorDescription);

  return result_parse;
}

/*************************************************************/
/*  Function: _asn1_yyerror                                  */
/*  Description: function called when there are syntax errors*/
/*  Parameters:                                              */
/*    char *s : error description                            */
/*  Return: int                                              */
/*                                                           */
/*************************************************************/
static int _asn1_yyerror (const char *s)
{
  /* Sends the error description to the std_out */

#if 0
  printf("_asn1_yyerror:%s:%ld: %s (Last Token:'%s')\n",fileName,
	 lineNumber,s,lastToken);
#endif

  if(result_parse!=ASN1_NAME_TOO_LONG)
    result_parse=ASN1_SYNTAX_ERROR;

  return 0;
}
