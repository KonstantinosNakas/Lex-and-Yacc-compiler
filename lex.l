
DIGIT		[0-9]
ID			[a-zA-Z][a-zA-Z0-9_]*
ADDSUBOPS	[\+\-]
MULDIVOPS	[\*\/]
ASSIGN 		[=]
RELATOPS	[><][=]?|={2}

%{
#include <stdio.h>
#include "y.tab.h"

int column = 0;
int line = 1;

void count(){
	int i ;
	printf(" ");
	for(i = 0 ; yytext[i] != '\0' ; i++){
		if(yytext[i] == '\n'){
			column = 0;
		}else if(yytext[i] == '\t'){
			column += 8 - (column % 8);
		}else{
			column++;
		}
	}
}

%}


%%
"$$"		{comment();}
"program"	{count(); return(PROGRAM);}
"constructor" {count(); return(CONSTRUCTOR);}
"var"		{count(); return(VAR);}
"endvar"	{count(); return(ENDVAR);}
"table"		{count(); return(TABLE);}
"endtable"	{count(); return(ENDTABLE);}
"object"	{count(); return(OBJECT);}
"endobject"	{count(); return(ENDOBJECT);}
"and"		{count(); return(AND);}
"or"		{count(); return(OR);}
"if"		{count(); return(IF);}
"else"		{count(); return(ELSE);}
"function"	{count(); return(FUNCTION);}
"print"		{count(); return(PRINT);}
"not"		{count(); return(NOT);}
"return"	{count(); return(RETURN);}
"while"		{count(); return(WHILE);}
"input"		{count(); return(INPUT);}
"class"		{count(); return(CLASS);}
"extends"	{count(); return(EXTENDS);}
"super"		{count(); return(SUPER);}
"main"		{count(); return(MAIN);}

{DIGIT}+	{count(); yylval = strdup(yytext); return(CONST);}
{ID}		{count(); yylval = strdup(yytext); return(IDENT);}
{ADDSUBOPS}	{count(); yylval = strdup(yytext); return(ADDSUBOPS);}
{MULDIVOPS}	{count(); yylval = strdup(yytext); return(MULDIVOPS);}
{RELATOPS}	{count(); yylval = strdup(yytext); return(RELATOP);}
{ASSIGN}	{count(); yylval = strdup(yytext); return(ASSIGN);}
"!=" 		{count(); yylval = strdup(yytext); return(DIFF);}
"("			{count(); return('(');}
")"			{count(); return(')');}
"["			{count(); return('[');}
"]"			{count(); return(']');}
"{"			{count(); return('{');}
"}"			{count(); return('}');}
";"			{count(); return(';');}
","			{count(); return(',');}
"."			{count(); return('.');}
[ \t]       {count();}
"\n"		{count(); line = line + 1;}
.			{count(); yyerror(yytext);}

%%


yywrap()
{
	return(1);
}

comment()
{
	char c, c1;

loop:
	while ((c = input()) != '$' && c != 0){
		if(c == '\n' && c != 0){
			line = line + 1;
		}
	}
	if ((c1 = input()) != '$' && c != 0)
	{
		unput(c1);
		goto loop;
	}
		
}

