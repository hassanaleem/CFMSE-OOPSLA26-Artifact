/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_TYPE = 258,
    TK_VAR = 259,
    TK_FN = 260,
    TK_RETURN = 261,
    TK_INT = 262,
    TK_LONG = 263,
    TK_REAL = 264,
    TK_STRING = 265,
    TK_TIME = 266,
    TK_VOID = 267,
    TK_PROJECT = 268,
    TK_RENAME = 269,
    TK_SELECT = 270,
    TK_EXTEND = 271,
    TK_SUMMARY = 272,
    TK_JOIN = 273,
    TK_UNION = 274,
    TK_MINUS = 275,
    TK_EQ = 276,
    TK_NEQ = 277,
    TK_AND = 278,
    TK_OR = 279,
    TK_LTE = 280,
    TK_GTE = 281,
    TK_NAME = 282,
    TK_INT_VAL = 283,
    TK_LONG_VAL = 284,
    TK_REAL_VAL = 285,
    TK_STRING_VAL = 286
  };
#endif
/* Tokens.  */
#define TK_TYPE 258
#define TK_VAR 259
#define TK_FN 260
#define TK_RETURN 261
#define TK_INT 262
#define TK_LONG 263
#define TK_REAL 264
#define TK_STRING 265
#define TK_TIME 266
#define TK_VOID 267
#define TK_PROJECT 268
#define TK_RENAME 269
#define TK_SELECT 270
#define TK_EXTEND 271
#define TK_SUMMARY 272
#define TK_JOIN 273
#define TK_UNION 274
#define TK_MINUS 275
#define TK_EQ 276
#define TK_NEQ 277
#define TK_AND 278
#define TK_OR 279
#define TK_LTE 280
#define TK_GTE 281
#define TK_NAME 282
#define TK_INT_VAL 283
#define TK_LONG_VAL 284
#define TK_REAL_VAL 285
#define TK_STRING_VAL 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 97 "language.y" /* yacc.c:1909  */

    char name[MAX_NAME];
    Head *head;

    L_Value val;
    L_Expr *expr;
    L_Attrs attrs;
    L_Sum sum;
    Rel *rel;

#line 127 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
