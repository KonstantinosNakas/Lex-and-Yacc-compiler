
%{
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
%}



%token VAR ENDVAR TABLE ENDTABLE OBJECT ENDOBJECT PROGRAM IDENT CONSTRUCTOR MAIN
%token AND OR NOT
%token IF ELSE WHILE
%token FUNCTION RETURN CLASS EXTENDS SUPER
%token PRINT INPUT
%token ADDSUBOPS MULDIVOPS CONST DIFF RELATOP ASSIGN


%left  AND OR 
%left  "!=" '<' "<=" '>' ">=" "==" 
%left  '+' '-' 
%left  '*' '/' 
%left NOT
%left  '.'

%start program

%%
program:	{fprintf(ResultsFile,"#include <stdio.h>\n#include <stdlib.h>\n\n"); }PROGRAM {memset(class_info, 0, sizeof(class_info)); memset(main_objects, 0, sizeof(main_objects));} ID '{' programblock main '}' 
			;

main:	MAIN '(' ')' '{' {class_count = class_count + 1; 
				 		  class_name = strdup($1);
				  		  addNameToClass(class_count,$1); fprintf(ResultsFile,"int main(){\n");} declarations_main sequence '}' {fprintf(ResultsFile,"}\n");}
		;

ID:	IDENT {$$ = $1;}
	;

IDTABLE: IDENT '[' CONST ']' {int len = strlen($1) + strlen($3) + 3; malloc_func($$, len); sprintf($$, "%s[%s]",$1,$3);}
		 |IDENT '[' ID ']' {int len = strlen($1) + strlen($3) + 3; malloc_func($$, len); if (findParameter($3)==0){sprintf($$, "%s[self->%s]",$1,$3);}else{sprintf($$, "%s[%s]",$1,$3);}}
		 ;

programblock:	class programblock
				|{$$ = "";}
				;

class:	CLASS ID {class_count = class_count + 1; 
				  class_name = strdup($2);
				  addNameToClass(class_count,$2); } '{' {fprintf(ResultsFile,"typedef struct {\n"); } declarations  {fprintf(ResultsFile,"} %s;\n\n",$2); } constructors  function  '}'
		|CLASS ID EXTENDS ID {class_count = class_count + 1; 
				  class_name = strdup($2);
				  addNameToClass(class_count,$2);
				  addExtendNameToClass(class_count,$4); } '{' {fprintf(ResultsFile,"typedef struct {\n"); } declarations {fprintf(ResultsFile,"} %s;\n\n",$2); }  constructors  function  '}'
		;

declarations_main:	vardecmain tabledecmain objdec
				;

declarations: {createExtendedClassProperties(class_name);} vardec tabledec
				;

vardecmain:	VAR {memset(parameters, 0, sizeof(parameters));} varrepeatmain ENDVAR
		;

varrepeatmain:	ID ',' {addParameterToArray($1);
					fprintf(ResultsFile,"int %s;\n",$1);} varrepeatmain
			|ID {addParameterToArray($1); fprintf(ResultsFile,"int %s;\n",$1);}
			|{$$ = "";}
			;

tabledecmain:	TABLE tablerepeatmain ENDTABLE
			;

tablerepeatmain:IDTABLE ',' {addParameterToArray($1); fprintf(ResultsFile,"int %s;\n",$1);} tablerepeatmain
				|IDTABLE {addParameterToArray($1); fprintf(ResultsFile,"int %s;\n",$1);}
				|{$$ = "";}
				;

vardec:	VAR varrepeat ENDVAR
		;

varrepeat:	ID ',' {addVarToClass(class_name,$1);
					fprintf(ResultsFile,"int %s;\n",$1);} varrepeat
			|ID {addVarToClass(class_name,$1); fprintf(ResultsFile,"int %s;\n",$1);}
			|{$$ = "";}
			;		

tabledec:	TABLE tablerepeat ENDTABLE
			;

tablerepeat:	IDTABLE ',' {addTableToClass(class_name,$1); fprintf(ResultsFile,"int %s;\n",$1);} tablerepeat
				|IDTABLE {addTableToClass(class_name,$1); fprintf(ResultsFile,"int %s;\n",$1);}
				|{$$ = "";}
				;

objdec:   OBJECT objectrepeat ENDOBJECT
	   	  ;

objectrepeat:	ID ID ',' {addObjectToArray($1, $2); createStructForObject($1,$2);} objectrepeat 
				|ID ID {addObjectToArray($1, $2); createStructForObject($1,$2);}
				|{$$ = "";}
				;		

constructors:	CONSTRUCTOR ID {if (class_name && strcmp(class_name,$2)!=0){yyerror("Error: Constructor should has the same name with class\n");} addMethodToClass(class_name, $2);fprintf(ResultsFile,"void %s_%s",$2,$2);} formalpars  '{' {fprintf(ResultsFile,"{\n");} sequence'}' {fprintf(ResultsFile,"}\n\n");}
				|{$$ = "";}
				;

function: functionrep
		  |functionrep function
		  ;

functionrep:	FUNCTION VAR ID {addMethodToClass(class_name, $3); fprintf(ResultsFile,"int %s_%s",class_name,$3);} formalpars '{' {fprintf(ResultsFile,"{\n");} sequence '}' {fprintf(ResultsFile,"}\n\n");}
			|FUNCTION TABLE ID {addMethodToClass(class_name, $3); fprintf(ResultsFile,"int[] %s_%s",class_name,$3);} formalpars '{' {fprintf(ResultsFile,"{\n");} sequence '}' {fprintf(ResultsFile,"}\n\n");}
			|FUNCTION ID {addMethodToClass(class_name, $2); fprintf(ResultsFile,"void %s_%s",class_name,$2);} formalpars '{' {fprintf(ResultsFile,"{\n");} sequence '}' {fprintf(ResultsFile,"}\n\n");}
			|{$$ = "";}
			;

formalpars: 	'('{memset(parameters, 0, sizeof(parameters)); fprintf(ResultsFile,"(%s* self,",class_name);} formalparlist ')' {fprintf(ResultsFile,")");}
				|'(' ')'  {fprintf(ResultsFile,"(%s* self)",class_name); $$ = "";}
				;

formalparlist:	formalparitem  {fprintf(ResultsFile,"%s",$1);}
				|formalparitem ',' {fprintf(ResultsFile,"%s, ",$1);} formalparlist
				;

formalparitem:	VAR ID {int len = strlen($1) + strlen($2) + 1; malloc_func($$, len); sprintf($$,"int %s",$2); addParameterToArray($2);}
				|TABLE ID {int len = strlen($1) + strlen($2) + 1; malloc_func($$, len); sprintf($$,"int %s[]",$2); addParameterToArray($2);}
				|ID ID {int len = strlen($1) + strlen($2) + 1; malloc_func($$, len); sprintf($$,"%s %s",$1,$2); addParameterToArray($2);}
				;

sequence:	statement ';'
			|statement ';' sequence
			;

statement:	assignment {fprintf(ResultsFile,"%s;\n",$1);}
			|if
			|while
			|return
			|call {fprintf(ResultsFile,"%s;\n",$1);}
			|print
			|input
			|super
			|{$$ = "";}
			;

assignment:	ID ASSIGN expr {int len = strlen($1) + strlen($3) + 7; malloc_func($$, len); if (findParameter($1)==0){sprintf($$,"self->%s = %s",$1,$3);}else{sprintf($$,"%s = %s",$1,$3);} }
			|ID ASSIGN input {int len = strlen($1) + strlen($3) + 7; malloc_func($$, len); if (findParameter($1)==0){sprintf($$,"self->%s = %s",$1,$3);}else{sprintf($$,"%s = %s",$1,$3);}}
			|IDTABLE ASSIGN expr {int len = strlen($1) + strlen($3) + 7; malloc_func($$, len); char *str = strdup($1); if (findParameter(strtok(str,"["))==0){sprintf($$,"self->%s = %s",$1,$3);}else{sprintf($$,"%s = %s",$1,$3);}}
			|IDTABLE ASSIGN input {int len = strlen($1) + strlen($3) + 7; malloc_func($$, len); char *str = strdup($1); if (findParameter(strtok(str,"["))==0){sprintf($$,"self->%s = %s",$1,$3);}else{sprintf($$,"%s = %s",$1,$3);}}
			;

if:	IF '(' condition ')' '{'  {fprintf(ResultsFile,"if (%s){\n",$3);}  sequence '}' {fprintf(ResultsFile,"}\n");} else
	;

else:	ELSE '{'  {fprintf(ResultsFile,"else{\n");} sequence '}' {fprintf(ResultsFile,"}\n");}
		|{$$ = "";}
		;

while:	WHILE '(' condition ')' '{' {fprintf(ResultsFile,"while (%s){\n",$3);} sequence '}' {fprintf(ResultsFile,"}\n");}
		;

return:	RETURN '(' expr ')' {fprintf(ResultsFile,"return (%s);\n",$3);}
		;

input:	INPUT '(' ID ')' {char *str = "scanf(\"%"; fprintf(ResultsFile,"%s",str); if (findParameter($1)==0){fprintf(ResultsFile,"d\",&(self->%s));\n",$3);}else{fprintf(ResultsFile,"d\",&%s);\n",$3);}}
		|INPUT '(' IDTABLE ')' {char *str = "scanf(\"%"; fprintf(ResultsFile,"%s",str); if (findParameter($1)==0){fprintf(ResultsFile,"d\",&(self->%s));\n",$3);}else{fprintf(ResultsFile,"d\",&%s);\n",$3);}}
		;

super:	SUPER '(' ID '(' actualpars ')' ')' {superCall(class_name, $3, $5);}
		;

call:	ID '.' ID '(' actualpars ')' {int len = strlen($1) + strlen($3) + strlen($5) + 4; malloc_func($$, len);char *str = NULL; str = findClassFromObject($1); if(str){if(strcmp($5,")") != 0){ sprintf($$,"%s_%s(&%s,%s",findMethod(str,$3),$3,$1,$5);}else{sprintf($$,"%s_%s(&%s%s",findMethod(str,$3),$3,$1,$5);}}}
		|ID '(' actualpars ')' {int len = strlen($1) + strlen($3) + 3; malloc_func($$, len);if(strcmp($3,")") != 0){ sprintf($$,"%s_%s(&self,%s",class_name,$1,$3);}else{sprintf($$,"%s_%s(&self%s",class_name,$1,$3);} }
		;

actualpars:	actualparlist {int len = strlen($1) + 2; malloc_func($$, len); sprintf($$,"%s)",$1);}
			|{malloc_func($$, 3); sprintf($$,")");}
			;

actualparlist:	actualparitem {$$ = $1;}
				|actualparitem ',' actualparlist {int len = strlen($1) + strlen($3) + 2; malloc_func($$, len); sprintf($$,"%s, %s",$1,$3);}
				;

actualparitem:	ID {int len = strlen($1) + 1; malloc_func($$, len); sprintf($$,"%s",$1);}
				|IDTABLE {int len = strlen($1) + 1; malloc_func($$, len); sprintf($$,"%s",$1);}
				|expr {int len = strlen($1) + 1; malloc_func($$, len); sprintf($$,"%s",$1);}
				;

condition:	bterm {$$ = $1;}
			|bterm OR condition {int len = strlen($1) + strlen($3) + 3; malloc_func($$, len); sprintf($$,"%s || %s",$1,$3);}
			;

bterm:	bfactor {$$ = $1;}
		|bfactor AND bterm {int len = strlen($1) + strlen($3) + 3; malloc_func($$, len); sprintf($$,"%s && %s",$1,$3);}
		;

bfactor:	NOT '[' condition ']' {int len = strlen($3) + 4; malloc_func($$, len); sprintf($$,"![ %s ]",$3);}
			|'[' condition ']' {int len = strlen($2) + 3; malloc_func($$, len); sprintf($$,"[ %s ]",$2);}
			|expr RELATOP expr {int len = strlen($1) + strlen($2) + strlen($3) + 1; malloc_func($$, len); sprintf($$,"%s %s %s",$1,$2,$3);}
			|expr DIFF expr {int len = strlen($1) + strlen($3) + 3; malloc_func($$, len); sprintf($$,"%s != %s",$1,$3);}
			|expr {$$ = $1;}
			;
	
expr:	optsign term {int len = strlen($1) 
+ strlen($2) + 1; malloc_func($$, len); sprintf($$,"%s%s",$1,$2);}
		|optsign term optsignterm {int len = strlen($1) + strlen($2) + strlen($3) + 1; malloc_func($$, len); sprintf($$,"%s%s%s",$1,$2,$3);}
		;

optsignterm:	ADDSUBOPS term {int len = strlen($1) + strlen($2) + 1; malloc_func($$, len); sprintf($$,"%s%s",$1,$2);}
				|ADDSUBOPS term optsignterm {int len = strlen($1) + strlen($2) + strlen($3) + 1; malloc_func($$, len); sprintf($$,"%s%s%s",$1,$2,$3);}
				;
				
optsign:	ADDSUBOPS {$$ = $1;}
			|{$$ = "";}
			;

term:	factor {$$ = $1;}
		|factor optsignfactor {int len = strlen($1) + strlen($2) + 1; malloc_func($$, len); sprintf($$,"%s%s",$1,$2);}
		;

optsignfactor:	MULDIVOPS factor {int len = strlen($1) + strlen($2) + 1; malloc_func($$, len); sprintf($$,"%s%s",$1,$2);}
				|MULDIVOPS factor optsignfactor {int len = strlen($1) + strlen($2) + strlen($3) + 1; malloc_func($$, len); sprintf($$,"%s%s%s",$1,$2,$3);}
				;

factor:	CONST {$$ = $1;}
		|'(' expr ')' {int len = strlen($2) + 3; malloc_func($$, len); sprintf($$,"(%s)",$2);} 
		|funccall {$$ = $1;}
		|IDTABLE {int len = strlen($1) + 1; malloc_func($$, len); char *str = strdup($1); if (findParameter(strtok(str,"["))==0){sprintf($$,"self->%s",$1);}else{sprintf($$,"%s",$1);}}
		;

funccall:	ID '.' ID '('  actualpars ')' {int len = strlen($1) + strlen($3) + strlen($5) + 30; malloc_func($$, len);char *str = NULL; str = findClassFromObject($1); if(str){if(strcmp($5,")") != 0){sprintf($$,"%s_%s(&%s,%s",findMethod(str,$3),$3,$1,$5);}else{sprintf($$,"%s_%s(&%s%s",findMethod(str,$3),$3,$1,$5);}}}
			|ID '(' actualpars ')' {int len = strlen($1) + strlen($3) + strlen(class_name) + 9; malloc_func($$, len); if(strcmp($3,")") != 0){sprintf($$,"%s_%s(&self, %s",class_name,$1,$3);}else{sprintf($$,"%s_%s(&self%s",class_name,$1,$3);}}
			|ID {int len = strlen($1) + 1; malloc_func($$, len); if (findParameter($1)==0){sprintf($$,"self->%s",$1);}else{sprintf($$,"%s",$1);}}
			;

print:	PRINT '(' ID ')' {char *str = "printf(\"%"; fprintf(ResultsFile,"%s",str); if (findParameter($3)==0){ fprintf(ResultsFile,"d\\n\",self->%s);\n",$3);} else{fprintf(ResultsFile,"d\\n\",%s);\n",$3);}}
		;
	
%%

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



