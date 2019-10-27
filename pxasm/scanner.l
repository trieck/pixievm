%option yylineno

%{
#include "Common.h"
#include "SymbolTable.h"
#include "Code.h"
#include "Parser.hpp"
#include "Exception.h"
#include "Util.h"

#define YY_NO_UNISTD_H (1)

#ifdef _MSC_VER
#include <io.h>
#endif	// _MSC_VER 

extern "C" int yywrap(void) { return 1; }
extern int yyerror(const char *s);
string line;

char backslash(const char **pp)
{
	static char transtab[] = "b\bf\fn\nr\rt\t";
	char c;

	if (**pp != '\\')
		return **pp;
	c = *++(*pp);
	if (c == '\0')
		return *--(*pp);
	if (strchr(transtab, c))
		return strchr(transtab, c)[1];
	return c;
}

ANON_BEGIN
Code *code = Code::getInstance();
SymbolTable *table = SymbolTable::getInstance();
ANON_END

%}

comment				;.*
decnum				[0-9]+
div						\/
gt						>
hexnum				\$[a-fA-F0-9]+
identifier		[a-zA-Z][a-zA-Z0-9_]*
lt						<
minus					-
mult					\*
newline				[\n]
offset-reg		[a-zA-Z]+[\r\t ]*\+[\r\t ]*[xX]
plus					\+
pseudo_op			\.[a-zA-Z][a-zA-Z0-9_]*
quotedstr			\"[^"\n]+\"
whitespace		[\t\r ]+
here					\$\$

%%
{whitespace}	;
{comment}			;
{decnum}			{
	word d;
	if (!sscanf(yytext, "%hu", &d)) {
		yyerror("invalid decimal number");
		return 0;
	}
	
	if (d < 0x100) {
		yylval.sym = table->installw(SymbolType::ST_CONST, IM8, d); 
		return IM8;
	} else {
		yylval.sym = table->installw(SymbolType::ST_CONST, IM16, d); 
		return IM16;
	}
}
{hexnum}		{
	word d;
	if (!sscanf(&yytext[1], "%hx", &d)) {
		yyerror("invalid hex number");
		return 0;
	}
	
	if (d < 0x100) {
		yylval.sym = table->installw(SymbolType::ST_CONST, IM8, d); 
		return IM8;
	} else {
		yylval.sym = table->installw(SymbolType::ST_CONST, IM16, d); 
		return IM16;
	}
}
{offset-reg}		{
	string error;
	string reg = trim(string(yytext, strchr(yytext, '+') - yytext));
	LPSYMBOL sym;
	if ((sym = table->lookup(reg)) == nullptr) {
		yyerror("unexpected token");
		return 0;
	}
	if (sym->type != SymbolType::ST_REG) {
		yyerror("unsupported symbol");
		return 0;
	}

	// encode offset bit in register
	yylval.sym = table->installw(sym->type, sym->sub, sym->val8 | 0x08);
	return RX16;
}
{newline}.*		{
		line = trim(yytext + 1);
		yyless(1);
	}
{identifier}	{
	LPSYMBOL sym;
	if ((sym = table->lookup(yytext)) == NULL) {
		yylval.sym = table->install(yytext);
		return UNDEF;
	}
	
	switch (sym->type) {
	case SymbolType::ST_REG:
	case SymbolType::ST_INSTRUCTION:
	case SymbolType::ST_ID:
		yylval.sym = sym;
		return sym->sub;
	case SymbolType::ST_UNDEF:
		yylval.sym = sym;
		return UNDEF;
	default:
		yyerror("unsupported symbol");
	}
	
	return 0;
}
{pseudo_op}		{ 
	LPSYMBOL sym;
	if ((sym = table->lookup(yytext)) == NULL) {
		yyerror("unrecognized pseudo-op");
		return 0;
	}
	
	return sym->sub;
 }

{quotedstr}		{
	const char *ptext = yytext+1;	// eat '"'
	string str;

	for ( ; *ptext != '"'; ptext++) {
		if (ptext[0] == '\0' || ptext[0] == '\n') {
			yyerror("unterminated string literal");
			return 0;
		}
		
		str += backslash(&ptext);
	}
	
	yylval.sym = table->installs(str);
	return STRING;
}
{lt}		{ return LO_BYTE; }
{gt}		{ return HI_BYTE; }
{plus}	{ return PLUS; }
{minus}	{ return MINUS; }
{mult}	{ return MULT; }
{div}		{ return DIV; }
{here}	{ 
	yylval.sym = table->installw(SymbolType::ST_CONST, IM16, code->location()); 
	return IM16; 
}
.				{ return yytext[0]; }
%%
