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
    VAR = 258,
    ENDVAR = 259,
    TABLE = 260,
    ENDTABLE = 261,
    OBJECT = 262,
    ENDOBJECT = 263,
    PROGRAM = 264,
    IDENT = 265,
    CONSTRUCTOR = 266,
    MAIN = 267,
    AND = 268,
    OR = 269,
    NOT = 270,
    IF = 271,
    ELSE = 272,
    WHILE = 273,
    FUNCTION = 274,
    RETURN = 275,
    CLASS = 276,
    EXTENDS = 277,
    SUPER = 278,
    PRINT = 279,
    INPUT = 280,
    ADDSUBOPS = 281,
    MULDIVOPS = 282,
    CONST = 283,
    DIFF = 284,
    RELATOP = 285,
    ASSIGN = 286
  };
#endif
/* Tokens.  */
#define VAR 258
#define ENDVAR 259
#define TABLE 260
#define ENDTABLE 261
#define OBJECT 262
#define ENDOBJECT 263
#define PROGRAM 264
#define IDENT 265
#define CONSTRUCTOR 266
#define MAIN 267
#define AND 268
#define OR 269
#define NOT 270
#define IF 271
#define ELSE 272
#define WHILE 273
#define FUNCTION 274
#define RETURN 275
#define CLASS 276
#define EXTENDS 277
#define SUPER 278
#define PRINT 279
#define INPUT 280
#define ADDSUBOPS 281
#define MULDIVOPS 282
#define CONST 283
#define DIFF 284
#define RELATOP 285
#define ASSIGN 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
