%{

/*
Andrew Jurik
CS435
Scanner & Parser & Symbol Table
*/

#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include "y.tab.h"

int checkreserved(const char*);
int parseint(const char* word);
int ipow(int base, int exp);
int checkseparators(const char* word);
int checkoperators(const char* word);

#define TOKEN_INDEX_OFFSET 257

//For processing string literals
char buf[256];
char *s;


extern int lines;
extern FILE *listingFile;

enum Literal_Type_Names {INTEGER_TYPE, LONG_TYPE } literal_type; 

%}

%x STRING

separator \(|\)|\[|\]|\{|\}|\;|\,|\.
operator =|\>|\<|!|~|\?|:|"=="|"<="|">="|"!="|"&&"|"||"|"++"|"--"|\+|\-|\*|\/|%|&|\||\^|"<<"|">>"|">>>"|"+="|"-="|"*="|"/="|"&="|"|="|"^="|"%="|"<<="|">>="|">>>="

%%
[\t ]+ fprintf(listingFile, "%s", yytext);

\n {lines++; fprintf(listingFile, "\n%3d   ", lines);}

[a-zA-Z_$][a-zA-Z_$0-9]* {fprintf(listingFile, "%s", yytext);
						  yylval.ident_name = yytext;
						  //printf("In scanner: %s\n", identifier);
						  int thisToken = checkreserved(yytext); 
						  return thisToken;}

(([1-9][0-9]*)|(0[0-7]*)|(0(x|X)[0-9a-fA-F]+))(l|L)? {fprintf(listingFile, "%s", yytext); parseint(yytext); return INT_LITERAL;}

\"           { BEGIN STRING; buf[0] = 0; s = buf; }
<STRING>\\n  { *s++ = '\\'; *s++ = 'n'; }
<STRING>\\t  { *s++ = '\\'; *s++ = 't'; }
<STRING>\\\" { *s++ = '\\'; *s++ = '\"'; }
<STRING>\"   { *s = 0; 
                fprintf(listingFile, "\"%s\"", buf); 
                yylval.string_value = _strdup(buf);
                BEGIN 0; 
                return STRING_LITERAL; }
<STRING>.    {  *s++ = *yytext; }
<STRING>\n   {  *s = 0;
                fprintf(listingFile, "\"%s\n", buf);  
                fprintf(listingFile, "invalid string shown above\n"); printf("invalid string\n"); 
                lines++; fprintf(listingFile, "%3d   ", lines);
               yylval.string_value = _strdup(buf); 
                BEGIN 0;
				fprintf(listingFile, "%s \n", yylval.string_value);
                /*return STRING_LITERAL;*/ }
\/\/[^\n]* {fprintf(listingFile, "%s", yytext); return COMMENT;}
{separator} {fprintf(listingFile, "%s", yytext); return checkseparators(yytext);}
{operator} {fprintf(listingFile, "%s", yytext); return checkoperators(yytext);}
[^ \t\n\"\.\(\)\[\]\>\<!~{},:;%&\+\-\*\/\|\^]+ ;
%%

//scan list of operators for matched operator
int checkoperators(const char* word){
	char **operators[37] = {"=", ">", "<", "!", "~", "?", ":", "==", "<=", ">=",
	                       "!=", "&&", "||", "++", "--", "+", "-", "*", "/", "%", 
						   "&", "|", "^", "<<", ">>", ">>>", "+=", "-=", "*=", 
						   "/=", "&=", "|=", "^=", "%=", "<<=", ">>=", ">>>="};
	
	int i = 0;

	for(; i < sizeof(operators)/sizeof(operators[0]); i++)
	{
		if(strcmp(operators[i], word) == 0){
			return i+TOKEN_INDEX_OFFSET+67;
			}

	}

	return i;
}

//scan list of separators for matched separator
int checkseparators(const char* word){

	char** separators[9] = {"(", ")", "[", "]", "{", "}", ";", ",", "."};

	int i = 0;

	for(; i < sizeof(separators)/sizeof(separators[0]); i++)
	{
		if(strcmp(separators[i], word) == 0)
			return i+TOKEN_INDEX_OFFSET+58;
	}

	return i;
}

//set appropriate literal of yylval equal to value of matched int literal
int parseint(const char* word){
	
	literal_type = INTEGER_TYPE;
	
	if(word[strlen(word)-1]=='l'||word[strlen(word)-1]=='L')
	{
		literal_type = LONG_TYPE;
	}

	//detect base of literal
	int mult;
	if(strlen(word)>2){
		if(word[1]=='x'||word[1]=='X')
		{
			mult = 16;
		}
		else if(word[0]=='0')
		{
			mult = 8;
		}
		else{
			mult = 10;
		}
	}
	else if((strlen(word)>1)&&(word[0]=='0'))
	{
		if(word[0]=='0')
			mult = 8;

	}
	else
	{
		mult = 10;
	}


	int i = 0;
	int index;
	int value = 0;

	for(; i <= strlen(word) - 1 - literal_type; i++)
	{
		index = strlen(word) -1 - literal_type - i;

		switch(word[index]){

		case '1':
				value += 1*ipow(mult, i);
				break;
		case '2':
				value += 2*ipow(mult, i);
				break;
		case '3':
				value += 3*ipow(mult, i);
				break;
		case '4':
				value += 4*ipow(mult, i);
				break;
		case '5':
				value += 5*ipow(mult, i);
				break;
		case '6':
				value += 6*ipow(mult, i);
				break;
		case '7':
				value += 7*ipow(mult, i);
				break;
		case '8':
				value += 8*ipow(mult, i);
				break;
		case '9':
				value += 9*ipow(mult, i);
				break;
		case 'a':
				value += 10*ipow(mult, i);
				break;
		case 'A':
				value += 10*ipow(mult, i);
				break;
		case 'b':
				value += 11*ipow(mult, i);
				break;
		case 'B':
				value += 11*ipow(mult, i);
				break;
		case 'c':
				value += 12*ipow(mult, i);
				break;
		case 'C':
				value += 12*ipow(mult, i);
				break;
		case 'd':
				value += 13*ipow(mult, i);
				break;
		case 'D':
				value += 13*ipow(mult, i);
				break;
		case 'e':
				value += 14*ipow(mult, i);
				break;
		case 'E':
				value += 14*ipow(mult, i);
				break;
		case 'f':
				value += 15*ipow(mult, i);
				break;
		case 'F':
				value += 15*ipow(mult, i);
				break;
		}
	}

	if(literal_type)
		yylval.l_int_value = value;
		else
			yylval.int_value = value;
						

	return 1;

}

//return base raised to power of exp
int ipow(int base, int exp)
{
    int result = 1;
    while (exp)
    {
        result *= base;
		exp--;
    }

    return result;
}

//indicates whether matched identifier matches any of the reserved words
int checkreserved(const char* word){	

	const char *reserved[55] = {"abstract", "assert", "boolean", "break", "byte", "case", "catch",
		"char", "class", "const", "continue", "default", "do", "double", "else", "enum",
		"extends", "false", "final", "finally", "float", "for", "goto", "if", "implements",
		"import", "input", "instanceof", "int", "interface", "long", "native", "new", "null",
		"output", "package", "private", "protected", "public", "return", "short", "static",
		"strictfp", "super", "switch", "synchronized", "this", "throw", "throws", "transient",
		"true", "try", "void", "volatile", "while"};


	int found = IDENT;

	int min = 0;
	int max = sizeof(reserved)/sizeof(reserved[0])-1;
	int mid;

	while(min<=max)
	{
		mid=(min+max)/2;

		if(strcmp(word, reserved[mid])<0)
			max = mid-1;
		if(strcmp(word, reserved[mid])>0)
			min = mid+1;
		if(strcmp(word, reserved[mid])==0){
			found = mid + TOKEN_INDEX_OFFSET;
			min = max + 1;
		}	
	}
	return found;
}
