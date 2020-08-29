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




/* Copy the first part of user declarations.  */
#line 2 "yacc.y" /* yacc.c:339  */

int yylex();

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define malloc_func(pntr, size) (pntr) = malloc(size); \
                                 if (!(pntr)) { \
                                     fprintf(stderr, "Error, no available memory"); \
                                     exit(1); \
                                 }
#define YYSTYPE char *
FILE *ResultsFile;
int class_count = -1;
char *class_name = NULL;
char *parameters[20];

struct objects {
	char *class_name;
	char *object_name;
} typedef objects;

struct info {
	char *class_name;
	char *extends_name;
	
	char *var_names[100];
	char *table_names[100];
	char *method_names[100];
} typedef info;

info class_info[100];
objects main_objects[50];

void createExtendedClassProperties(char *class){
	int i,j,k;
	char *extends_name;
	for (i = 0; i < 100; ++i) {
		if (class_info[i].class_name && strcmp(class_info[i].class_name, class) == 0){
			extends_name = class_info[i].extends_name;
			if(extends_name){
				for (j = 0; j < 100; ++j) {
					if (class_info[j].class_name && strcmp(class_info[j].class_name, extends_name) == 0){
						for (k = 0; k < 100; ++k) {
							if(class_info[j].var_names[k]){
								addVarToClass(class_info[i].class_name,class_info[j].var_names[k]);
								fprintf(ResultsFile,"int %s;\n",class_info[j].var_names[k]);
							}
						}

						for (k = 0; k < 100; ++k) {
							if(class_info[j].table_names[k]){
								addTableToClass(class_info[i].class_name,class_info[j].table_names[k]);
								fprintf(ResultsFile,"int %s;\n",class_info[j].table_names[k]);
							}
						}
					}
				}
			}
		}
	}
}

void superCall(char *class, char *method, char *actualpars){
	int i,j,k;
	char *extends_name;
	for (i = 0; i < 100; ++i) {
		if (class_info[i].class_name && strcmp(class_info[i].class_name, class) == 0){
			extends_name = class_info[i].extends_name;
			if(extends_name){
				for (j = 0; j < 100; ++j) {
					if (class_info[j].class_name && strcmp(class_info[j].class_name, extends_name) == 0){
						for (k = 0; k < 100; ++k) {
							if (class_info[j].method_names[k] && strcmp(class_info[j].method_names[k], method) == 0){
								if(strcmp(actualpars,")") != 0){
									fprintf(ResultsFile,"%s_%s(&self, %s;\n",class_info[j].class_name,method,actualpars);
									return;
								}else{
									fprintf(ResultsFile,"%s_%s(&self%s;\n",class_info[j].class_name,method,actualpars);
									return;
								}
							}
						}
					}
				}
			}
		}
	}
	char str[200];
	sprintf(str, "Error: Either method '%s' does not exist, or object class '%s' does not extend from other class!",method,class);
	yyerror(str);
}

char * findMethod(char *class, char *method){
	int i,j,k;
	char *extends_name;
	for (i = 0; i < 100; ++i) {
		if (class_info[i].class_name && strcmp(class_info[i].class_name, class) == 0){
			for (j = 0; j < 100; ++j) {
				if (class_info[i].method_names[j] && strcmp(class_info[i].method_names[j], method) == 0){
					return class_info[i].class_name;
				}
			}
			extends_name = class_info[i].extends_name;
			if (extends_name){
				for (j = 0; j < 100; ++j) {
					if (class_info[j].class_name && strcmp(class_info[j].class_name, extends_name) == 0){
						for (k = 0; k < 100; ++k) {
							if (class_info[j].method_names[k] && strcmp(class_info[j].method_names[k], method) == 0){
								return class_info[j].class_name;
							}
						}
					}
				}
			}
		}
	}
	char str[200];
	sprintf(str, "Error: The method %s does not exist for objects of class %s\n",method,class);
	yyerror(str);
}

void createStructForObject(char *class,char *object){
	fprintf(ResultsFile, "%s %s;\n\n",class,object);
}

char* findClassFromObject(char *object){
	int i;
	for (i = 0; i < 50; ++i) {
		if(main_objects[i].object_name && strcmp(main_objects[i].object_name, object) == 0){
			return main_objects[i].class_name;
		}
	}
	return NULL;
}

void addNameToClass(int index,char *name){
	class_info[index].class_name  = strdup(name);
}

void addExtendNameToClass(int index,char *name){
	class_info[index].extends_name  = strdup(name);
}

void addVarToClass(char *class,char *var){
	int i, j;
	for (i = 0; i < 100; ++i) {
		if (strcmp(class_info[i].class_name, class) == 0) {
			for (j = 0; j < 100; ++j) {
				if (class_info[i].var_names[j] == NULL) {
					class_info[i].var_names[j] = strdup(var);
					return;
				}
			}
		}
	}
}

void addTableToClass(char *class,char *table){
	int i, j;
	for (i = 0; i < 100; ++i) {
		if (strcmp(class_info[i].class_name, class) == 0) {
			for (j = 0; j < 100; ++j) {
				if (class_info[i].table_names[j] == NULL) {
					class_info[i].table_names[j] = strdup(table);
					return;
				}
			}
		}
	}
}

void addParameterToArray(char *parameter){
	int i;
	for (i = 0; i < 20; ++i) {
		if (parameters[i] == NULL) {
			parameters[i] = strdup(parameter);
			return;
		}
	}
}

int findParameter(char *parameter){
	int i;
	for (i = 0; i < 20; ++i) {
		if (parameters[i] && strcmp(parameters[i],parameter) == 0) {
			return 1;
		}
	}
	return 0;
}

void addObjectToArray(char *class, char *object){
	int i;
	for (i = 0; i < 50; ++i) {
		if (main_objects[i].object_name == 0) {
			main_objects[i].object_name = strdup(object);
			main_objects[i].class_name = strdup(class);
			return;
		}
	}
}

void addMethodToClass(char *class,char *method){
	int i, j;
	for (i = 0; i < 100; ++i) {
		if (strcmp(class_info[i].class_name, class) == 0) {
			for (j = 0; j < 100; ++j) {
				if (class_info[i].method_names[j] == NULL) {
					class_info[i].method_names[j] = strdup(method);
					return;
				}
			}
		}
	}
}

void printParameter(){
	int i;
	for (i = 0; i < 20; ++i) {
		if(parameters[i]){
			printf("%s\n",parameters[i]);
		}
	}
}

#line 293 "y.tab.c" /* yacc.c:339  */

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
   by #include "y.tab.h".  */
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

/* Copy the second part of user declarations.  */

#line 406 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   233

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  78
/* YYNRULES -- Number of rules.  */
#define YYNRULES  133
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  261

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      45,    46,    40,    38,    49,    39,    42,    41,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    50,
      33,     2,    35,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    47,     2,    48,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    43,     2,    44,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    34,    36,
      37
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   249,   249,   249,   249,   252,   254,   252,   257,   260,
     261,   264,   265,   268,   270,   270,   268,   271,   274,   274,
     271,   277,   280,   280,   283,   283,   286,   286,   288,   289,
     292,   300,   303,   303,   305,   306,   309,   312,   312,   313,
     314,   317,   320,   320,   321,   322,   325,   325,   325,   326,
     329,   330,   333,   333,   333,   334,   334,   334,   335,   335,
     335,   336,   339,   339,   340,   343,   344,   344,   347,   348,
     349,   352,   353,   356,   357,   358,   359,   360,   361,   362,
     363,   364,   367,   368,   369,   370,   373,   373,   373,   376,
     376,   377,   380,   380,   383,   386,   387,   390,   393,   394,
     397,   398,   401,   402,   405,   406,   407,   410,   411,   414,
     415,   418,   419,   420,   421,   422,   425,   427,   430,   431,
     434,   435,   438,   439,   442,   443,   446,   447,   448,   449,
     452,   453,   454,   457
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VAR", "ENDVAR", "TABLE", "ENDTABLE",
  "OBJECT", "ENDOBJECT", "PROGRAM", "IDENT", "CONSTRUCTOR", "MAIN", "AND",
  "OR", "NOT", "IF", "ELSE", "WHILE", "FUNCTION", "RETURN", "CLASS",
  "EXTENDS", "SUPER", "PRINT", "INPUT", "ADDSUBOPS", "MULDIVOPS", "CONST",
  "DIFF", "RELATOP", "ASSIGN", "\"!=\"", "'<'", "\"<=\"", "'>'", "\">=\"",
  "\"==\"", "'+'", "'-'", "'*'", "'/'", "'.'", "'{'", "'}'", "'('", "')'",
  "'['", "']'", "','", "';'", "$accept", "program", "$@1", "$@2", "main",
  "$@3", "$@4", "ID", "IDTABLE", "programblock", "class", "$@5", "$@6",
  "$@7", "$@8", "$@9", "$@10", "declarations_main", "declarations", "$@11",
  "vardecmain", "$@12", "varrepeatmain", "$@13", "tabledecmain", "vardec",
  "varrepeat", "$@15", "tabledec", "tablerepeat", "$@16", "objdec",
  "objectrepeat", "$@17", "constructors", "$@18", "$@19", "function",
  "functionrep", "$@20", "$@21", "$@22", "$@23", "$@24", "$@25",
  "formalpars", "$@26", "formalparlist", "$@27", "formalparitem",
  "sequence", "statement", "assignment", "if", "$@28", "$@29", "else",
  "$@30", "while", "$@31", "return", "input", "super", "call",
  "actualpars", "actualparlist", "actualparitem", "condition", "bterm",
  "bfactor", "expr", "optsignterm", "optsign", "term", "optsignfactor",
  "factor", "funccall", "print", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,    60,   288,    62,   289,   290,    43,    45,
      42,    47,    46,   123,   125,    40,    41,    91,    93,    44,
      59
};
# endif

#define YYPACT_NINF -175

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-175)))

#define YYTABLE_NINF -102

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -175,    19,    27,  -175,  -175,    22,  -175,     9,    38,    22,
      28,    38,    40,    25,    33,  -175,    22,    24,    37,  -175,
    -175,  -175,    44,    45,  -175,  -175,  -175,  -175,    86,    87,
    -175,    81,    22,    91,  -175,  -175,    96,  -175,    22,    85,
      56,   102,    97,  -175,    22,   110,    97,   101,    81,  -175,
      50,    65,    85,  -175,  -175,    64,    63,   107,    69,   117,
      64,    77,    79,    82,    84,    92,    93,    23,   109,    98,
      94,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,   135,
      22,  -175,    85,   103,    22,    22,  -175,  -175,  -175,    22,
      15,  -175,  -175,  -175,  -175,     3,     3,   121,    22,    22,
     139,    31,    22,    -2,    31,  -175,    -3,  -175,    22,   142,
     108,   105,   111,  -175,  -175,   103,  -175,   112,   113,    97,
      22,   106,  -175,     3,   116,   143,   145,    43,     6,   118,
     123,   114,   124,   127,   128,  -175,  -175,   122,  -175,  -175,
     130,  -175,   129,  -175,  -175,  -175,  -175,   133,  -175,  -175,
    -175,    66,  -175,   103,   103,   120,  -175,  -175,  -175,  -175,
       3,   136,   140,     3,     3,   121,   121,  -175,   121,   -19,
    -175,   159,   160,  -175,   146,  -175,    -2,  -175,  -175,  -175,
      -2,  -175,    20,  -175,    22,    22,    22,   144,   137,   110,
     148,   149,  -175,   147,  -175,  -175,  -175,  -175,  -175,  -175,
     153,    22,    -2,     6,  -175,     6,  -175,  -175,   156,   157,
    -175,    22,  -175,  -175,  -175,  -175,  -175,   150,  -175,  -175,
     110,  -175,   110,  -175,   162,   158,   159,   160,   110,   163,
    -175,  -175,    66,  -175,   110,   110,   161,   164,    -2,  -175,
    -175,  -175,   166,  -175,  -175,   167,   168,  -175,  -175,   169,
    -175,  -175,  -175,   171,  -175,   170,  -175,  -175,   110,   172,
    -175
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     3,     0,     8,     0,    12,     0,
       0,    12,    13,     0,     0,    11,     0,     0,     0,     4,
      17,    14,     0,     0,    22,     5,    18,    15,     0,     0,
      22,    49,    35,     0,    24,     6,     0,    19,     0,    61,
      34,     0,    40,    23,    29,    81,    40,     0,    49,    46,
       0,     0,    50,    32,    31,     0,    39,     0,    28,     0,
       8,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    73,    74,    75,    76,    79,    80,    77,    78,     0,
      45,    21,    61,     0,     0,     0,    58,    16,    51,    35,
       0,    37,    36,    26,    25,   121,   121,   121,     0,     0,
       0,   121,     0,   121,   121,     7,    71,    30,     0,     0,
       0,    62,     0,    52,    55,     0,    33,     0,     0,    40,
      29,     0,   120,   121,     0,   107,   109,   115,     0,     0,
       0,     0,     0,     0,     0,    83,    82,     0,   104,   105,
       0,   100,   102,   106,    85,    84,    72,    44,    41,    20,
      64,     0,    47,     0,     0,     0,     9,    10,    38,    27,
     121,     0,     0,   121,   121,   121,   121,   126,   121,   132,
     129,   116,   122,   128,     0,    94,   121,   133,    95,    96,
     121,    99,   121,    42,     0,     0,     0,     0,    65,    81,
       0,     0,    59,     0,   112,    86,   108,   110,   114,   113,
       0,     0,   121,     0,   117,     0,   123,    92,     0,     0,
     103,    45,    68,    69,    70,    63,    66,     0,    53,    56,
      81,   111,    81,   127,     0,     0,   118,   124,    81,     0,
      98,    43,     0,    48,    81,    81,     0,     0,   121,   131,
     119,   125,     0,    97,    67,     0,     0,    60,    87,     0,
      93,    54,    57,    91,   130,     0,    88,    89,    81,     0,
      90
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -175,  -175,  -175,  -175,  -175,  -175,  -175,    -5,   -37,   182,
    -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,   126,  -175,
    -175,  -175,    99,  -175,  -175,  -175,   125,  -175,  -175,   -45,
    -175,  -175,     7,  -175,   173,  -175,  -175,   -40,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,  -105,  -175,   -15,  -175,  -175,
    -103,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,   -43,  -175,  -175,  -174,    41,  -175,   -82,    58,  -175,
     -66,    -6,  -175,    21,    -1,    26,  -175,  -175
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     5,    14,    29,    45,    67,    68,    10,
      11,    17,    24,    31,    23,    30,    48,    35,    27,    28,
      36,    44,    59,   120,    47,    33,    41,    89,    43,    57,
     119,    81,   109,   211,    39,    83,   189,    51,    52,   153,
     234,   154,   235,   115,   220,   112,   151,   187,   232,   188,
      69,    70,    71,    72,   222,   253,   256,   258,    73,   228,
      74,    75,    76,    77,   140,   141,   142,   124,   125,   126,
     127,   204,   128,   171,   206,   172,   173,    78
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       7,    79,   208,   146,    12,    56,   209,    60,    60,    56,
     155,    20,    88,    61,   129,    62,    60,    63,   121,     3,
      64,    65,    66,   201,   122,     6,   202,    40,   225,   122,
      60,   130,     6,    49,   167,   136,     4,   143,   145,    58,
      13,   161,   110,   117,  -101,    86,   122,   -81,   190,   191,
     123,   168,     8,    84,   101,    85,    66,   122,   135,     9,
       6,   144,    16,   134,   249,   102,   139,    21,   103,   184,
      18,   185,   165,   166,   158,   108,     6,    19,   193,   113,
     114,   196,    56,    22,    40,   118,   217,    25,    26,    32,
      34,   170,    38,   131,   132,   133,    42,   137,   138,   198,
     199,    46,   200,   147,    50,    53,    54,    55,    80,    87,
     143,    90,    91,    92,   143,    58,   143,   236,    93,   237,
      60,    94,    95,   169,    96,   242,    61,    97,    62,    98,
      63,   245,   246,    64,    65,    66,   143,    99,   100,   139,
     104,   107,   105,   139,   106,   139,   186,   122,   111,    60,
     148,   150,   149,   160,   152,   259,    37,   163,   164,   176,
     156,   157,   162,   192,   174,   139,   170,   180,   170,   175,
     177,   138,   143,   178,   179,   138,   181,   138,   182,   212,
     213,   214,   183,   195,   194,   203,   216,   205,   255,   207,
     215,   218,   219,    15,   233,   221,   224,   138,   169,   223,
     169,   139,   229,   230,   239,   247,   108,   238,   248,   243,
     250,   251,   252,   257,   116,   254,   260,   244,   231,   159,
     240,    82,   197,   210,   226,     0,   241,   186,     0,     0,
       0,   227,     0,   138
};

static const yytype_int16 yycheck[] =
{
       5,    46,   176,   106,     9,    42,   180,    10,    10,    46,
     115,    16,    52,    16,    96,    18,    10,    20,    15,     0,
      23,    24,    25,    42,    26,    10,    45,    32,   202,    26,
      10,    97,    10,    38,    28,   101,     9,   103,   104,    44,
      12,   123,    82,    28,    46,    50,    26,    50,   153,   154,
      47,    45,    43,     3,    31,     5,    25,    26,   101,    21,
      10,   104,    22,   100,   238,    42,   103,    43,    45,     3,
      45,     5,    29,    30,   119,    80,    10,    44,   160,    84,
      85,   163,   119,    46,    89,    90,   189,    43,    43,     3,
       3,   128,    11,    98,    99,   100,     5,   102,   103,   165,
     166,     5,   168,   108,    19,    49,     4,    10,     7,    44,
     176,    47,    49,     6,   180,   120,   182,   220,    49,   222,
      10,     4,    45,   128,    45,   228,    16,    45,    18,    45,
      20,   234,   235,    23,    24,    25,   202,    45,    45,   176,
      31,     6,    44,   180,    50,   182,   151,    26,    45,    10,
       8,    46,    44,    47,    43,   258,    30,    14,    13,    45,
      48,    48,    46,    43,    46,   202,   203,    45,   205,    46,
      46,   176,   238,    46,    46,   180,    46,   182,    49,   184,
     185,   186,    49,    43,    48,    26,    49,    27,    17,    43,
      46,    43,    43,    11,    44,    48,   201,   202,   203,    46,
     205,   238,    46,    46,    46,    44,   211,    45,    44,    46,
      44,    44,    44,    43,    89,    46,    44,   232,   211,   120,
     226,    48,   164,   182,   203,    -1,   227,   232,    -1,    -1,
      -1,   205,    -1,   238
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    52,    53,     0,     9,    54,    10,    58,    43,    21,
      60,    61,    58,    12,    55,    60,    22,    62,    45,    44,
      58,    43,    46,    65,    63,    43,    43,    69,    70,    56,
      66,    64,     3,    76,     3,    68,    71,    69,    11,    85,
      58,    77,     5,    79,    72,    57,     5,    75,    67,    58,
      19,    88,    89,    49,     4,    10,    59,    80,    58,    73,
      10,    16,    18,    20,    23,    24,    25,    58,    59,   101,
     102,   103,   104,   109,   111,   112,   113,   114,   128,    80,
       7,    82,    85,    86,     3,     5,    58,    44,    88,    78,
      47,    49,     6,    49,     4,    45,    45,    45,    45,    45,
      45,    31,    42,    45,    31,    44,    50,     6,    58,    83,
      88,    45,    96,    58,    58,    94,    77,    28,    58,    81,
      74,    15,    26,    47,   118,   119,   120,   121,   123,   118,
     121,    58,    58,    58,    59,   112,   121,    58,    58,    59,
     115,   116,   117,   121,   112,   121,   101,    58,     8,    44,
      46,    97,    43,    90,    92,    96,    48,    48,    80,    73,
      47,   118,    46,    14,    13,    29,    30,    28,    45,    58,
      59,   124,   126,   127,    46,    46,    45,    46,    46,    46,
      45,    46,    49,    49,     3,     5,    58,    98,   100,    87,
      96,    96,    43,   118,    48,    43,   118,   119,   121,   121,
     121,    42,    45,    26,   122,    27,   125,    43,   115,   115,
     116,    84,    58,    58,    58,    46,    49,   101,    43,    43,
      95,    48,   105,    46,    58,   115,   124,   126,   110,    46,
      46,    83,    99,    44,    91,    93,   101,   101,    45,    46,
     122,   125,   101,    46,    98,   101,   101,    44,    44,   115,
      44,    44,    44,   106,    46,    17,   107,    43,   108,   101,
      44
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    53,    54,    52,    56,    57,    55,    58,    59,
      59,    60,    60,    62,    63,    64,    61,    65,    66,    67,
      61,    68,    70,    69,    72,    71,    74,    73,    73,    73,
      75,    76,    78,    77,    77,    77,    79,    81,    80,    80,
      80,    82,    84,    83,    83,    83,    86,    87,    85,    85,
      88,    88,    90,    91,    89,    92,    93,    89,    94,    95,
      89,    89,    97,    96,    96,    98,    99,    98,   100,   100,
     100,   101,   101,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   103,   103,   103,   103,   105,   106,   104,   108,
     107,   107,   110,   109,   111,   112,   112,   113,   114,   114,
     115,   115,   116,   116,   117,   117,   117,   118,   118,   119,
     119,   120,   120,   120,   120,   120,   121,   121,   122,   122,
     123,   123,   124,   124,   125,   125,   126,   126,   126,   126,
     127,   127,   127,   128
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     8,     0,     0,     9,     1,     4,
       4,     2,     0,     0,     0,     0,    10,     0,     0,     0,
      12,     3,     0,     3,     0,     4,     0,     4,     1,     0,
       3,     3,     0,     4,     1,     0,     3,     0,     4,     1,
       0,     3,     0,     5,     2,     0,     0,     0,     8,     0,
       1,     2,     0,     0,     9,     0,     0,     9,     0,     0,
       8,     0,     0,     4,     2,     1,     0,     4,     2,     2,
       2,     2,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     3,     3,     3,     3,     0,     0,    10,     0,
       5,     0,     0,     8,     4,     4,     4,     7,     6,     4,
       1,     0,     1,     3,     1,     1,     1,     1,     3,     1,
       3,     4,     3,     3,     3,     1,     2,     3,     2,     3,
       1,     0,     1,     2,     2,     3,     1,     3,     1,     1,
       6,     4,     1,     4
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
#line 249 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"#include <stdio.h>\n#include <stdlib.h>\n\n"); }
#line 1674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 249 "yacc.y" /* yacc.c:1646  */
    {memset(class_info, 0, sizeof(class_info)); memset(main_objects, 0, sizeof(main_objects));}
#line 1680 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 252 "yacc.y" /* yacc.c:1646  */
    {class_count = class_count + 1; 
				 		  class_name = strdup((yyvsp[-3]));
				  		  addNameToClass(class_count,(yyvsp[-3])); fprintf(ResultsFile,"int main(){\n");}
#line 1688 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 254 "yacc.y" /* yacc.c:1646  */
    {printParameter();}
#line 1694 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 254 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"}\n");}
#line 1700 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 257 "yacc.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1706 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 260 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-3])) + strlen((yyvsp[-1])) + 3; malloc_func((yyval), len); sprintf((yyval), "%s[%s]",(yyvsp[-3]),(yyvsp[-1]));}
#line 1712 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 261 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-3])) + strlen((yyvsp[-1])) + 3; malloc_func((yyval), len); if (findParameter((yyvsp[-1]))==0){sprintf((yyval), "%s[self->%s]",(yyvsp[-3]),(yyvsp[-1]));}else{sprintf((yyval), "%s[%s]",(yyvsp[-3]),(yyvsp[-1]));}}
#line 1718 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 265 "yacc.y" /* yacc.c:1646  */
    {(yyval) = "";}
#line 1724 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 268 "yacc.y" /* yacc.c:1646  */
    {class_count = class_count + 1; 
				  class_name = strdup((yyvsp[0]));
				  addNameToClass(class_count,(yyvsp[0])); }
#line 1732 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 270 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"typedef struct {\n"); }
#line 1738 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 270 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"} %s;\n\n",(yyvsp[-4])); }
#line 1744 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 271 "yacc.y" /* yacc.c:1646  */
    {class_count = class_count + 1; 
				  class_name = strdup((yyvsp[-2]));
				  addNameToClass(class_count,(yyvsp[-2]));
				  addExtendNameToClass(class_count,(yyvsp[0])); }
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 274 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"typedef struct {\n"); }
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 274 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"} %s;\n\n",(yyvsp[-6])); }
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 280 "yacc.y" /* yacc.c:1646  */
    {createExtendedClassProperties(class_name);}
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 283 "yacc.y" /* yacc.c:1646  */
    {memset(parameters, 0, sizeof(parameters));}
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 286 "yacc.y" /* yacc.c:1646  */
    {addParameterToArray((yyvsp[-1]));
					fprintf(ResultsFile,"int %s;\n",(yyvsp[-1]));}
#line 1784 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 288 "yacc.y" /* yacc.c:1646  */
    {addParameterToArray((yyvsp[0])); fprintf(ResultsFile,"int %s;\n",(yyvsp[0]));}
#line 1790 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 289 "yacc.y" /* yacc.c:1646  */
    {(yyval) = "";}
#line 1796 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 303 "yacc.y" /* yacc.c:1646  */
    {addVarToClass(class_name,(yyvsp[-1]));
					fprintf(ResultsFile,"int %s;\n",(yyvsp[-1]));}
#line 1803 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 305 "yacc.y" /* yacc.c:1646  */
    {addVarToClass(class_name,(yyvsp[0])); fprintf(ResultsFile,"int %s;\n",(yyvsp[0]));}
#line 1809 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 306 "yacc.y" /* yacc.c:1646  */
    {(yyval) = "";}
#line 1815 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 312 "yacc.y" /* yacc.c:1646  */
    {addTableToClass(class_name,(yyvsp[-1])); fprintf(ResultsFile,"int %s;\n",(yyvsp[-1]));}
#line 1821 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 313 "yacc.y" /* yacc.c:1646  */
    {addTableToClass(class_name,(yyvsp[0])); fprintf(ResultsFile,"int %s;\n",(yyvsp[0]));}
#line 1827 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 314 "yacc.y" /* yacc.c:1646  */
    {(yyval) = "";}
#line 1833 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 320 "yacc.y" /* yacc.c:1646  */
    {addObjectToArray((yyvsp[-2]), (yyvsp[-1])); createStructForObject((yyvsp[-2]),(yyvsp[-1]));}
#line 1839 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 321 "yacc.y" /* yacc.c:1646  */
    {addObjectToArray((yyvsp[-1]), (yyvsp[0])); createStructForObject((yyvsp[-1]),(yyvsp[0]));}
#line 1845 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 322 "yacc.y" /* yacc.c:1646  */
    {(yyval) = "";}
#line 1851 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 325 "yacc.y" /* yacc.c:1646  */
    {if (class_name && strcmp(class_name,(yyvsp[0]))!=0){yyerror("Error: Constructor should has the same name with class\n");} addMethodToClass(class_name, (yyvsp[0]));fprintf(ResultsFile,"void %s_%s",(yyvsp[0]),(yyvsp[0]));}
#line 1857 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 325 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"{\n");}
#line 1863 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 325 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"}\n\n");}
#line 1869 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 326 "yacc.y" /* yacc.c:1646  */
    {(yyval) = "";}
#line 1875 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 333 "yacc.y" /* yacc.c:1646  */
    {addMethodToClass(class_name, (yyvsp[0])); fprintf(ResultsFile,"int %s_%s",class_name,(yyvsp[0]));}
#line 1881 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 333 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"{\n");}
#line 1887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 333 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"}\n\n");}
#line 1893 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 334 "yacc.y" /* yacc.c:1646  */
    {addMethodToClass(class_name, (yyvsp[0])); fprintf(ResultsFile,"int[] %s_%s",class_name,(yyvsp[0]));}
#line 1899 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 334 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"{\n");}
#line 1905 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 334 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"}\n\n");}
#line 1911 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 335 "yacc.y" /* yacc.c:1646  */
    {addMethodToClass(class_name, (yyvsp[0])); fprintf(ResultsFile,"void %s_%s",class_name,(yyvsp[0]));}
#line 1917 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 335 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"{\n");}
#line 1923 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 335 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"}\n\n");}
#line 1929 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 336 "yacc.y" /* yacc.c:1646  */
    {(yyval) = "";}
#line 1935 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 339 "yacc.y" /* yacc.c:1646  */
    {memset(parameters, 0, sizeof(parameters)); fprintf(ResultsFile,"(%s* self,",class_name);}
#line 1941 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 339 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,")");}
#line 1947 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 340 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"(%s* self)",class_name); (yyval) = "";}
#line 1953 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 343 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"%s",(yyvsp[0]));}
#line 1959 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 344 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"%s, ",(yyvsp[-1]));}
#line 1965 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 347 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-1])) + strlen((yyvsp[0])) + 1; malloc_func((yyval), len); sprintf((yyval),"int %s",(yyvsp[0])); addParameterToArray((yyvsp[0]));}
#line 1971 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 348 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-1])) + strlen((yyvsp[0])) + 1; malloc_func((yyval), len); sprintf((yyval),"int %s[]",(yyvsp[0])); addParameterToArray((yyvsp[0]));}
#line 1977 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 349 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-1])) + strlen((yyvsp[0])) + 1; malloc_func((yyval), len); sprintf((yyval),"%s %s",(yyvsp[-1]),(yyvsp[0])); addParameterToArray((yyvsp[0]));}
#line 1983 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 356 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"%s;\n",(yyvsp[0]));}
#line 1989 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 360 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"%s;\n",(yyvsp[0]));}
#line 1995 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 364 "yacc.y" /* yacc.c:1646  */
    {(yyval) = "";}
#line 2001 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 367 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-2])) + strlen((yyvsp[0])) + 7; malloc_func((yyval), len); if (findParameter((yyvsp[-2]))==0){sprintf((yyval),"self->%s = %s",(yyvsp[-2]),(yyvsp[0]));}else{sprintf((yyval),"%s = %s",(yyvsp[-2]),(yyvsp[0]));} }
#line 2007 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 368 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-2])) + strlen((yyvsp[0])) + 7; malloc_func((yyval), len); if (findParameter((yyvsp[-2]))==0){sprintf((yyval),"self->%s = %s",(yyvsp[-2]),(yyvsp[0]));}else{sprintf((yyval),"%s = %s",(yyvsp[-2]),(yyvsp[0]));}}
#line 2013 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 369 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-2])) + strlen((yyvsp[0])) + 7; malloc_func((yyval), len); char *str = strdup((yyvsp[-2])); if (findParameter(strtok(str,"["))==0){sprintf((yyval),"self->%s = %s",(yyvsp[-2]),(yyvsp[0]));}else{sprintf((yyval),"%s = %s",(yyvsp[-2]),(yyvsp[0]));}}
#line 2019 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 370 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-2])) + strlen((yyvsp[0])) + 7; malloc_func((yyval), len); char *str = strdup((yyvsp[-2])); if (findParameter(strtok(str,"["))==0){sprintf((yyval),"self->%s = %s",(yyvsp[-2]),(yyvsp[0]));}else{sprintf((yyval),"%s = %s",(yyvsp[-2]),(yyvsp[0]));}}
#line 2025 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 373 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"if (%s){\n",(yyvsp[-2]));}
#line 2031 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 373 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"}\n");}
#line 2037 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 376 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"else{\n");}
#line 2043 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 376 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"}\n");}
#line 2049 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 377 "yacc.y" /* yacc.c:1646  */
    {(yyval) = "";}
#line 2055 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 380 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"while (%s){\n",(yyvsp[-2]));}
#line 2061 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 380 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"}\n");}
#line 2067 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 383 "yacc.y" /* yacc.c:1646  */
    {fprintf(ResultsFile,"return (%s);\n",(yyvsp[-1]));}
#line 2073 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 386 "yacc.y" /* yacc.c:1646  */
    {char *str = "scanf(\"%"; fprintf(ResultsFile,"%s",str); if (findParameter((yyvsp[-3]))==0){fprintf(ResultsFile,"d\",&(self->%s));\n",(yyvsp[-1]));}else{fprintf(ResultsFile,"d\",&%s);\n",(yyvsp[-1]));}}
#line 2079 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 387 "yacc.y" /* yacc.c:1646  */
    {char *str = "scanf(\"%"; fprintf(ResultsFile,"%s",str); if (findParameter((yyvsp[-3]))==0){fprintf(ResultsFile,"d\",&(self->%s));\n",(yyvsp[-1]));}else{fprintf(ResultsFile,"d\",&%s);\n",(yyvsp[-1]));}}
#line 2085 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 390 "yacc.y" /* yacc.c:1646  */
    {superCall(class_name, (yyvsp[-4]), (yyvsp[-2]));}
#line 2091 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 393 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-5])) + strlen((yyvsp[-3])) + strlen((yyvsp[-1])) + 4; malloc_func((yyval), len);char *str = NULL; str = findClassFromObject((yyvsp[-5])); if(str){if(strcmp((yyvsp[-1]),")") != 0){ sprintf((yyval),"%s_%s(&%s,%s",findMethod(str,(yyvsp[-3])),(yyvsp[-3]),(yyvsp[-5]),(yyvsp[-1]));}else{sprintf((yyval),"%s_%s(&%s%s",findMethod(str,(yyvsp[-3])),(yyvsp[-3]),(yyvsp[-5]),(yyvsp[-1]));}}}
#line 2097 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 394 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-3])) + strlen((yyvsp[-1])) + 3; malloc_func((yyval), len);if(strcmp((yyvsp[-1]),")") != 0){ sprintf((yyval),"%s_%s(&self,%s",class_name,(yyvsp[-3]),(yyvsp[-1]));}else{sprintf((yyval),"%s_%s(&self%s",class_name,(yyvsp[-3]),(yyvsp[-1]));} }
#line 2103 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 397 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[0])) + 2; malloc_func((yyval), len); sprintf((yyval),"%s)",(yyvsp[0]));}
#line 2109 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 398 "yacc.y" /* yacc.c:1646  */
    {malloc_func((yyval), 3); sprintf((yyval),")");}
#line 2115 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 401 "yacc.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2121 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 402 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-2])) + strlen((yyvsp[0])) + 2; malloc_func((yyval), len); sprintf((yyval),"%s, %s",(yyvsp[-2]),(yyvsp[0]));}
#line 2127 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 405 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[0])) + 1; malloc_func((yyval), len); sprintf((yyval),"%s",(yyvsp[0]));}
#line 2133 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 406 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[0])) + 1; malloc_func((yyval), len); sprintf((yyval),"%s",(yyvsp[0]));}
#line 2139 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 407 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[0])) + 1; malloc_func((yyval), len); sprintf((yyval),"%s",(yyvsp[0]));}
#line 2145 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 410 "yacc.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2151 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 411 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-2])) + strlen((yyvsp[0])) + 3; malloc_func((yyval), len); sprintf((yyval),"%s || %s",(yyvsp[-2]),(yyvsp[0]));}
#line 2157 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 414 "yacc.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2163 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 415 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-2])) + strlen((yyvsp[0])) + 3; malloc_func((yyval), len); sprintf((yyval),"%s && %s",(yyvsp[-2]),(yyvsp[0]));}
#line 2169 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 418 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-1])) + 4; malloc_func((yyval), len); sprintf((yyval),"![ %s ]",(yyvsp[-1]));}
#line 2175 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 419 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-1])) + 3; malloc_func((yyval), len); sprintf((yyval),"[ %s ]",(yyvsp[-1]));}
#line 2181 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 420 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-2])) + strlen((yyvsp[-1])) + strlen((yyvsp[0])) + 1; malloc_func((yyval), len); sprintf((yyval),"%s %s %s",(yyvsp[-2]),(yyvsp[-1]),(yyvsp[0]));}
#line 2187 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 421 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-2])) + strlen((yyvsp[0])) + 3; malloc_func((yyval), len); sprintf((yyval),"%s != %s",(yyvsp[-2]),(yyvsp[0]));}
#line 2193 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 422 "yacc.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2199 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 425 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-1])) 
+ strlen((yyvsp[0])) + 1; malloc_func((yyval), len); sprintf((yyval),"%s%s",(yyvsp[-1]),(yyvsp[0]));}
#line 2206 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 427 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-2])) + strlen((yyvsp[-1])) + strlen((yyvsp[0])) + 1; malloc_func((yyval), len); sprintf((yyval),"%s%s%s",(yyvsp[-2]),(yyvsp[-1]),(yyvsp[0]));}
#line 2212 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 430 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-1])) + strlen((yyvsp[0])) + 1; malloc_func((yyval), len); sprintf((yyval),"%s%s",(yyvsp[-1]),(yyvsp[0]));}
#line 2218 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 431 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-2])) + strlen((yyvsp[-1])) + strlen((yyvsp[0])) + 1; malloc_func((yyval), len); sprintf((yyval),"%s%s%s",(yyvsp[-2]),(yyvsp[-1]),(yyvsp[0]));}
#line 2224 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 434 "yacc.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2230 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 435 "yacc.y" /* yacc.c:1646  */
    {(yyval) = "";}
#line 2236 "y.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 438 "yacc.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2242 "y.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 439 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-1])) + strlen((yyvsp[0])) + 1; malloc_func((yyval), len); sprintf((yyval),"%s%s",(yyvsp[-1]),(yyvsp[0]));}
#line 2248 "y.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 442 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-1])) + strlen((yyvsp[0])) + 1; malloc_func((yyval), len); sprintf((yyval),"%s%s",(yyvsp[-1]),(yyvsp[0]));}
#line 2254 "y.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 443 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-2])) + strlen((yyvsp[-1])) + strlen((yyvsp[0])) + 1; malloc_func((yyval), len); sprintf((yyval),"%s%s%s",(yyvsp[-2]),(yyvsp[-1]),(yyvsp[0]));}
#line 2260 "y.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 446 "yacc.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2266 "y.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 447 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-1])) + 3; malloc_func((yyval), len); sprintf((yyval),"(%s)",(yyvsp[-1]));}
#line 2272 "y.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 448 "yacc.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2278 "y.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 449 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[0])) + 1; malloc_func((yyval), len); char *str = strdup((yyvsp[0])); if (findParameter(strtok(str,"["))==0){sprintf((yyval),"self->%s",(yyvsp[0]));}else{sprintf((yyval),"%s",(yyvsp[0]));}}
#line 2284 "y.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 452 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-5])) + strlen((yyvsp[-3])) + strlen((yyvsp[-1])) + 30; malloc_func((yyval), len);char *str = NULL; str = findClassFromObject((yyvsp[-5])); if(str){if(strcmp((yyvsp[-1]),")") != 0){sprintf((yyval),"%s_%s(&%s,%s",findMethod(str,(yyvsp[-3])),(yyvsp[-3]),(yyvsp[-5]),(yyvsp[-1]));}else{sprintf((yyval),"%s_%s(&%s%s",findMethod(str,(yyvsp[-3])),(yyvsp[-3]),(yyvsp[-5]),(yyvsp[-1]));}}}
#line 2290 "y.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 453 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[-3])) + strlen((yyvsp[-1])) + strlen(class_name) + 9; malloc_func((yyval), len); if(strcmp((yyvsp[-1]),")") != 0){sprintf((yyval),"%s_%s(&self, %s",class_name,(yyvsp[-3]),(yyvsp[-1]));}else{sprintf((yyval),"%s_%s(&self%s",class_name,(yyvsp[-3]),(yyvsp[-1]));}}
#line 2296 "y.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 454 "yacc.y" /* yacc.c:1646  */
    {int len = strlen((yyvsp[0])) + 1; malloc_func((yyval), len); if (findParameter((yyvsp[0]))==0){sprintf((yyval),"self->%s",(yyvsp[0]));}else{sprintf((yyval),"%s",(yyvsp[0]));}}
#line 2302 "y.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 457 "yacc.y" /* yacc.c:1646  */
    {char *str = "printf(\"%"; fprintf(ResultsFile,"%s",str); if (findParameter((yyvsp[-1]))==0){ fprintf(ResultsFile,"d\\n\",self->%s);\n",(yyvsp[-1]));} else{fprintf(ResultsFile,"d\\n\",%s);\n",(yyvsp[-1]));}}
#line 2308 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2312 "y.tab.c" /* yacc.c:1646  */
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
#line 460 "yacc.y" /* yacc.c:1906  */


extern int column;
extern int line;

int main(){

	extern FILE *yyin;
	char file[30];
	printf("Enter file name: ");
	scanf("%s",file);

	char filenameTxt[30];
	strcpy(filenameTxt,file);

	char filenameC[30];
	strcpy(filenameC,file);

	strcat(filenameTxt,".txt");
	strcat(filenameC,".c");
 	yyin=fopen(filenameTxt,"r");
 	if(yyin==NULL){
  		fprintf(stderr, "Error opening file.\n");
 	}
	ResultsFile = fopen(filenameC, "w");
    if (ResultsFile == NULL) {
    	fprintf(stderr, "Error creating output file.\n");
     	return 1;
    }
 	yyparse();
    fclose(yyin);
    fclose(ResultsFile);

    return 0;
}

yyerror(s)
char *s;
{
	fflush(stdout);
	printf("Error, not expected character in line: %d and column: %d %s\n", line, column,s);
}



