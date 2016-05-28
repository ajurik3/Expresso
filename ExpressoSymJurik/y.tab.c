#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 3 "exprParserSymTabJurik.y"

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
		/*yyin = fopen(infile, "r");*/
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

#line 120 "exprParserSymTabJurik.y"
typedef union{
  int           int_value;
  long          l_int_value; 
  char*         string_value;
  char*         ident_name;
} YYSTYPE;
#line 135 "y.tab.c"
#define ABSTRACT 257
#define ASSERT 258
#define BOOLEAN 259
#define BREAK 260
#define BYTE 261
#define CASE 262
#define CATCH 263
#define CHAR 264
#define CLASS 265
#define CONST 266
#define CONTINUE 267
#define DEFAULT 268
#define DO 269
#define DOUBLE 270
#define ELSE 271
#define ENUM 272
#define EXTENDS 273
#define FALSE 274
#define FINAL 275
#define FINALLY 276
#define FLOAT 277
#define FOR 278
#define GOTO 279
#define IF 280
#define IMPLEMENTS 281
#define IMPORT 282
#define INPUT 283
#define INSTANCEOF 284
#define INT 285
#define INTERFACE 286
#define LONG 287
#define NATIVE 288
#define NEW 289
#define NULL_TOK 290
#define OUTPUT 291
#define PACKAGE 292
#define PRIVATE 293
#define PROTECTED 294
#define PUBLIC 295
#define RETURN 296
#define SHORT 297
#define STATIC 298
#define STRICTFP 299
#define SUPER 300
#define SWITCH 301
#define SYNCHRONIZED 302
#define THIS 303
#define THROW 304
#define THROWS 305
#define TRANSIENT 306
#define TRUE 307
#define TRY 308
#define VOID 309
#define VOLATILE 310
#define WHILE 311
#define IDENT 312
#define INT_LITERAL 313
#define STRING_LITERAL 314
#define LPAREN 315
#define RPAREN 316
#define LBRACKET 317
#define RBRACKET 318
#define LBRACE 319
#define RBRACE 320
#define SEMICOLON 321
#define COMMA 322
#define DOT 323
#define EQ 324
#define GTR 325
#define LESS 326
#define EXCLAIM 327
#define TILDE 328
#define QUESTION 329
#define COLON 330
#define DBL_EQ 331
#define LESS_EQ 332
#define GTR_EQ 333
#define EXCL_EQ 334
#define DBL_AMP 335
#define DBL_BAR 336
#define DBL_PLUS 337
#define DBL_MINUS 338
#define PLUS 339
#define MINUS 340
#define STAR 341
#define SLASH 342
#define PERCENT 343
#define AMP 344
#define BAR 345
#define CARET 346
#define DBL_LESS 347
#define DBL_GTR 348
#define TRIPLE_GTR 349
#define PLUS_EQ 350
#define MINUS_EQ 351
#define STAR_EQ 352
#define SLASH_EQ 353
#define AMP_EQ 354
#define BAR_EQ 355
#define CARET_EQ 356
#define PERCENT_EQ 357
#define DBL_LESS_EQ 358
#define DBL_GTR_EQ 359
#define TRIPLE_GTR_EQ 360
#define COMMENT 361
#define REDUCE 362
#define REDUCE1 363
#define REDUCE2 364
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    1,    1,    2,    2,    3,    3,    4,    4,    6,
    6,    8,    8,    5,    7,    7,    7,    7,    7,    7,
   13,   13,    9,   10,   10,   11,   12,   12,   16,   16,
   16,   17,   17,   15,   15,   15,   15,   15,   15,   14,
   14,   14,   18,   18,   18,   19,   19,   19,   19,   19,
   20,   20,
};
short yylen[] = {                                         2,
   11,    1,    1,    2,    3,    1,    2,    3,    1,    1,
    3,    3,    1,    1,    1,    1,    1,    1,    2,    5,
    1,    3,    1,    5,    7,    5,    1,    1,    3,    1,
    5,    1,    1,    3,    3,    3,    3,    3,    3,    3,
    3,    1,    3,    3,    1,    2,    2,    2,    1,    3,
    1,    1,
};
short yydefred[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    3,    0,    2,    0,   14,    0,    0,    0,   51,
    0,    4,   23,    0,    0,    0,   15,    0,    6,    0,
    9,   16,   17,   18,    0,    0,   28,   27,    0,   45,
   49,    1,    0,    0,    0,    0,   33,    0,   52,    0,
   46,   47,   48,    5,    7,    0,    0,   10,   19,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   29,   50,    0,    8,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   43,
   44,    0,    0,    0,    0,    0,   12,   11,    0,   20,
    0,   26,   31,    0,   25,
};
short yydgoto[] = {                                       2,
   13,   27,   28,   29,   30,   57,   31,   58,   32,   33,
   34,   35,   72,   36,   37,   38,   48,   39,   40,   41,
};
short yysindex[] = {                                   -264,
 -300,    0, -302, -257, -263, -261, -242, -237, -235, -259,
 -266,    0, -228,    0, -205,    0, -185, -180, -322,    0,
 -308,    0,    0, -292, -292, -292,    0, -254,    0, -167,
    0,    0,    0,    0, -175, -124,    0,    0, -240,    0,
    0,    0, -308, -308, -308, -132,    0, -304,    0, -260,
    0,    0,    0,    0,    0, -171, -202,    0,    0, -308,
 -308, -308, -308, -308, -308, -308, -308, -308, -308, -124,
 -162, -306, -200, -157, -155, -200,    0,    0, -150,    0,
 -167, -200, -200, -200, -200, -200, -200, -240, -240,    0,
    0, -204, -156, -308, -204, -152,    0,    0, -105,    0,
 -200,    0,    0, -204,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -128,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -148,    0,    0, -184,    0,
    0,    0,    0,    0,    0, -224,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -178,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -222,    0,    0, -148,    0,    0,    0,    0,
    0, -303, -253, -239, -231, -223, -198, -164, -144,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -216,    0,
 -210,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
    0,  161,    0,  146,    0,    0,  -89,   98,    0,    0,
    0,    0,    0,  -21,   86,  132,    0,   59,    0,   26,
};
#define YYTABLESIZE 216
short yytable[] = {                                      50,
    1,   46,   99,   49,   20,  102,   21,   19,   20,   93,
   21,    3,   37,   15,  105,   94,    4,   37,   16,   49,
   20,   70,   73,   70,   17,   15,   76,   47,   24,   25,
   16,   26,   24,   25,    6,   26,   17,    5,   82,   83,
   84,   85,   86,   87,   18,   19,   20,    7,   21,   51,
   52,   53,   11,   22,   23,   78,   18,   19,   20,   11,
   21,   12,   36,   24,   11,   54,   23,   36,   24,    8,
   24,   25,  101,   26,   24,   15,   34,    9,   66,   67,
   10,   34,   24,   25,   38,   26,   17,   32,   32,   38,
   32,   42,   39,   21,   24,   24,   24,   39,   24,   21,
   68,   69,   24,   24,   24,   22,   18,   19,   20,   43,
   21,   22,   32,   32,   11,   32,   23,   35,   80,   81,
   24,   24,   35,   24,   88,   89,   90,   91,   71,   44,
   74,   42,   24,   25,   45,   26,   42,   42,   66,   67,
   42,   42,   13,   13,   56,   59,   42,   42,   42,   42,
   75,   40,   79,   92,   42,   42,   40,   40,   95,   96,
   40,   40,   97,  103,  100,  104,   40,   40,   40,   40,
   14,   41,   30,   55,   40,   40,   41,   41,   98,   77,
   41,   41,    0,    0,    0,    0,   41,   41,   41,   41,
    0,    0,   52,    0,   41,   41,   52,   52,    0,    0,
   60,   61,   52,   52,   52,   52,   62,   63,   64,   65,
   52,   52,   52,   52,   66,   67,
};
short yycheck[] = {                                      21,
  265,  324,   92,  312,  313,   95,  315,  312,  313,  316,
  315,  312,  316,  280,  104,  322,  319,  321,  285,  312,
  313,   43,   44,   45,  291,  280,   48,  350,  337,  338,
  285,  340,  337,  338,  298,  340,  291,  295,   60,   61,
   62,   63,   64,   65,  311,  312,  313,  309,  315,   24,
   25,   26,  319,  320,  321,  316,  311,  312,  313,  319,
  315,  321,  316,  280,  319,  320,  321,  321,  285,  312,
  337,  338,   94,  340,  291,  280,  316,  315,  339,  340,
  316,  321,  337,  338,  316,  340,  291,  312,  313,  321,
  315,  320,  316,  316,  311,  312,  313,  321,  315,  322,
  341,  342,  319,  320,  321,  316,  311,  312,  313,  315,
  315,  322,  337,  338,  319,  340,  321,  316,  321,  322,
  337,  338,  321,  340,   66,   67,   68,   69,   43,  315,
   45,  316,  337,  338,  315,  340,  321,  322,  339,  340,
  325,  326,  321,  322,  312,  321,  331,  332,  333,  334,
  283,  316,  324,  316,  339,  340,  321,  322,  316,  315,
  325,  326,  313,  316,  321,  271,  331,  332,  333,  334,
   10,  316,  321,   28,  339,  340,  321,  322,   81,   48,
  325,  326,   -1,   -1,   -1,   -1,  331,  332,  333,  334,
   -1,   -1,  321,   -1,  339,  340,  325,  326,   -1,   -1,
  325,  326,  331,  332,  333,  334,  331,  332,  333,  334,
  339,  340,  341,  342,  339,  340,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 364
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"ABSTRACT","ASSERT","BOOLEAN",
"BREAK","BYTE","CASE","CATCH","CHAR","CLASS","CONST","CONTINUE","DEFAULT","DO",
"DOUBLE","ELSE","ENUM","EXTENDS","FALSE","FINAL","FINALLY","FLOAT","FOR","GOTO",
"IF","IMPLEMENTS","IMPORT","INPUT","INSTANCEOF","INT","INTERFACE","LONG",
"NATIVE","NEW","NULL_TOK","OUTPUT","PACKAGE","PRIVATE","PROTECTED","PUBLIC",
"RETURN","SHORT","STATIC","STRICTFP","SUPER","SWITCH","SYNCHRONIZED","THIS",
"THROW","THROWS","TRANSIENT","TRUE","TRY","VOID","VOLATILE","WHILE","IDENT",
"INT_LITERAL","STRING_LITERAL","LPAREN","RPAREN","LBRACKET","RBRACKET","LBRACE",
"RBRACE","SEMICOLON","COMMA","DOT","EQ","GTR","LESS","EXCLAIM","TILDE",
"QUESTION","COLON","DBL_EQ","LESS_EQ","GTR_EQ","EXCL_EQ","DBL_AMP","DBL_BAR",
"DBL_PLUS","DBL_MINUS","PLUS","MINUS","STAR","SLASH","PERCENT","AMP","BAR",
"CARET","DBL_LESS","DBL_GTR","TRIPLE_GTR","PLUS_EQ","MINUS_EQ","STAR_EQ",
"SLASH_EQ","AMP_EQ","BAR_EQ","CARET_EQ","PERCENT_EQ","DBL_LESS_EQ","DBL_GTR_EQ",
"TRIPLE_GTR_EQ","COMMENT","REDUCE","REDUCE1","REDUCE2",
};
char *yyrule[] = {
"$accept : program",
"program : CLASS IDENT LBRACE PUBLIC STATIC VOID IDENT LPAREN RPAREN methodbody RBRACE",
"methodbody : block",
"methodbody : SEMICOLON",
"block : LBRACE RBRACE",
"block : LBRACE blockstatementsequence RBRACE",
"blockstatementsequence : blockstatement",
"blockstatementsequence : blockstatementsequence blockstatement",
"blockstatement : type vardeclaratorlist SEMICOLON",
"blockstatement : statement",
"vardeclaratorlist : vardeclarator",
"vardeclaratorlist : vardeclaratorlist COMMA vardeclarator",
"vardeclarator : IDENT EQ INT_LITERAL",
"vardeclarator : IDENT",
"type : INT",
"statement : block",
"statement : emptystatement",
"statement : ifstatement",
"statement : whilestatement",
"statement : statementexpression SEMICOLON",
"statement : OUTPUT LPAREN addexprlist RPAREN SEMICOLON",
"addexprlist : addexpr",
"addexprlist : addexprlist COMMA addexpr",
"emptystatement : SEMICOLON",
"ifstatement : IF LPAREN conditionalexpr RPAREN statement",
"ifstatement : IF LPAREN conditionalexpr RPAREN statement ELSE statement",
"whilestatement : WHILE LPAREN conditionalexpr RPAREN statement",
"statementexpression : assignment",
"statementexpression : conditionalexpr",
"assignment : IDENT assignmentop assignment",
"assignment : addexpr",
"assignment : IDENT EQ INPUT LPAREN RPAREN",
"assignmentop : EQ",
"assignmentop : PLUS_EQ",
"conditionalexpr : addexpr DBL_EQ addexpr",
"conditionalexpr : addexpr EXCL_EQ addexpr",
"conditionalexpr : addexpr LESS addexpr",
"conditionalexpr : addexpr GTR addexpr",
"conditionalexpr : addexpr LESS_EQ addexpr",
"conditionalexpr : addexpr GTR_EQ addexpr",
"addexpr : addexpr PLUS multexpr",
"addexpr : addexpr MINUS multexpr",
"addexpr : multexpr",
"multexpr : multexpr STAR multexpr",
"multexpr : multexpr SLASH multexpr",
"multexpr : unaryexpr",
"unaryexpr : DBL_PLUS primaryexpr",
"unaryexpr : DBL_MINUS primaryexpr",
"unaryexpr : MINUS primaryexpr",
"unaryexpr : primaryexpr",
"unaryexpr : LPAREN addexpr RPAREN",
"primaryexpr : INT_LITERAL",
"primaryexpr : IDENT",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 247 "exprParserSymTabJurik.y"

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
#line 594 "y.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 12:
#line 181 "exprParserSymTabJurik.y"
{procIdent(yyvsp[-2]);}
break;
case 13:
#line 182 "exprParserSymTabJurik.y"
{procIdent(yyvsp[0]);}
break;
case 29:
#line 211 "exprParserSymTabJurik.y"
{lookUpKey(yyvsp[-2]);}
break;
case 31:
#line 213 "exprParserSymTabJurik.y"
{lookUpKey(yyvsp[-4]);}
break;
case 52:
#line 245 "exprParserSymTabJurik.y"
{lookUpKey(yyvsp[0]);}
break;
#line 755 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
