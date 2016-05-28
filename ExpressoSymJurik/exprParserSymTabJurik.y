
%{

/*
Andrew Jurik
CS435
Scanner & Parser & Symbol Table
*/

#define TABLE_SIZE 397
#define MAX_IDENT 150

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 
typedef struct node_t Node;
typedef enum Obj_Type Object_Type;
typedef enum Obj_Binding Object_Binding;
typedef enum {false, true} bool;

enum Obj_Type {INT, LONG, UNSIGNED_LONG, STRING, DOUBLE, CHARACTER, ARRAY};
enum Obj_Binding {CONSTANT, VARIABLE, FNAME};

struct node_t{

	char* name;
	unsigned address;
	Object_Type type;
	Object_Binding attributes;
	Node* next;
};

Node table[TABLE_SIZE];
int lines = 1;
extern char* yytext;
FILE *listingFile;
errno_t fileErrorCode = 1;
errno_t redefinitionErrorCode = 2;
errno_t undeclaredErrorCode = 3;
int identNum = 0;

int yylex(void);
void yyerror(char *);
int hash(char* key);
void getKey(char* line, char* key);
void procIdent(YYSTYPE);
void insert(char* key);
bool find(char* key);
void lookUpKey(YYSTYPE);

main(int argc, char **argv)
{
	int token;
	char *infile = "test.e";
	char *listing = "list.lis";
	extern FILE *yyin;
	extern FILE *listingFile;

	if(argc>1)
	{
		yyin = fopen(argv[1], "r");
		if(!yyin)
		{
			printf("Error opening file: %s", argv[1]);
			exit(fileErrorCode);
		}

		if(argc>3&&strcmp(argv[2], "-s")==0){
			listing = argv[3];
		}
	}
	else
	{
		yyin = stdin;
		//yyin = fopen(infile, "r");
	}

	listingFile = fopen(listing, "w");
	fprintf(listingFile, "%3d   ", lines);

	if( !yyparse() )
	{
		printf("Parsing completed with no errors.\n");


		/*  print resulting table

		int check;
		for(check = 0; check < sizeof(table)/sizeof(table[0]); check++)
		{
			if(table[check].name){
				printf("%d: %s %d\n", check, table[check].name, table[check].address);
				if(table[check].next){
					Node* j = table[check].next;
					printf("%d: %s %d\n", check, j->name, j->address);
					while(j->next)
					{
						j = j->next;
						printf("%d: %s %d\n", check, j->name, j->address);
					}
				}
			}
		}*/

		return 0;
	}
	else
	{
		printf("Parsing Failed, Error on line: %i at %s.\n", lines, yytext);
		return 2;
	}

    fclose(listingFile);
	fclose(yyin);
}

%}

%union{
  int           int_value;
  long          l_int_value; 
  char*         string_value;
  char*         ident_name;
}

%token ABSTRACT ASSERT BOOLEAN BREAK BYTE
%token CASE CATCH CHAR CLASS CONST CONTINUE
%token DEFAULT DO DOUBLE ELSE ENUM EXTENDS
%token FALSE FINAL FINALLY FLOAT FOR GOTO
%token IF IMPLEMENTS IMPORT INPUT INSTANCEOF INT INTERFACE LONG
%token NATIVE NEW NULL_TOK OUTPUT
%token PACKAGE PRIVATE PROTECTED PUBLIC RETURN
%token SHORT STATIC STRICTFP SUPER SWITCH SYNCHRONIZED
%token THIS THROW THROWS TRANSIENT TRUE TRY
%token VOID VOLATILE WHILE
%token IDENT 
%token INT_LITERAL STRING_LITERAL
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE SEMICOLON COMMA DOT
%token EQ GTR LESS EXCLAIM TILDE QUESTION COLON
%token DBL_EQ LESS_EQ GTR_EQ EXCL_EQ DBL_AMP DBL_BAR DBL_PLUS
%token DBL_MINUS PLUS MINUS STAR SLASH PERCENT AMP
%token BAR CARET DBL_LESS DBL_GTR TRIPLE_GTR PLUS_EQ MINUS_EQ
%token STAR_EQ SLASH_EQ AMP_EQ BAR_EQ CARET_EQ PERCENT_EQ DBL_LESS_EQ
%token DBL_GTR_EQ TRIPLE_GTR_EQ
%token COMMENT
%token REDUCE

%nonassoc IF
%nonassoc ELSE
%right EQ
%left PLUS MINUS
%left STAR SLASH
%nonassoc REDUCE1
%nonassoc REDUCE2

%%

program : 
			CLASS IDENT LBRACE PUBLIC STATIC VOID IDENT LPAREN RPAREN methodbody RBRACE;

methodbody :
				block | SEMICOLON;

block :
			LBRACE RBRACE
		|	LBRACE blockstatementsequence RBRACE;

blockstatementsequence :
					blockstatement | blockstatementsequence blockstatement;

blockstatement :
					type vardeclaratorlist SEMICOLON
				|	statement;

vardeclaratorlist :
						vardeclarator
					|	vardeclaratorlist COMMA vardeclarator;

vardeclarator :
				IDENT EQ INT_LITERAL{procIdent($1);}
			|	IDENT {procIdent($1);};

type: INT;

statement:
			block
		|	emptystatement
		|	ifstatement
		|	whilestatement
		|	statementexpression SEMICOLON
		|	OUTPUT LPAREN addexprlist RPAREN SEMICOLON;

addexprlist :
				addexpr
			|	addexprlist COMMA addexpr;

emptystatement : SEMICOLON;

ifstatement :
				IF LPAREN conditionalexpr RPAREN statement
			|	IF LPAREN conditionalexpr RPAREN statement ELSE statement;

whilestatement :
					WHILE LPAREN conditionalexpr RPAREN statement;

statementexpression :
				assignment | conditionalexpr;

assignment :
				IDENT assignmentop assignment {lookUpKey($1);}
			|	addexpr
			|	IDENT EQ INPUT LPAREN RPAREN {lookUpKey($1);};

assignmentop :
				EQ
			|	PLUS_EQ;

conditionalexpr:
					addexpr DBL_EQ addexpr
				|	addexpr EXCL_EQ addexpr
				|	addexpr LESS addexpr
				|	addexpr GTR addexpr
				|	addexpr LESS_EQ addexpr
				|	addexpr GTR_EQ addexpr;

addexpr :
			addexpr PLUS multexpr
		|	addexpr MINUS multexpr
		|	multexpr;

multexpr:
	multexpr STAR multexpr |
	multexpr SLASH multexpr |
	unaryexpr;

unaryexpr : 
			DBL_PLUS primaryexpr %prec REDUCE1
	|		DBL_MINUS primaryexpr %prec REDUCE1
	|		MINUS primaryexpr %prec REDUCE1
	|		primaryexpr
	|		LPAREN addexpr RPAREN %prec REDUCE2;

primaryexpr :
	INT_LITERAL | IDENT {lookUpKey($1);};
%%

void procIdent(YYSTYPE lexeme){

	char* key[MAX_IDENT];
	getKey(lexeme.ident_name, key);

	if(!find(key))
		insert(key);
	else
	{
		fprintf(stderr, "Redefinition error at line %d.\n", lines);
		exit(redefinitionErrorCode);
	}
}

void lookUpKey(YYSTYPE lexeme){

	char* key[MAX_IDENT];
	getKey(lexeme.ident_name, key);

	if(!find(key)){
		fprintf(stderr, "Undeclared identifier at line %d.\n", lines);
		exit(undeclaredErrorCode);
	}
}

bool find(char* key){
	bool found = false;
	unsigned address = hash(key);

	if(table[address].name&&strcmp(table[address].name, key)==0)
		found = true;
	else if(table[address].next){
		Node* j = &table[address];
		while(j->next)
		{
			j = j->next;
			if(j->name&&strcmp(j->name, key)==0)
				found = true;
		}
	}
	return found;
}

void insert(char* key){
	unsigned address = hash(key);

	if(!table[address].name){
		table[address].name = malloc(strlen(key));
		memcpy(table[address].name, key, strlen(key));
		table[address].name[strlen(key)] = '\0';
		table[address].next = NULL;
		table[address].type = INT;
		table[address].address = identNum;
		identNum++;
	}
	else if(!table[address].next){
		

		Node* n = malloc(sizeof(Node*));
		n->name = malloc(strlen(key));
		memcpy(n->name, key, strlen(key));
		n->name[strlen(key)] = '\0';
		n->next = NULL;
		n->type = INT;
		n->address = identNum;
		identNum++;

		table[address].next = n;
	}
	else{
		Node *next = table[address].next;
		
		if(next){
			while(next->next){
				next = next->next;
			}
		}

		Node* n = malloc(sizeof(Node*));
		n->name = malloc(strlen(key));
		memcpy(n->name, key, strlen(key));
		n->name[strlen(key)] = '\0';
		n->next = NULL;
		n->type = INT;
		n->address = identNum;
		identNum++;

		next->next = n;
	}
}

void getKey(char* line, char* key){

	unsigned i;
	unsigned sub = strlen(line);

	for(i = 0; i < strlen(line); i++){
		if((line[i]==' ')||(line[i]==';')||(line[i]==',')
			||(line[i]=='=')||(line[i]=='+')||(line[i]=='-')
			||(line[i]=='*')||(line[i]=='/')||(line[i]=='!')
			||(line[i]=='<')||(line[i]=='>')||(line[i]=='(')
			||(line[i]==')')){
			sub = i;
			break;
		}
	}

	memcpy(key, line, sub );
	key[sub] = '\0';
}

int hash(char* key){

	unsigned address = 0;
	int i;

	for(i = 0; i < strlen(key); i++){
		address += (int)key[i];
	}

	address %= TABLE_SIZE;

	return address;
}

void yyerror(char *s) 
{
    fprintf(stderr, "%s\n", s);
}