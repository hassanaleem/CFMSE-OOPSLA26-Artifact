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
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "getdate.y"

/* Parse a string into an internal time stamp.

   Copyright (C) 1999, 2000, 2002, 2003, 2004, 2005, 2006, 2007 Free Software
   Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* Originally written by Steven M. Bellovin <smb@research.att.com> while
   at the University of North Carolina at Chapel Hill.  Later tweaked by
   a couple of people on Usenet.  Completely overhauled by Rich $alz
   <rsalz@bbn.com> and Jim Berets <jberets@bbn.com> in August, 1990.

   Modified by Paul Eggert <eggert@twinsun.com> in August 1999 to do
   the right thing about local DST.  Also modified by Paul Eggert
   <eggert@cs.ucla.edu> in February 2004 to support
   nanosecond-resolution time stamps, and in October 2004 to support
   TZ strings in dates.  */

/* FIXME: Check for arithmetic overflow in all cases, not just
   some of them.  */

#include <config.h>

#include "getdate.h"

#include "intprops.h"
#include "timespec.h"
#include "verify.h"

/* There's no need to extend the stack, so there's no need to involve
   alloca.  */
#define YYSTACK_USE_ALLOCA 0

/* Tell Bison how much stack space is needed.  20 should be plenty for
   this grammar, which is not right recursive.  Beware setting it too
   high, since that might cause problems on machines whose
   implementations have lame stack-overflow checking.  */
#define YYMAXDEPTH 20
#define YYINITDEPTH YYMAXDEPTH

/* Since the code of getdate.y is not included in the Emacs executable
   itself, there is no need to #define static in this file.  Even if
   the code were included in the Emacs executable, it probably
   wouldn't do any harm to #undef it here; this will only cause
   problems if we try to write to a static variable, which I don't
   think this code needs to do.  */
#ifdef emacs
# undef static
#endif

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xalloc.h"


/* ISDIGIT differs from isdigit, as follows:
   - Its arg may be any int or unsigned int; it need not be an unsigned char
     or EOF.
   - It's typically faster.
   POSIX says that only '0' through '9' are digits.  Prefer ISDIGIT to
   isdigit unless it's important to use the locale's definition
   of `digit' even when the host does not conform to POSIX.  */
#define ISDIGIT(c) ((unsigned int) (c) - '0' <= 9)

#ifndef __attribute__
# if __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 8) || __STRICT_ANSI__
#  define __attribute__(x)
# endif
#endif

#ifndef ATTRIBUTE_UNUSED
# define ATTRIBUTE_UNUSED __attribute__ ((__unused__))
#endif

/* Shift A right by B bits portably, by dividing A by 2**B and
   truncating towards minus infinity.  A and B should be free of side
   effects, and B should be in the range 0 <= B <= INT_BITS - 2, where
   INT_BITS is the number of useful bits in an int.  GNU code can
   assume that INT_BITS is at least 32.

   ISO C99 says that A >> B is implementation-defined if A < 0.  Some
   implementations (e.g., UNICOS 9.0 on a Cray Y-MP EL) don't shift
   right in the usual way when A < 0, so SHR falls back on division if
   ordinary A >> B doesn't seem to be the usual signed shift.  */
#define SHR(a, b)	\
  (-1 >> 1 == -1	\
   ? (a) >> (b)		\
   : (a) / (1 << (b)) - ((a) % (1 << (b)) < 0))

#define EPOCH_YEAR 1970
#define TM_YEAR_BASE 1900

#define HOUR(x) ((x) * 60)

/* Lots of this code assumes time_t and time_t-like values fit into
   long int.  It also assumes that signed integer overflow silently
   wraps around, but there's no portable way to check for that at
   compile-time.  */
verify (TYPE_IS_INTEGER (time_t));
verify (LONG_MIN <= TYPE_MINIMUM (time_t) && TYPE_MAXIMUM (time_t) <= LONG_MAX);

/* An integer value, and the number of digits in its textual
   representation.  */
typedef struct
{
  bool negative;
  long int value;
  size_t digits;
} textint;

/* An entry in the lexical lookup table.  */
typedef struct
{
  char const *name;
  int type;
  int value;
} table;

/* Meridian: am, pm, or 24-hour style.  */
enum { MERam, MERpm, MER24 };

enum { BILLION = 1000000000, LOG10_BILLION = 9 };

/* Relative times.  */
typedef struct
{
  /* Relative year, month, day, hour, minutes, seconds, and nanoseconds.  */
  long int year;
  long int month;
  long int day;
  long int hour;
  long int minutes;
  long int seconds;
  long int ns;
} relative_time;

#if HAVE_COMPOUND_LITERALS
# define RELATIVE_TIME_0 ((relative_time) { 0, 0, 0, 0, 0, 0, 0 })
#else
static relative_time const RELATIVE_TIME_0;
#endif

/* Information passed to and from the parser.  */
typedef struct
{
  /* The input string remaining to be parsed. */
  const char *input;

  /* N, if this is the Nth Tuesday.  */
  long int day_ordinal;

  /* Day of week; Sunday is 0.  */
  int day_number;

  /* tm_isdst flag for the local zone.  */
  int local_isdst;

  /* Time zone, in minutes east of UTC.  */
  long int time_zone;

  /* Style used for time.  */
  int meridian;

  /* Gregorian year, month, day, hour, minutes, seconds, and nanoseconds.  */
  textint year;
  long int month;
  long int day;
  long int hour;
  long int minutes;
  struct timespec seconds; /* includes nanoseconds */

  /* Relative year, month, day, hour, minutes, seconds, and nanoseconds.  */
  relative_time rel;

  /* Presence or counts of nonterminals of various flavors parsed so far.  */
  bool timespec_seen;
  bool rels_seen;
  size_t dates_seen;
  size_t days_seen;
  size_t local_zones_seen;
  size_t dsts_seen;
  size_t times_seen;
  size_t zones_seen;

  /* Table of local time zone abbrevations, terminated by a null entry.  */
  table local_time_zone_table[3];
} parser_control;

union YYSTYPE;
static int yylex (union YYSTYPE *, parser_control *);
static int yyerror (parser_control const *, char const *);
static long int time_zone_hhmm (textint, long int);

/* Extract into *PC any date and time info from a string of digits
   of the form e.g., YYYYMMDD, YYMMDD, HHMM, HH (and sometimes YYY,
   YYYY, ...).  */
static void
digits_to_date_time (parser_control *pc, textint text_int)
{
  if (pc->dates_seen && ! pc->year.digits
      && ! pc->rels_seen && (pc->times_seen || 2 < text_int.digits))
    pc->year = text_int;
  else
    {
      if (4 < text_int.digits)
	{
	  pc->dates_seen++;
	  pc->day = text_int.value % 100;
	  pc->month = (text_int.value / 100) % 100;
	  pc->year.value = text_int.value / 10000;
	  pc->year.digits = text_int.digits - 4;
	}
      else
	{
	  pc->times_seen++;
	  if (text_int.digits <= 2)
	    {
	      pc->hour = text_int.value;
	      pc->minutes = 0;
	    }
	  else
	    {
	      pc->hour = text_int.value / 100;
	      pc->minutes = text_int.value % 100;
	    }
	  pc->seconds.tv_sec = 0;
	  pc->seconds.tv_nsec = 0;
	  pc->meridian = MER24;
	}
    }
}


#line 321 "getdate.c"

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
extern int yydebug;
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
    tAGO = 258,                    /* tAGO  */
    tDST = 259,                    /* tDST  */
    tYEAR_UNIT = 260,              /* tYEAR_UNIT  */
    tMONTH_UNIT = 261,             /* tMONTH_UNIT  */
    tHOUR_UNIT = 262,              /* tHOUR_UNIT  */
    tMINUTE_UNIT = 263,            /* tMINUTE_UNIT  */
    tSEC_UNIT = 264,               /* tSEC_UNIT  */
    tDAY_UNIT = 265,               /* tDAY_UNIT  */
    tDAY = 266,                    /* tDAY  */
    tDAYZONE = 267,                /* tDAYZONE  */
    tLOCAL_ZONE = 268,             /* tLOCAL_ZONE  */
    tMERIDIAN = 269,               /* tMERIDIAN  */
    tMONTH = 270,                  /* tMONTH  */
    tORDINAL = 271,                /* tORDINAL  */
    tZONE = 272,                   /* tZONE  */
    tSNUMBER = 273,                /* tSNUMBER  */
    tUNUMBER = 274,                /* tUNUMBER  */
    tSDECIMAL_NUMBER = 275,        /* tSDECIMAL_NUMBER  */
    tUDECIMAL_NUMBER = 276         /* tUDECIMAL_NUMBER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define tAGO 258
#define tDST 259
#define tYEAR_UNIT 260
#define tMONTH_UNIT 261
#define tHOUR_UNIT 262
#define tMINUTE_UNIT 263
#define tSEC_UNIT 264
#define tDAY_UNIT 265
#define tDAY 266
#define tDAYZONE 267
#define tLOCAL_ZONE 268
#define tMERIDIAN 269
#define tMONTH 270
#define tORDINAL 271
#define tZONE 272
#define tSNUMBER 273
#define tUNUMBER 274
#define tSDECIMAL_NUMBER 275
#define tUDECIMAL_NUMBER 276

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 261 "getdate.y"

  long int intval;
  textint textintval;
  struct timespec timespec;
  relative_time rel;

#line 420 "getdate.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int yyparse (parser_control *pc);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_tAGO = 3,                       /* tAGO  */
  YYSYMBOL_tDST = 4,                       /* tDST  */
  YYSYMBOL_tYEAR_UNIT = 5,                 /* tYEAR_UNIT  */
  YYSYMBOL_tMONTH_UNIT = 6,                /* tMONTH_UNIT  */
  YYSYMBOL_tHOUR_UNIT = 7,                 /* tHOUR_UNIT  */
  YYSYMBOL_tMINUTE_UNIT = 8,               /* tMINUTE_UNIT  */
  YYSYMBOL_tSEC_UNIT = 9,                  /* tSEC_UNIT  */
  YYSYMBOL_tDAY_UNIT = 10,                 /* tDAY_UNIT  */
  YYSYMBOL_tDAY = 11,                      /* tDAY  */
  YYSYMBOL_tDAYZONE = 12,                  /* tDAYZONE  */
  YYSYMBOL_tLOCAL_ZONE = 13,               /* tLOCAL_ZONE  */
  YYSYMBOL_tMERIDIAN = 14,                 /* tMERIDIAN  */
  YYSYMBOL_tMONTH = 15,                    /* tMONTH  */
  YYSYMBOL_tORDINAL = 16,                  /* tORDINAL  */
  YYSYMBOL_tZONE = 17,                     /* tZONE  */
  YYSYMBOL_tSNUMBER = 18,                  /* tSNUMBER  */
  YYSYMBOL_tUNUMBER = 19,                  /* tUNUMBER  */
  YYSYMBOL_tSDECIMAL_NUMBER = 20,          /* tSDECIMAL_NUMBER  */
  YYSYMBOL_tUDECIMAL_NUMBER = 21,          /* tUDECIMAL_NUMBER  */
  YYSYMBOL_22_ = 22,                       /* '@'  */
  YYSYMBOL_23_ = 23,                       /* ':'  */
  YYSYMBOL_24_ = 24,                       /* ','  */
  YYSYMBOL_25_ = 25,                       /* '/'  */
  YYSYMBOL_YYACCEPT = 26,                  /* $accept  */
  YYSYMBOL_spec = 27,                      /* spec  */
  YYSYMBOL_timespec = 28,                  /* timespec  */
  YYSYMBOL_items = 29,                     /* items  */
  YYSYMBOL_item = 30,                      /* item  */
  YYSYMBOL_time = 31,                      /* time  */
  YYSYMBOL_local_zone = 32,                /* local_zone  */
  YYSYMBOL_zone = 33,                      /* zone  */
  YYSYMBOL_day = 34,                       /* day  */
  YYSYMBOL_date = 35,                      /* date  */
  YYSYMBOL_rel = 36,                       /* rel  */
  YYSYMBOL_relunit = 37,                   /* relunit  */
  YYSYMBOL_relunit_snumber = 38,           /* relunit_snumber  */
  YYSYMBOL_seconds = 39,                   /* seconds  */
  YYSYMBOL_signed_seconds = 40,            /* signed_seconds  */
  YYSYMBOL_unsigned_seconds = 41,          /* unsigned_seconds  */
  YYSYMBOL_number = 42,                    /* number  */
  YYSYMBOL_hybrid = 43,                    /* hybrid  */
  YYSYMBOL_o_colon_minutes = 44,           /* o_colon_minutes  */
  YYSYMBOL_o_merid = 45                    /* o_merid  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   96

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  26
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  98

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   276


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
       2,     2,     2,     2,    24,     2,     2,    25,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    23,     2,
       2,     2,     2,     2,    22,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   287,   287,   288,   292,   299,   301,   305,   307,   309,
     311,   313,   315,   317,   318,   322,   330,   338,   348,   355,
     367,   372,   380,   382,   392,   394,   396,   401,   406,   411,
     416,   424,   429,   449,   456,   464,   472,   477,   483,   488,
     497,   507,   520,   522,   524,   526,   528,   530,   532,   534,
     536,   538,   540,   542,   544,   546,   548,   550,   552,   554,
     556,   558,   560,   564,   566,   568,   570,   572,   574,   578,
     578,   581,   582,   587,   588,   593,   598,   616,   617,   623,
     624
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
  "\"end of file\"", "error", "\"invalid token\"", "tAGO", "tDST",
  "tYEAR_UNIT", "tMONTH_UNIT", "tHOUR_UNIT", "tMINUTE_UNIT", "tSEC_UNIT",
  "tDAY_UNIT", "tDAY", "tDAYZONE", "tLOCAL_ZONE", "tMERIDIAN", "tMONTH",
  "tORDINAL", "tZONE", "tSNUMBER", "tUNUMBER", "tSDECIMAL_NUMBER",
  "tUDECIMAL_NUMBER", "'@'", "':'", "','", "'/'", "$accept", "spec",
  "timespec", "items", "item", "time", "local_zone", "zone", "day", "date",
  "rel", "relunit", "relunit_snumber", "seconds", "signed_seconds",
  "unsigned_seconds", "number", "hybrid", "o_colon_minutes", "o_merid", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-81)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -10,    54,    70,   -81,    25,   -81,   -81,   -81,   -81,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,    55,
     -81,    74,    50,    48,    10,    56,    -5,    71,    72,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,    79,   -81,   -81,   -81,
     -81,   -81,    65,    60,   -81,   -81,   -81,   -81,   -81,   -81,
     -81,   -81,    16,   -81,   -81,   -81,   -81,   -81,   -81,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,    58,    42,
      66,    67,   -81,   -81,   -81,   -81,   -81,    68,    69,   -81,
     -81,   -81,   -81,    -7,    64,   -81,   -81,   -81,    73,    -2,
     -81,    75,   -81,    53,   -81,    73,   -81,   -81
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,     0,     2,     3,    72,    74,    71,    73,     4,
      69,    70,     1,    44,    47,    53,    56,    61,    50,    27,
      25,    20,     0,     0,    22,     0,    75,     0,     0,     6,
       7,     8,     9,    11,    10,    12,    41,    62,    13,    14,
      28,    21,     0,    36,    42,    45,    51,    54,    57,    48,
      29,    26,    77,    23,    63,    64,    66,    67,    68,    65,
      43,    46,    52,    55,    58,    49,    30,    15,    38,     0,
       0,     0,    76,    59,    60,    40,    35,     0,     0,    24,
      34,    39,    33,    79,    31,    37,    78,    80,    77,     0,
      16,     0,    17,    79,    32,    77,    18,    19
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,
     -81,   -81,     3,   -81,   -81,     1,   -81,   -81,   -80,    -1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     4,    29,    30,    31,    32,    33,    34,
      35,    36,    37,     9,    10,    11,    38,    39,    79,    90
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      60,    61,    62,    63,    64,    65,    66,    87,    92,    67,
      68,    88,     1,    69,    51,    97,    89,     6,    70,     8,
      71,    54,    55,    56,    57,    58,    59,    53,    52,    72,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    78,
      22,    23,    24,    25,    26,    27,    28,    54,    55,    56,
      57,    58,    59,    44,    45,    46,    47,    48,    49,    50,
      82,    54,    55,    56,    57,    58,    59,    87,    42,    43,
      12,    95,     5,     6,     7,     8,    80,    81,    41,    40,
      73,    74,    75,    76,    77,    83,    84,    85,    86,    91,
      93,     0,    96,     0,    94,     0,    78
};

static const yytype_int8 yycheck[] =
{
       5,     6,     7,     8,     9,    10,    11,    14,    88,    14,
      15,    18,    22,    18,     4,    95,    23,    19,    23,    21,
      25,     5,     6,     7,     8,     9,    10,    24,    18,    26,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    23,
      15,    16,    17,    18,    19,    20,    21,     5,     6,     7,
       8,     9,    10,     5,     6,     7,     8,     9,    10,    11,
      18,     5,     6,     7,     8,     9,    10,    14,    18,    19,
       0,    18,    18,    19,    20,    21,    18,    19,     4,    24,
       9,     9,     3,    18,    24,    19,    19,    19,    19,    25,
      89,    -1,    93,    -1,    19,    -1,    23
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    22,    27,    28,    29,    18,    19,    20,    21,    39,
      40,    41,     0,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    15,    16,    17,    18,    19,    20,    21,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    42,    43,
      24,     4,    18,    19,     5,     6,     7,     8,     9,    10,
      11,     4,    18,    38,     5,     6,     7,     8,     9,    10,
       5,     6,     7,     8,     9,    10,    11,    14,    15,    18,
      23,    25,    38,     9,     9,     3,    18,    24,    23,    44,
      18,    19,    18,    19,    19,    19,    19,    14,    18,    23,
      45,    25,    44,    41,    19,    18,    45,    44
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    26,    27,    27,    28,    29,    29,    30,    30,    30,
      30,    30,    30,    30,    30,    31,    31,    31,    31,    31,
      32,    32,    33,    33,    33,    33,    33,    34,    34,    34,
      34,    35,    35,    35,    35,    35,    35,    35,    35,    35,
      36,    36,    37,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    37,    38,    38,    38,    38,    38,    38,    39,
      39,    40,    40,    41,    41,    42,    43,    44,    44,    45,
      45
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     0,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     4,     5,     6,     7,
       1,     2,     1,     2,     3,     1,     2,     1,     2,     2,
       2,     3,     5,     3,     3,     3,     2,     4,     2,     3,
       2,     1,     2,     2,     1,     2,     2,     1,     2,     2,
       1,     2,     2,     1,     2,     2,     1,     2,     2,     2,
       2,     1,     1,     2,     2,     2,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     2,     0,     2,     0,
       1
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
        yyerror (pc, YY_("syntax error: cannot back up")); \
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
                  Kind, Value, pc); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, parser_control *pc)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (pc);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, parser_control *pc)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, pc);
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
                 int yyrule, parser_control *pc)
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
                       &yyvsp[(yyi + 1) - (yynrhs)], pc);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, pc); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, parser_control *pc)
{
  YY_USE (yyvaluep);
  YY_USE (pc);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (parser_control *pc)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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
      yychar = yylex (&yylval, pc);
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
  case 4: /* timespec: '@' seconds  */
#line 293 "getdate.y"
      {
	pc->seconds = (yyvsp[0].timespec);
	pc->timespec_seen = true;
      }
#line 1519 "getdate.c"
    break;

  case 7: /* item: time  */
#line 306 "getdate.y"
      { pc->times_seen++; }
#line 1525 "getdate.c"
    break;

  case 8: /* item: local_zone  */
#line 308 "getdate.y"
      { pc->local_zones_seen++; }
#line 1531 "getdate.c"
    break;

  case 9: /* item: zone  */
#line 310 "getdate.y"
      { pc->zones_seen++; }
#line 1537 "getdate.c"
    break;

  case 10: /* item: date  */
#line 312 "getdate.y"
      { pc->dates_seen++; }
#line 1543 "getdate.c"
    break;

  case 11: /* item: day  */
#line 314 "getdate.y"
      { pc->days_seen++; }
#line 1549 "getdate.c"
    break;

  case 12: /* item: rel  */
#line 316 "getdate.y"
      { pc->rels_seen = true; }
#line 1555 "getdate.c"
    break;

  case 15: /* time: tUNUMBER tMERIDIAN  */
#line 323 "getdate.y"
      {
	pc->hour = (yyvsp[-1].textintval).value;
	pc->minutes = 0;
	pc->seconds.tv_sec = 0;
	pc->seconds.tv_nsec = 0;
	pc->meridian = (yyvsp[0].intval);
      }
#line 1567 "getdate.c"
    break;

  case 16: /* time: tUNUMBER ':' tUNUMBER o_merid  */
#line 331 "getdate.y"
      {
	pc->hour = (yyvsp[-3].textintval).value;
	pc->minutes = (yyvsp[-1].textintval).value;
	pc->seconds.tv_sec = 0;
	pc->seconds.tv_nsec = 0;
	pc->meridian = (yyvsp[0].intval);
      }
#line 1579 "getdate.c"
    break;

  case 17: /* time: tUNUMBER ':' tUNUMBER tSNUMBER o_colon_minutes  */
#line 339 "getdate.y"
      {
	pc->hour = (yyvsp[-4].textintval).value;
	pc->minutes = (yyvsp[-2].textintval).value;
	pc->seconds.tv_sec = 0;
	pc->seconds.tv_nsec = 0;
	pc->meridian = MER24;
	pc->zones_seen++;
	pc->time_zone = time_zone_hhmm ((yyvsp[-1].textintval), (yyvsp[0].intval));
      }
#line 1593 "getdate.c"
    break;

  case 18: /* time: tUNUMBER ':' tUNUMBER ':' unsigned_seconds o_merid  */
#line 349 "getdate.y"
      {
	pc->hour = (yyvsp[-5].textintval).value;
	pc->minutes = (yyvsp[-3].textintval).value;
	pc->seconds = (yyvsp[-1].timespec);
	pc->meridian = (yyvsp[0].intval);
      }
#line 1604 "getdate.c"
    break;

  case 19: /* time: tUNUMBER ':' tUNUMBER ':' unsigned_seconds tSNUMBER o_colon_minutes  */
#line 356 "getdate.y"
      {
	pc->hour = (yyvsp[-6].textintval).value;
	pc->minutes = (yyvsp[-4].textintval).value;
	pc->seconds = (yyvsp[-2].timespec);
	pc->meridian = MER24;
	pc->zones_seen++;
	pc->time_zone = time_zone_hhmm ((yyvsp[-1].textintval), (yyvsp[0].intval));
      }
#line 1617 "getdate.c"
    break;

  case 20: /* local_zone: tLOCAL_ZONE  */
#line 368 "getdate.y"
      {
	pc->local_isdst = (yyvsp[0].intval);
	pc->dsts_seen += (0 < (yyvsp[0].intval));
      }
#line 1626 "getdate.c"
    break;

  case 21: /* local_zone: tLOCAL_ZONE tDST  */
#line 373 "getdate.y"
      {
	pc->local_isdst = 1;
	pc->dsts_seen += (0 < (yyvsp[-1].intval)) + 1;
      }
#line 1635 "getdate.c"
    break;

  case 22: /* zone: tZONE  */
#line 381 "getdate.y"
      { pc->time_zone = (yyvsp[0].intval); }
#line 1641 "getdate.c"
    break;

  case 23: /* zone: tZONE relunit_snumber  */
#line 383 "getdate.y"
      { pc->time_zone = (yyvsp[-1].intval);
	pc->rel.ns += (yyvsp[0].rel).ns;
	pc->rel.seconds += (yyvsp[0].rel).seconds;
	pc->rel.minutes += (yyvsp[0].rel).minutes;
	pc->rel.hour += (yyvsp[0].rel).hour;
	pc->rel.day += (yyvsp[0].rel).day;
	pc->rel.month += (yyvsp[0].rel).month;
	pc->rel.year += (yyvsp[0].rel).year;
        pc->rels_seen = true; }
#line 1655 "getdate.c"
    break;

  case 24: /* zone: tZONE tSNUMBER o_colon_minutes  */
#line 393 "getdate.y"
      { pc->time_zone = (yyvsp[-2].intval) + time_zone_hhmm ((yyvsp[-1].textintval), (yyvsp[0].intval)); }
#line 1661 "getdate.c"
    break;

  case 25: /* zone: tDAYZONE  */
#line 395 "getdate.y"
      { pc->time_zone = (yyvsp[0].intval) + 60; }
#line 1667 "getdate.c"
    break;

  case 26: /* zone: tZONE tDST  */
#line 397 "getdate.y"
      { pc->time_zone = (yyvsp[-1].intval) + 60; }
#line 1673 "getdate.c"
    break;

  case 27: /* day: tDAY  */
#line 402 "getdate.y"
      {
	pc->day_ordinal = 1;
	pc->day_number = (yyvsp[0].intval);
      }
#line 1682 "getdate.c"
    break;

  case 28: /* day: tDAY ','  */
#line 407 "getdate.y"
      {
	pc->day_ordinal = 1;
	pc->day_number = (yyvsp[-1].intval);
      }
#line 1691 "getdate.c"
    break;

  case 29: /* day: tORDINAL tDAY  */
#line 412 "getdate.y"
      {
	pc->day_ordinal = (yyvsp[-1].intval);
	pc->day_number = (yyvsp[0].intval);
      }
#line 1700 "getdate.c"
    break;

  case 30: /* day: tUNUMBER tDAY  */
#line 417 "getdate.y"
      {
	pc->day_ordinal = (yyvsp[-1].textintval).value;
	pc->day_number = (yyvsp[0].intval);
      }
#line 1709 "getdate.c"
    break;

  case 31: /* date: tUNUMBER '/' tUNUMBER  */
#line 425 "getdate.y"
      {
	pc->month = (yyvsp[-2].textintval).value;
	pc->day = (yyvsp[0].textintval).value;
      }
#line 1718 "getdate.c"
    break;

  case 32: /* date: tUNUMBER '/' tUNUMBER '/' tUNUMBER  */
#line 430 "getdate.y"
      {
	/* Interpret as YYYY/MM/DD if the first value has 4 or more digits,
	   otherwise as MM/DD/YY.
	   The goal in recognizing YYYY/MM/DD is solely to support legacy
	   machine-generated dates like those in an RCS log listing.  If
	   you want portability, use the ISO 8601 format.  */
	if (4 <= (yyvsp[-4].textintval).digits)
	  {
	    pc->year = (yyvsp[-4].textintval);
	    pc->month = (yyvsp[-2].textintval).value;
	    pc->day = (yyvsp[0].textintval).value;
	  }
	else
	  {
	    pc->month = (yyvsp[-4].textintval).value;
	    pc->day = (yyvsp[-2].textintval).value;
	    pc->year = (yyvsp[0].textintval);
	  }
      }
#line 1742 "getdate.c"
    break;

  case 33: /* date: tUNUMBER tSNUMBER tSNUMBER  */
#line 450 "getdate.y"
      {
	/* ISO 8601 format.  YYYY-MM-DD.  */
	pc->year = (yyvsp[-2].textintval);
	pc->month = -(yyvsp[-1].textintval).value;
	pc->day = -(yyvsp[0].textintval).value;
      }
#line 1753 "getdate.c"
    break;

  case 34: /* date: tUNUMBER tMONTH tSNUMBER  */
#line 457 "getdate.y"
      {
	/* e.g. 17-JUN-1992.  */
	pc->day = (yyvsp[-2].textintval).value;
	pc->month = (yyvsp[-1].intval);
	pc->year.value = -(yyvsp[0].textintval).value;
	pc->year.digits = (yyvsp[0].textintval).digits;
      }
#line 1765 "getdate.c"
    break;

  case 35: /* date: tMONTH tSNUMBER tSNUMBER  */
#line 465 "getdate.y"
      {
	/* e.g. JUN-17-1992.  */
	pc->month = (yyvsp[-2].intval);
	pc->day = -(yyvsp[-1].textintval).value;
	pc->year.value = -(yyvsp[0].textintval).value;
	pc->year.digits = (yyvsp[0].textintval).digits;
      }
#line 1777 "getdate.c"
    break;

  case 36: /* date: tMONTH tUNUMBER  */
#line 473 "getdate.y"
      {
	pc->month = (yyvsp[-1].intval);
	pc->day = (yyvsp[0].textintval).value;
      }
#line 1786 "getdate.c"
    break;

  case 37: /* date: tMONTH tUNUMBER ',' tUNUMBER  */
#line 478 "getdate.y"
      {
	pc->month = (yyvsp[-3].intval);
	pc->day = (yyvsp[-2].textintval).value;
	pc->year = (yyvsp[0].textintval);
      }
#line 1796 "getdate.c"
    break;

  case 38: /* date: tUNUMBER tMONTH  */
#line 484 "getdate.y"
      {
	pc->day = (yyvsp[-1].textintval).value;
	pc->month = (yyvsp[0].intval);
      }
#line 1805 "getdate.c"
    break;

  case 39: /* date: tUNUMBER tMONTH tUNUMBER  */
#line 489 "getdate.y"
      {
	pc->day = (yyvsp[-2].textintval).value;
	pc->month = (yyvsp[-1].intval);
	pc->year = (yyvsp[0].textintval);
      }
#line 1815 "getdate.c"
    break;

  case 40: /* rel: relunit tAGO  */
#line 498 "getdate.y"
      {
	pc->rel.ns -= (yyvsp[-1].rel).ns;
	pc->rel.seconds -= (yyvsp[-1].rel).seconds;
	pc->rel.minutes -= (yyvsp[-1].rel).minutes;
	pc->rel.hour -= (yyvsp[-1].rel).hour;
	pc->rel.day -= (yyvsp[-1].rel).day;
	pc->rel.month -= (yyvsp[-1].rel).month;
	pc->rel.year -= (yyvsp[-1].rel).year;
      }
#line 1829 "getdate.c"
    break;

  case 41: /* rel: relunit  */
#line 508 "getdate.y"
      {
	pc->rel.ns += (yyvsp[0].rel).ns;
	pc->rel.seconds += (yyvsp[0].rel).seconds;
	pc->rel.minutes += (yyvsp[0].rel).minutes;
	pc->rel.hour += (yyvsp[0].rel).hour;
	pc->rel.day += (yyvsp[0].rel).day;
	pc->rel.month += (yyvsp[0].rel).month;
	pc->rel.year += (yyvsp[0].rel).year;
      }
#line 1843 "getdate.c"
    break;

  case 42: /* relunit: tORDINAL tYEAR_UNIT  */
#line 521 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).year = (yyvsp[-1].intval); }
#line 1849 "getdate.c"
    break;

  case 43: /* relunit: tUNUMBER tYEAR_UNIT  */
#line 523 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).year = (yyvsp[-1].textintval).value; }
#line 1855 "getdate.c"
    break;

  case 44: /* relunit: tYEAR_UNIT  */
#line 525 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).year = 1; }
#line 1861 "getdate.c"
    break;

  case 45: /* relunit: tORDINAL tMONTH_UNIT  */
#line 527 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).month = (yyvsp[-1].intval); }
#line 1867 "getdate.c"
    break;

  case 46: /* relunit: tUNUMBER tMONTH_UNIT  */
#line 529 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).month = (yyvsp[-1].textintval).value; }
#line 1873 "getdate.c"
    break;

  case 47: /* relunit: tMONTH_UNIT  */
#line 531 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).month = 1; }
#line 1879 "getdate.c"
    break;

  case 48: /* relunit: tORDINAL tDAY_UNIT  */
#line 533 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).day = (yyvsp[-1].intval) * (yyvsp[0].intval); }
#line 1885 "getdate.c"
    break;

  case 49: /* relunit: tUNUMBER tDAY_UNIT  */
#line 535 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).day = (yyvsp[-1].textintval).value * (yyvsp[0].intval); }
#line 1891 "getdate.c"
    break;

  case 50: /* relunit: tDAY_UNIT  */
#line 537 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).day = (yyvsp[0].intval); }
#line 1897 "getdate.c"
    break;

  case 51: /* relunit: tORDINAL tHOUR_UNIT  */
#line 539 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).hour = (yyvsp[-1].intval); }
#line 1903 "getdate.c"
    break;

  case 52: /* relunit: tUNUMBER tHOUR_UNIT  */
#line 541 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).hour = (yyvsp[-1].textintval).value; }
#line 1909 "getdate.c"
    break;

  case 53: /* relunit: tHOUR_UNIT  */
#line 543 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).hour = 1; }
#line 1915 "getdate.c"
    break;

  case 54: /* relunit: tORDINAL tMINUTE_UNIT  */
#line 545 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).minutes = (yyvsp[-1].intval); }
#line 1921 "getdate.c"
    break;

  case 55: /* relunit: tUNUMBER tMINUTE_UNIT  */
#line 547 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).minutes = (yyvsp[-1].textintval).value; }
#line 1927 "getdate.c"
    break;

  case 56: /* relunit: tMINUTE_UNIT  */
#line 549 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).minutes = 1; }
#line 1933 "getdate.c"
    break;

  case 57: /* relunit: tORDINAL tSEC_UNIT  */
#line 551 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).seconds = (yyvsp[-1].intval); }
#line 1939 "getdate.c"
    break;

  case 58: /* relunit: tUNUMBER tSEC_UNIT  */
#line 553 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).seconds = (yyvsp[-1].textintval).value; }
#line 1945 "getdate.c"
    break;

  case 59: /* relunit: tSDECIMAL_NUMBER tSEC_UNIT  */
#line 555 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).seconds = (yyvsp[-1].timespec).tv_sec; (yyval.rel).ns = (yyvsp[-1].timespec).tv_nsec; }
#line 1951 "getdate.c"
    break;

  case 60: /* relunit: tUDECIMAL_NUMBER tSEC_UNIT  */
#line 557 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).seconds = (yyvsp[-1].timespec).tv_sec; (yyval.rel).ns = (yyvsp[-1].timespec).tv_nsec; }
#line 1957 "getdate.c"
    break;

  case 61: /* relunit: tSEC_UNIT  */
#line 559 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).seconds = 1; }
#line 1963 "getdate.c"
    break;

  case 63: /* relunit_snumber: tSNUMBER tYEAR_UNIT  */
#line 565 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).year = (yyvsp[-1].textintval).value; }
#line 1969 "getdate.c"
    break;

  case 64: /* relunit_snumber: tSNUMBER tMONTH_UNIT  */
#line 567 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).month = (yyvsp[-1].textintval).value; }
#line 1975 "getdate.c"
    break;

  case 65: /* relunit_snumber: tSNUMBER tDAY_UNIT  */
#line 569 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).day = (yyvsp[-1].textintval).value * (yyvsp[0].intval); }
#line 1981 "getdate.c"
    break;

  case 66: /* relunit_snumber: tSNUMBER tHOUR_UNIT  */
#line 571 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).hour = (yyvsp[-1].textintval).value; }
#line 1987 "getdate.c"
    break;

  case 67: /* relunit_snumber: tSNUMBER tMINUTE_UNIT  */
#line 573 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).minutes = (yyvsp[-1].textintval).value; }
#line 1993 "getdate.c"
    break;

  case 68: /* relunit_snumber: tSNUMBER tSEC_UNIT  */
#line 575 "getdate.y"
      { (yyval.rel) = RELATIVE_TIME_0; (yyval.rel).seconds = (yyvsp[-1].textintval).value; }
#line 1999 "getdate.c"
    break;

  case 72: /* signed_seconds: tSNUMBER  */
#line 583 "getdate.y"
      { (yyval.timespec).tv_sec = (yyvsp[0].textintval).value; (yyval.timespec).tv_nsec = 0; }
#line 2005 "getdate.c"
    break;

  case 74: /* unsigned_seconds: tUNUMBER  */
#line 589 "getdate.y"
      { (yyval.timespec).tv_sec = (yyvsp[0].textintval).value; (yyval.timespec).tv_nsec = 0; }
#line 2011 "getdate.c"
    break;

  case 75: /* number: tUNUMBER  */
#line 594 "getdate.y"
      { digits_to_date_time (pc, (yyvsp[0].textintval)); }
#line 2017 "getdate.c"
    break;

  case 76: /* hybrid: tUNUMBER relunit_snumber  */
#line 599 "getdate.y"
      {
	/* Hybrid all-digit and relative offset, so that we accept e.g.,
	   "YYYYMMDD +N days" as well as "YYYYMMDD N days".  */
	digits_to_date_time (pc, (yyvsp[-1].textintval));
	pc->rel.ns += (yyvsp[0].rel).ns;
	pc->rel.seconds += (yyvsp[0].rel).seconds;
	pc->rel.minutes += (yyvsp[0].rel).minutes;
	pc->rel.hour += (yyvsp[0].rel).hour;
	pc->rel.day += (yyvsp[0].rel).day;
	pc->rel.month += (yyvsp[0].rel).month;
	pc->rel.year += (yyvsp[0].rel).year;
	pc->rels_seen = true;
      }
#line 2035 "getdate.c"
    break;

  case 77: /* o_colon_minutes: %empty  */
#line 616 "getdate.y"
      { (yyval.intval) = -1; }
#line 2041 "getdate.c"
    break;

  case 78: /* o_colon_minutes: ':' tUNUMBER  */
#line 618 "getdate.y"
      { (yyval.intval) = (yyvsp[0].textintval).value; }
#line 2047 "getdate.c"
    break;

  case 79: /* o_merid: %empty  */
#line 623 "getdate.y"
      { (yyval.intval) = MER24; }
#line 2053 "getdate.c"
    break;

  case 80: /* o_merid: tMERIDIAN  */
#line 625 "getdate.y"
      { (yyval.intval) = (yyvsp[0].intval); }
#line 2059 "getdate.c"
    break;


#line 2063 "getdate.c"

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
      yyerror (pc, YY_("syntax error"));
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
                      yytoken, &yylval, pc);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, pc);
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
  yyerror (pc, YY_("memory exhausted"));
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
                  yytoken, &yylval, pc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, pc);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 628 "getdate.y"


static table const meridian_table[] =
{
  { "AM",   tMERIDIAN, MERam },
  { "A.M.", tMERIDIAN, MERam },
  { "PM",   tMERIDIAN, MERpm },
  { "P.M.", tMERIDIAN, MERpm },
  { NULL, 0, 0 }
};

static table const dst_table[] =
{
  { "DST", tDST, 0 }
};

static table const month_and_day_table[] =
{
  { "JANUARY",	tMONTH,	 1 },
  { "FEBRUARY",	tMONTH,	 2 },
  { "MARCH",	tMONTH,	 3 },
  { "APRIL",	tMONTH,	 4 },
  { "MAY",	tMONTH,	 5 },
  { "JUNE",	tMONTH,	 6 },
  { "JULY",	tMONTH,	 7 },
  { "AUGUST",	tMONTH,	 8 },
  { "SEPTEMBER",tMONTH,	 9 },
  { "SEPT",	tMONTH,	 9 },
  { "OCTOBER",	tMONTH,	10 },
  { "NOVEMBER",	tMONTH,	11 },
  { "DECEMBER",	tMONTH,	12 },
  { "SUNDAY",	tDAY,	 0 },
  { "MONDAY",	tDAY,	 1 },
  { "TUESDAY",	tDAY,	 2 },
  { "TUES",	tDAY,	 2 },
  { "WEDNESDAY",tDAY,	 3 },
  { "WEDNES",	tDAY,	 3 },
  { "THURSDAY",	tDAY,	 4 },
  { "THUR",	tDAY,	 4 },
  { "THURS",	tDAY,	 4 },
  { "FRIDAY",	tDAY,	 5 },
  { "SATURDAY",	tDAY,	 6 },
  { NULL, 0, 0 }
};

static table const time_units_table[] =
{
  { "YEAR",	tYEAR_UNIT,	 1 },
  { "MONTH",	tMONTH_UNIT,	 1 },
  { "FORTNIGHT",tDAY_UNIT,	14 },
  { "WEEK",	tDAY_UNIT,	 7 },
  { "DAY",	tDAY_UNIT,	 1 },
  { "HOUR",	tHOUR_UNIT,	 1 },
  { "MINUTE",	tMINUTE_UNIT,	 1 },
  { "MIN",	tMINUTE_UNIT,	 1 },
  { "SECOND",	tSEC_UNIT,	 1 },
  { "SEC",	tSEC_UNIT,	 1 },
  { NULL, 0, 0 }
};

/* Assorted relative-time words. */
static table const relative_time_table[] =
{
  { "TOMORROW",	tDAY_UNIT,	 1 },
  { "YESTERDAY",tDAY_UNIT,	-1 },
  { "TODAY",	tDAY_UNIT,	 0 },
  { "NOW",	tDAY_UNIT,	 0 },
  { "LAST",	tORDINAL,	-1 },
  { "THIS",	tORDINAL,	 0 },
  { "NEXT",	tORDINAL,	 1 },
  { "FIRST",	tORDINAL,	 1 },
/*{ "SECOND",	tORDINAL,	 2 }, */
  { "THIRD",	tORDINAL,	 3 },
  { "FOURTH",	tORDINAL,	 4 },
  { "FIFTH",	tORDINAL,	 5 },
  { "SIXTH",	tORDINAL,	 6 },
  { "SEVENTH",	tORDINAL,	 7 },
  { "EIGHTH",	tORDINAL,	 8 },
  { "NINTH",	tORDINAL,	 9 },
  { "TENTH",	tORDINAL,	10 },
  { "ELEVENTH",	tORDINAL,	11 },
  { "TWELFTH",	tORDINAL,	12 },
  { "AGO",	tAGO,		 1 },
  { NULL, 0, 0 }
};

/* The universal time zone table.  These labels can be used even for
   time stamps that would not otherwise be valid, e.g., GMT time
   stamps in London during summer.  */
static table const universal_time_zone_table[] =
{
  { "GMT",	tZONE,     HOUR ( 0) },	/* Greenwich Mean */
  { "UT",	tZONE,     HOUR ( 0) },	/* Universal (Coordinated) */
  { "UTC",	tZONE,     HOUR ( 0) },
  { NULL, 0, 0 }
};

/* The time zone table.  This table is necessarily incomplete, as time
   zone abbreviations are ambiguous; e.g. Australians interpret "EST"
   as Eastern time in Australia, not as US Eastern Standard Time.
   You cannot rely on getdate to handle arbitrary time zone
   abbreviations; use numeric abbreviations like `-0500' instead.  */
static table const time_zone_table[] =
{
  { "WET",	tZONE,     HOUR ( 0) },	/* Western European */
  { "WEST",	tDAYZONE,  HOUR ( 0) },	/* Western European Summer */
  { "BST",	tDAYZONE,  HOUR ( 0) },	/* British Summer */
  { "ART",	tZONE,	  -HOUR ( 3) },	/* Argentina */
  { "BRT",	tZONE,	  -HOUR ( 3) },	/* Brazil */
  { "BRST",	tDAYZONE, -HOUR ( 3) },	/* Brazil Summer */
  { "NST",	tZONE,	 -(HOUR ( 3) + 30) },	/* Newfoundland Standard */
  { "NDT",	tDAYZONE,-(HOUR ( 3) + 30) },	/* Newfoundland Daylight */
  { "AST",	tZONE,    -HOUR ( 4) },	/* Atlantic Standard */
  { "ADT",	tDAYZONE, -HOUR ( 4) },	/* Atlantic Daylight */
  { "CLT",	tZONE,    -HOUR ( 4) },	/* Chile */
  { "CLST",	tDAYZONE, -HOUR ( 4) },	/* Chile Summer */
  { "EST",	tZONE,    -HOUR ( 5) },	/* Eastern Standard */
  { "EDT",	tDAYZONE, -HOUR ( 5) },	/* Eastern Daylight */
  { "CST",	tZONE,    -HOUR ( 6) },	/* Central Standard */
  { "CDT",	tDAYZONE, -HOUR ( 6) },	/* Central Daylight */
  { "MST",	tZONE,    -HOUR ( 7) },	/* Mountain Standard */
  { "MDT",	tDAYZONE, -HOUR ( 7) },	/* Mountain Daylight */
  { "PST",	tZONE,    -HOUR ( 8) },	/* Pacific Standard */
  { "PDT",	tDAYZONE, -HOUR ( 8) },	/* Pacific Daylight */
  { "AKST",	tZONE,    -HOUR ( 9) },	/* Alaska Standard */
  { "AKDT",	tDAYZONE, -HOUR ( 9) },	/* Alaska Daylight */
  { "HST",	tZONE,    -HOUR (10) },	/* Hawaii Standard */
  { "HAST",	tZONE,	  -HOUR (10) },	/* Hawaii-Aleutian Standard */
  { "HADT",	tDAYZONE, -HOUR (10) },	/* Hawaii-Aleutian Daylight */
  { "SST",	tZONE,    -HOUR (12) },	/* Samoa Standard */
  { "WAT",	tZONE,     HOUR ( 1) },	/* West Africa */
  { "CET",	tZONE,     HOUR ( 1) },	/* Central European */
  { "CEST",	tDAYZONE,  HOUR ( 1) },	/* Central European Summer */
  { "MET",	tZONE,     HOUR ( 1) },	/* Middle European */
  { "MEZ",	tZONE,     HOUR ( 1) },	/* Middle European */
  { "MEST",	tDAYZONE,  HOUR ( 1) },	/* Middle European Summer */
  { "MESZ",	tDAYZONE,  HOUR ( 1) },	/* Middle European Summer */
  { "EET",	tZONE,     HOUR ( 2) },	/* Eastern European */
  { "EEST",	tDAYZONE,  HOUR ( 2) },	/* Eastern European Summer */
  { "CAT",	tZONE,	   HOUR ( 2) },	/* Central Africa */
  { "SAST",	tZONE,	   HOUR ( 2) },	/* South Africa Standard */
  { "EAT",	tZONE,	   HOUR ( 3) },	/* East Africa */
  { "MSK",	tZONE,	   HOUR ( 3) },	/* Moscow */
  { "MSD",	tDAYZONE,  HOUR ( 3) },	/* Moscow Daylight */
  { "IST",	tZONE,	  (HOUR ( 5) + 30) },	/* India Standard */
  { "SGT",	tZONE,     HOUR ( 8) },	/* Singapore */
  { "KST",	tZONE,     HOUR ( 9) },	/* Korea Standard */
  { "JST",	tZONE,     HOUR ( 9) },	/* Japan Standard */
  { "GST",	tZONE,     HOUR (10) },	/* Guam Standard */
  { "NZST",	tZONE,     HOUR (12) },	/* New Zealand Standard */
  { "NZDT",	tDAYZONE,  HOUR (12) },	/* New Zealand Daylight */
  { NULL, 0, 0 }
};

/* Military time zone table. */
static table const military_table[] =
{
  { "A", tZONE,	-HOUR ( 1) },
  { "B", tZONE,	-HOUR ( 2) },
  { "C", tZONE,	-HOUR ( 3) },
  { "D", tZONE,	-HOUR ( 4) },
  { "E", tZONE,	-HOUR ( 5) },
  { "F", tZONE,	-HOUR ( 6) },
  { "G", tZONE,	-HOUR ( 7) },
  { "H", tZONE,	-HOUR ( 8) },
  { "I", tZONE,	-HOUR ( 9) },
  { "K", tZONE,	-HOUR (10) },
  { "L", tZONE,	-HOUR (11) },
  { "M", tZONE,	-HOUR (12) },
  { "N", tZONE,	 HOUR ( 1) },
  { "O", tZONE,	 HOUR ( 2) },
  { "P", tZONE,	 HOUR ( 3) },
  { "Q", tZONE,	 HOUR ( 4) },
  { "R", tZONE,	 HOUR ( 5) },
  { "S", tZONE,	 HOUR ( 6) },
  { "T", tZONE,	 HOUR ( 7) },
  { "U", tZONE,	 HOUR ( 8) },
  { "V", tZONE,	 HOUR ( 9) },
  { "W", tZONE,	 HOUR (10) },
  { "X", tZONE,	 HOUR (11) },
  { "Y", tZONE,	 HOUR (12) },
  { "Z", tZONE,	 HOUR ( 0) },
  { NULL, 0, 0 }
};



/* Convert a time zone expressed as HH:MM into an integer count of
   minutes.  If MM is negative, then S is of the form HHMM and needs
   to be picked apart; otherwise, S is of the form HH.  */

static long int
time_zone_hhmm (textint s, long int mm)
{
  if (mm < 0)
    return (s.value / 100) * 60 + s.value % 100;
  else
    return s.value * 60 + (s.negative ? -mm : mm);
}

static int
to_hour (long int hours, int meridian)
{
  switch (meridian)
    {
    default: /* Pacify GCC.  */
    case MER24:
      return 0 <= hours && hours < 24 ? hours : -1;
    case MERam:
      return 0 < hours && hours < 12 ? hours : hours == 12 ? 0 : -1;
    case MERpm:
      return 0 < hours && hours < 12 ? hours + 12 : hours == 12 ? 12 : -1;
    }
}

static long int
to_year (textint textyear)
{
  long int year = textyear.value;

  if (year < 0)
    year = -year;

  /* XPG4 suggests that years 00-68 map to 2000-2068, and
     years 69-99 map to 1969-1999.  */
  else if (textyear.digits == 2)
    year += year < 69 ? 2000 : 1900;

  return year;
}

static table const *
lookup_zone (parser_control const *pc, char const *name)
{
  table const *tp;

  for (tp = universal_time_zone_table; tp->name; tp++)
    if (strcmp (name, tp->name) == 0)
      return tp;

  /* Try local zone abbreviations before those in time_zone_table, as
     the local ones are more likely to be right.  */
  for (tp = pc->local_time_zone_table; tp->name; tp++)
    if (strcmp (name, tp->name) == 0)
      return tp;

  for (tp = time_zone_table; tp->name; tp++)
    if (strcmp (name, tp->name) == 0)
      return tp;

  return NULL;
}

#if ! HAVE_TM_GMTOFF
/* Yield the difference between *A and *B,
   measured in seconds, ignoring leap seconds.
   The body of this function is taken directly from the GNU C Library;
   see src/strftime.c.  */
static long int
tm_diff (struct tm const *a, struct tm const *b)
{
  /* Compute intervening leap days correctly even if year is negative.
     Take care to avoid int overflow in leap day calculations.  */
  int a4 = SHR (a->tm_year, 2) + SHR (TM_YEAR_BASE, 2) - ! (a->tm_year & 3);
  int b4 = SHR (b->tm_year, 2) + SHR (TM_YEAR_BASE, 2) - ! (b->tm_year & 3);
  int a100 = a4 / 25 - (a4 % 25 < 0);
  int b100 = b4 / 25 - (b4 % 25 < 0);
  int a400 = SHR (a100, 2);
  int b400 = SHR (b100, 2);
  int intervening_leap_days = (a4 - b4) - (a100 - b100) + (a400 - b400);
  long int ayear = a->tm_year;
  long int years = ayear - b->tm_year;
  long int days = (365 * years + intervening_leap_days
		   + (a->tm_yday - b->tm_yday));
  return (60 * (60 * (24 * days + (a->tm_hour - b->tm_hour))
		+ (a->tm_min - b->tm_min))
	  + (a->tm_sec - b->tm_sec));
}
#endif /* ! HAVE_TM_GMTOFF */

static table const *
lookup_word (parser_control const *pc, char *word)
{
  char *p;
  char *q;
  size_t wordlen;
  table const *tp;
  bool period_found;
  bool abbrev;

  /* Make it uppercase.  */
  for (p = word; *p; p++)
    {
      unsigned char ch = *p;
      *p = toupper (ch);
    }

  for (tp = meridian_table; tp->name; tp++)
    if (strcmp (word, tp->name) == 0)
      return tp;

  /* See if we have an abbreviation for a month. */
  wordlen = strlen (word);
  abbrev = wordlen == 3 || (wordlen == 4 && word[3] == '.');

  for (tp = month_and_day_table; tp->name; tp++)
    if ((abbrev ? strncmp (word, tp->name, 3) : strcmp (word, tp->name)) == 0)
      return tp;

  if ((tp = lookup_zone (pc, word)))
    return tp;

  if (strcmp (word, dst_table[0].name) == 0)
    return dst_table;

  for (tp = time_units_table; tp->name; tp++)
    if (strcmp (word, tp->name) == 0)
      return tp;

  /* Strip off any plural and try the units table again. */
  if (word[wordlen - 1] == 'S')
    {
      word[wordlen - 1] = '\0';
      for (tp = time_units_table; tp->name; tp++)
	if (strcmp (word, tp->name) == 0)
	  return tp;
      word[wordlen - 1] = 'S';	/* For "this" in relative_time_table.  */
    }

  for (tp = relative_time_table; tp->name; tp++)
    if (strcmp (word, tp->name) == 0)
      return tp;

  /* Military time zones. */
  if (wordlen == 1)
    for (tp = military_table; tp->name; tp++)
      if (word[0] == tp->name[0])
	return tp;

  /* Drop out any periods and try the time zone table again. */
  for (period_found = false, p = q = word; (*p = *q); q++)
    if (*q == '.')
      period_found = true;
    else
      p++;
  if (period_found && (tp = lookup_zone (pc, word)))
    return tp;

  return NULL;
}

static int
yylex (YYSTYPE *lvalp, parser_control *pc)
{
  unsigned char c;
  size_t count;

  for (;;)
    {
      while (c = *pc->input, isspace (c))
	pc->input++;

      if (ISDIGIT (c) || c == '-' || c == '+')
	{
	  char const *p;
	  int sign;
	  unsigned long int value;
	  if (c == '-' || c == '+')
	    {
	      sign = c == '-' ? -1 : 1;
	      while (c = *++pc->input, isspace (c))
		continue;
	      if (! ISDIGIT (c))
		/* skip the '-' sign */
		continue;
	    }
	  else
	    sign = 0;
	  p = pc->input;
	  for (value = 0; ; value *= 10)
	    {
	      unsigned long int value1 = value + (c - '0');
	      if (value1 < value)
		return '?';
	      value = value1;
	      c = *++p;
	      if (! ISDIGIT (c))
		break;
	      if (ULONG_MAX / 10 < value)
		return '?';
	    }
	  if ((c == '.' || c == ',') && ISDIGIT (p[1]))
	    {
	      time_t s;
	      int ns;
	      int digits;
	      unsigned long int value1;

	      /* Check for overflow when converting value to time_t.  */
	      if (sign < 0)
		{
		  s = - value;
		  if (0 < s)
		    return '?';
		  value1 = -s;
		}
	      else
		{
		  s = value;
		  if (s < 0)
		    return '?';
		  value1 = s;
		}
	      if (value != value1)
		return '?';

	      /* Accumulate fraction, to ns precision.  */
	      p++;
	      ns = *p++ - '0';
	      for (digits = 2; digits <= LOG10_BILLION; digits++)
		{
		  ns *= 10;
		  if (ISDIGIT (*p))
		    ns += *p++ - '0';
		}

	      /* Skip excess digits, truncating toward -Infinity.  */
	      if (sign < 0)
		for (; ISDIGIT (*p); p++)
		  if (*p != '0')
		    {
		      ns++;
		      break;
		    }
	      while (ISDIGIT (*p))
		p++;

	      /* Adjust to the timespec convention, which is that
		 tv_nsec is always a positive offset even if tv_sec is
		 negative.  */
	      if (sign < 0 && ns)
		{
		  s--;
		  if (! (s < 0))
		    return '?';
		  ns = BILLION - ns;
		}

	      lvalp->timespec.tv_sec = s;
	      lvalp->timespec.tv_nsec = ns;
	      pc->input = p;
	      return sign ? tSDECIMAL_NUMBER : tUDECIMAL_NUMBER;
	    }
	  else
	    {
	      lvalp->textintval.negative = sign < 0;
	      if (sign < 0)
		{
		  lvalp->textintval.value = - value;
		  if (0 < lvalp->textintval.value)
		    return '?';
		}
	      else
		{
		  lvalp->textintval.value = value;
		  if (lvalp->textintval.value < 0)
		    return '?';
		}
	      lvalp->textintval.digits = p - pc->input;
	      pc->input = p;
	      return sign ? tSNUMBER : tUNUMBER;
	    }
	}

      if (isalpha (c))
	{
	  char buff[20];
	  char *p = buff;
	  table const *tp;

	  do
	    {
	      if (p < buff + sizeof buff - 1)
		*p++ = c;
	      c = *++pc->input;
	    }
	  while (isalpha (c) || c == '.');

	  *p = '\0';
	  tp = lookup_word (pc, buff);
	  if (! tp)
	    return '?';
	  lvalp->intval = tp->value;
	  return tp->type;
	}

      if (c != '(')
	return *pc->input++;
      count = 0;
      do
	{
	  c = *pc->input++;
	  if (c == '\0')
	    return c;
	  if (c == '(')
	    count++;
	  else if (c == ')')
	    count--;
	}
      while (count != 0);
    }
}

/* Do nothing if the parser reports an error.  */
static int
yyerror (parser_control const *pc ATTRIBUTE_UNUSED,
	 char const *s ATTRIBUTE_UNUSED)
{
  return 0;
}

/* If *TM0 is the old and *TM1 is the new value of a struct tm after
   passing it to mktime, return true if it's OK that mktime returned T.
   It's not OK if *TM0 has out-of-range members.  */

static bool
mktime_ok (struct tm const *tm0, struct tm const *tm1, time_t t)
{
  if (t == (time_t) -1)
    {
      /* Guard against falsely reporting an error when parsing a time
	 stamp that happens to equal (time_t) -1, on a host that
	 supports such a time stamp.  */
      tm1 = localtime (&t);
      if (!tm1)
	return false;
    }

  return ! ((tm0->tm_sec ^ tm1->tm_sec)
	    | (tm0->tm_min ^ tm1->tm_min)
	    | (tm0->tm_hour ^ tm1->tm_hour)
	    | (tm0->tm_mday ^ tm1->tm_mday)
	    | (tm0->tm_mon ^ tm1->tm_mon)
	    | (tm0->tm_year ^ tm1->tm_year));
}

/* A reasonable upper bound for the size of ordinary TZ strings.
   Use heap allocation if TZ's length exceeds this.  */
enum { TZBUFSIZE = 100 };

/* Return a copy of TZ, stored in TZBUF if it fits, and heap-allocated
   otherwise.  */
static char *
get_tz (char tzbuf[TZBUFSIZE])
{
  char *tz = getenv ("TZ");
  if (tz)
    {
      size_t tzsize = strlen (tz) + 1;
      tz = (tzsize <= TZBUFSIZE
	    ? memcpy (tzbuf, tz, tzsize)
	    : xmemdup (tz, tzsize));
    }
  return tz;
}

/* Parse a date/time string, storing the resulting time value into *RESULT.
   The string itself is pointed to by P.  Return true if successful.
   P can be an incomplete or relative time specification; if so, use
   *NOW as the basis for the returned time.  */
bool
get_date (struct timespec *result, char const *p, struct timespec const *now)
{
  time_t Start;
  long int Start_ns;
  struct tm const *tmp;
  struct tm tm;
  struct tm tm0;
  parser_control pc;
  struct timespec gettime_buffer;
  unsigned char c;
  bool tz_was_altered = false;
  char *tz0 = NULL;
  char tz0buf[TZBUFSIZE];
  bool ok = true;

  if (! now)
    {
      gettime (&gettime_buffer);
      now = &gettime_buffer;
    }

  Start = now->tv_sec;
  Start_ns = now->tv_nsec;

  tmp = localtime (&now->tv_sec);
  if (! tmp)
    return false;

  while (c = *p, isspace (c))
    p++;

  if (strncmp (p, "TZ=\"", 4) == 0)
    {
      char const *tzbase = p + 4;
      size_t tzsize = 1;
      char const *s;

      for (s = tzbase; *s; s++, tzsize++)
	if (*s == '\\')
	  {
	    s++;
	    if (! (*s == '\\' || *s == '"'))
	      break;
	  }
	else if (*s == '"')
	  {
	    char *z;
	    char *tz1;
	    char tz1buf[TZBUFSIZE];
	    bool large_tz = TZBUFSIZE < tzsize;
	    bool setenv_ok;
	    tz0 = get_tz (tz0buf);
	    z = tz1 = large_tz ? xmalloc (tzsize) : tz1buf;
	    for (s = tzbase; *s != '"'; s++)
	      *z++ = *(s += *s == '\\');
	    *z = '\0';
	    setenv_ok = setenv ("TZ", tz1, 1) == 0;
	    if (large_tz)
	      free (tz1);
	    if (!setenv_ok)
	      goto fail;
	    tz_was_altered = true;
	    p = s + 1;
	  }
    }

  /* As documented, be careful to treat the empty string just like
     a date string of "0".  Without this, an empty string would be
     declared invalid when parsed during a DST transition.  */
  if (*p == '\0')
    p = "0";

  pc.input = p;
  pc.year.value = tmp->tm_year;
  pc.year.value += TM_YEAR_BASE;
  pc.year.digits = 0;
  pc.month = tmp->tm_mon + 1;
  pc.day = tmp->tm_mday;
  pc.hour = tmp->tm_hour;
  pc.minutes = tmp->tm_min;
  pc.seconds.tv_sec = tmp->tm_sec;
  pc.seconds.tv_nsec = Start_ns;
  tm.tm_isdst = tmp->tm_isdst;

  pc.meridian = MER24;
  pc.rel = RELATIVE_TIME_0;
  pc.timespec_seen = false;
  pc.rels_seen = false;
  pc.dates_seen = 0;
  pc.days_seen = 0;
  pc.times_seen = 0;
  pc.local_zones_seen = 0;
  pc.dsts_seen = 0;
  pc.zones_seen = 0;

#if HAVE_STRUCT_TM_TM_ZONE
  pc.local_time_zone_table[0].name = tmp->tm_zone;
  pc.local_time_zone_table[0].type = tLOCAL_ZONE;
  pc.local_time_zone_table[0].value = tmp->tm_isdst;
  pc.local_time_zone_table[1].name = NULL;

  /* Probe the names used in the next three calendar quarters, looking
     for a tm_isdst different from the one we already have.  */
  {
    int quarter;
    for (quarter = 1; quarter <= 3; quarter++)
      {
	time_t probe = Start + quarter * (90 * 24 * 60 * 60);
	struct tm const *probe_tm = localtime (&probe);
	if (probe_tm && probe_tm->tm_zone
	    && probe_tm->tm_isdst != pc.local_time_zone_table[0].value)
	  {
	      {
		pc.local_time_zone_table[1].name = probe_tm->tm_zone;
		pc.local_time_zone_table[1].type = tLOCAL_ZONE;
		pc.local_time_zone_table[1].value = probe_tm->tm_isdst;
		pc.local_time_zone_table[2].name = NULL;
	      }
	    break;
	  }
      }
  }
#else
#if HAVE_TZNAME
  {
# if !HAVE_DECL_TZNAME
    extern char *tzname[];
# endif
    int i;
    for (i = 0; i < 2; i++)
      {
	pc.local_time_zone_table[i].name = tzname[i];
	pc.local_time_zone_table[i].type = tLOCAL_ZONE;
	pc.local_time_zone_table[i].value = i;
      }
    pc.local_time_zone_table[i].name = NULL;
  }
#else
  pc.local_time_zone_table[0].name = NULL;
#endif
#endif

  if (pc.local_time_zone_table[0].name && pc.local_time_zone_table[1].name
      && ! strcmp (pc.local_time_zone_table[0].name,
		   pc.local_time_zone_table[1].name))
    {
      /* This locale uses the same abbrevation for standard and
	 daylight times.  So if we see that abbreviation, we don't
	 know whether it's daylight time.  */
      pc.local_time_zone_table[0].value = -1;
      pc.local_time_zone_table[1].name = NULL;
    }

  if (yyparse (&pc) != 0)
    goto fail;

  if (pc.timespec_seen)
    *result = pc.seconds;
  else
    {
      if (1 < (pc.times_seen | pc.dates_seen | pc.days_seen | pc.dsts_seen
	       | (pc.local_zones_seen + pc.zones_seen)))
	goto fail;

      tm.tm_year = to_year (pc.year) - TM_YEAR_BASE;
      tm.tm_mon = pc.month - 1;
      tm.tm_mday = pc.day;
      if (pc.times_seen || (pc.rels_seen && ! pc.dates_seen && ! pc.days_seen))
	{
	  tm.tm_hour = to_hour (pc.hour, pc.meridian);
	  if (tm.tm_hour < 0)
	    goto fail;
	  tm.tm_min = pc.minutes;
	  tm.tm_sec = pc.seconds.tv_sec;
	}
      else
	{
	  tm.tm_hour = tm.tm_min = tm.tm_sec = 0;
	  pc.seconds.tv_nsec = 0;
	}

      /* Let mktime deduce tm_isdst if we have an absolute time stamp.  */
      if (pc.dates_seen | pc.days_seen | pc.times_seen)
	tm.tm_isdst = -1;

      /* But if the input explicitly specifies local time with or without
	 DST, give mktime that information.  */
      if (pc.local_zones_seen)
	tm.tm_isdst = pc.local_isdst;

      tm0 = tm;

      Start = mktime (&tm);

      if (! mktime_ok (&tm0, &tm, Start))
	{
	  if (! pc.zones_seen)
	    goto fail;
	  else
	    {
	      /* Guard against falsely reporting errors near the time_t
		 boundaries when parsing times in other time zones.  For
		 example, suppose the input string "1969-12-31 23:00:00 -0100",
		 the current time zone is 8 hours ahead of UTC, and the min
		 time_t value is 1970-01-01 00:00:00 UTC.  Then the min
		 localtime value is 1970-01-01 08:00:00, and mktime will
		 therefore fail on 1969-12-31 23:00:00.  To work around the
		 problem, set the time zone to 1 hour behind UTC temporarily
		 by setting TZ="XXX1:00" and try mktime again.  */

	      long int time_zone = pc.time_zone;
	      long int abs_time_zone = time_zone < 0 ? - time_zone : time_zone;
	      long int abs_time_zone_hour = abs_time_zone / 60;
	      int abs_time_zone_min = abs_time_zone % 60;
	      char tz1buf[sizeof "XXX+0:00"
			  + sizeof pc.time_zone * CHAR_BIT / 3];
	      if (!tz_was_altered)
		tz0 = get_tz (tz0buf);
	      sprintf (tz1buf, "XXX%s%ld:%02d", "-" + (time_zone < 0),
		       abs_time_zone_hour, abs_time_zone_min);
	      if (setenv ("TZ", tz1buf, 1) != 0)
		goto fail;
	      tz_was_altered = true;
	      tm = tm0;
	      Start = mktime (&tm);
	      if (! mktime_ok (&tm0, &tm, Start))
		goto fail;
	    }
	}

      if (pc.days_seen && ! pc.dates_seen)
	{
	  tm.tm_mday += ((pc.day_number - tm.tm_wday + 7) % 7
			 + 7 * (pc.day_ordinal - (0 < pc.day_ordinal)));
	  tm.tm_isdst = -1;
	  Start = mktime (&tm);
	  if (Start == (time_t) -1)
	    goto fail;
	}

      if (pc.zones_seen)
	{
	  long int delta = pc.time_zone * 60;
	  time_t t1;
#ifdef HAVE_TM_GMTOFF
	  delta -= tm.tm_gmtoff;
#else
	  time_t t = Start;
	  struct tm const *gmt = gmtime (&t);
	  if (! gmt)
	    goto fail;
	  delta -= tm_diff (&tm, gmt);
#endif
	  t1 = Start - delta;
	  if ((Start < t1) != (delta < 0))
	    goto fail;	/* time_t overflow */
	  Start = t1;
	}

      /* Add relative date.  */
      if (pc.rel.year | pc.rel.month | pc.rel.day)
	{
	  int year = tm.tm_year + pc.rel.year;
	  int month = tm.tm_mon + pc.rel.month;
	  int day = tm.tm_mday + pc.rel.day;
	  if (((year < tm.tm_year) ^ (pc.rel.year < 0))
	      | ((month < tm.tm_mon) ^ (pc.rel.month < 0))
	      | ((day < tm.tm_mday) ^ (pc.rel.day < 0)))
	    goto fail;
	  tm.tm_year = year;
	  tm.tm_mon = month;
	  tm.tm_mday = day;
	  tm.tm_hour = tm0.tm_hour;
	  tm.tm_min = tm0.tm_min;
	  tm.tm_sec = tm0.tm_sec;
	  tm.tm_isdst = tm0.tm_isdst;
	  Start = mktime (&tm);
	  if (Start == (time_t) -1)
	    goto fail;
	}

      /* Add relative hours, minutes, and seconds.  On hosts that support
	 leap seconds, ignore the possibility of leap seconds; e.g.,
	 "+ 10 minutes" adds 600 seconds, even if one of them is a
	 leap second.  Typically this is not what the user wants, but it's
	 too hard to do it the other way, because the time zone indicator
	 must be applied before relative times, and if mktime is applied
	 again the time zone will be lost.  */
      {
	long int sum_ns = pc.seconds.tv_nsec + pc.rel.ns;
	long int normalized_ns = (sum_ns % BILLION + BILLION) % BILLION;
	time_t t0 = Start;
	long int d1 = 60 * 60 * pc.rel.hour;
	time_t t1 = t0 + d1;
	long int d2 = 60 * pc.rel.minutes;
	time_t t2 = t1 + d2;
	long int d3 = pc.rel.seconds;
	time_t t3 = t2 + d3;
	long int d4 = (sum_ns - normalized_ns) / BILLION;
	time_t t4 = t3 + d4;

	if ((d1 / (60 * 60) ^ pc.rel.hour)
	    | (d2 / 60 ^ pc.rel.minutes)
	    | ((t1 < t0) ^ (d1 < 0))
	    | ((t2 < t1) ^ (d2 < 0))
	    | ((t3 < t2) ^ (d3 < 0))
	    | ((t4 < t3) ^ (d4 < 0)))
	  goto fail;

	result->tv_sec = t4;
	result->tv_nsec = normalized_ns;
      }
    }

  goto done;

 fail:
  ok = false;
 done:
  if (tz_was_altered)
    ok &= (tz0 ? setenv ("TZ", tz0, 1) : unsetenv ("TZ")) == 0;
  if (tz0 != tz0buf)
    free (tz0);
  return ok;
}

#if TEST

int
main (int ac, char **av)
{
  char buff[BUFSIZ];

  printf ("Enter date, or blank line to exit.\n\t> ");
  fflush (stdout);

  buff[BUFSIZ - 1] = '\0';
  while (fgets (buff, BUFSIZ - 1, stdin) && buff[0])
    {
      struct timespec d;
      struct tm const *tm;
      if (! get_date (&d, buff, NULL))
	printf ("Bad format - couldn't convert.\n");
      else if (! (tm = localtime (&d.tv_sec)))
	{
	  long int sec = d.tv_sec;
	  printf ("localtime (%ld) failed\n", sec);
	}
      else
	{
	  int ns = d.tv_nsec;
	  printf ("%04ld-%02d-%02d %02d:%02d:%02d.%09d\n",
		  tm->tm_year + 1900L, tm->tm_mon + 1, tm->tm_mday,
		  tm->tm_hour, tm->tm_min, tm->tm_sec, ns);
	}
      printf ("\t> ");
      fflush (stdout);
    }
  return 0;
}
#endif /* TEST */
