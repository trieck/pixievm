%{
#include "Common.h"
#include "SymbolTable.h"
#include "Code.h"
#include "Exception.h"
#include "Util.h"

extern char *yytext;
extern string line;

extern int yylineno;
extern int yylex(void);
extern int yyterminate(void);
int yyerror(const char *s);

ANON_BEGIN
Code *code = Code::getInstance();
SymbolTable *table = SymbolTable::getInstance();
ANON_END

%}

%union {
	int n;			// token id 
	LPSYMBOL sym;	// symbol 
}

%token	<n>		BYTE WORD

%token	<sym>	DECL_ORG DECL_BYTE DECL_WORD DECL_TEXT
%token	<sym>	STRING

%token	<sym>	I1 I2 I3 I4 I5 I6 I7
%token	<sym>	R8 R16 RX16
%token	<sym>	IM8 IM16
%token	<sym>	UNDEF

%type	<sym>	IVAL M16 A16 I16

%%	/* begin grammar */

prog:	stmts
		;

stmts:	stmt
		| stmts stmt
		;

stmt:	  def8
		| def16
		| deflabel
		| instr
		| pseudo_op
		;
		
def8:	UNDEF '=' IM8 {
			$1->type = ST_ID;
			$1->sub = IM8;
			$1->val8 = $3->val8;
		}
def16:	UNDEF '=' IM16 {
			$1->type = ST_ID;
			$1->sub = IM16;
			$1->val16 = $3->val16;
		}
		;
		
deflabel:	UNDEF ':'	{ 
			$1->type = ST_ID;
			$1->sub = IM16;
			$1->val16 = code->location();
		}
		;

instr:		I1 R8  ',' R8 		{ code->code3(AM_RR8, $1, $2, $4); }	
		|	I1 R8  ',' IM8		{ code->code3(AM_RI8, $1, $2, $4); }	
		|	I1 R8  ',' M16		{ code->code3(AM_RM8, $1, $2, $4); }	
		|	I1 R8  ',' A16      { code->code3(AM_RA8, $1, $2, $4); }	
        |	I1 R16 ',' R16		{ code->code3(AM_RR16, $1, $2, $4); }	
        |	I1 R16 ',' IM8		{ code->code3(AM_RI16, $1, $2, $4); }	
		|	I1 R16 ',' I16		{ code->code3(AM_RI16, $1, $2, $4); }	
        |	I1 R16 ',' M16		{ code->code3(AM_RM16, $1, $2, $4); }	
        |	I1 R16 ',' A16		{ code->code3(AM_RA16, $1, $2, $4); }	
        |	I1 M16 ',' R8		{ code->code3(AM_MR8, $1, $2, $4); }	
        |	I1 M16 ',' R16		{ code->code3(AM_MR16, $1, $2, $4); }	
		|	I1 BYTE M16 ',' IM8	{ code->code3(AM_M8I8, $1, $3, $5); }
		|	I1 WORD M16 ',' IM8	{ code->code3(AM_M16I8, $1, $3, $5); }
		|	I1 M16 ',' I16		{ code->code3(AM_MI16, $1, $2, $4); }		
        |	I1 A16 ',' R8		{ code->code3(AM_AR8, $1, $2, $4); }	
        |	I1 A16 ',' R16		{ code->code3(AM_AR16, $1, $2, $4); }	
        |	I1 BYTE A16 ',' IM8	{ code->code3(AM_A8I8, $1, $3, $5); }	
        |	I1 WORD A16 ',' IM8	{ code->code3(AM_A16I8, $1, $3, $5); }	
        |	I1 A16 ',' I16		{ code->code3(AM_AI16, $1, $2, $4); }	
        |	I2 R8				{ code->code2(AM_R8, $1, $2); }	
        |	I2 R16				{ code->code2(AM_R16, $1, $2); }
        |	I2 BYTE M16			{ code->code2(AM_M8, $1, $3); }
        |	I2 WORD M16			{ code->code2(AM_M16, $1, $3); }
        |	I2 BYTE A16			{ code->code2(AM_A8, $1, $3); }
        |	I2 WORD A16			{ code->code2(AM_A16, $1, $3); }
        |	I3					{ code->code1(AM_IMPLIED, $1); }
        |	I4 R16				{ code->code2(AM_R16, $1, $2); }
        |	I4 M16				{ code->code2(AM_M16, $1, $2); }
        |	I4 A16				{ code->code2(AM_A16, $1, $2); }
		|	I4 IM8				{ code->code2(AM_I16, $1, $2); }
        |	I4 I16				{ code->code2(AM_I16, $1, $2); }
        |	I5 IM8				{ code->code2(AM_I8, $1, $2); }
		|	I5 I16				{ code->relcode($1, $2); }
        |	I6 R8				{ code->code2(AM_R8, $1, $2); }
        |	I6 R16				{ code->code2(AM_R16, $1, $2); }
        |	I6 BYTE M16			{ code->code2(AM_M8, $1, $3); }
        |	I6 WORD M16			{ code->code2(AM_M16, $1, $3); }
        |	I6 BYTE A16			{ code->code2(AM_A8, $1, $3); }
        |	I6 WORD A16			{ code->code2(AM_A16, $1, $3); }
        |	I7 R8				{ code->code2(AM_R8, $1, $2); }
        |	I7 R16				{ code->code2(AM_R16, $1, $2); }
        |	I7 BYTE M16			{ code->code2(AM_M8, $1, $3); }
        |	I7 WORD M16			{ code->code2(AM_M16, $1, $3); }
        |	I7 BYTE A16			{ code->code2(AM_A8, $1, $3); }
        |	I7 WORD A16			{ code->code2(AM_A16, $1, $3); }
		|	I7 IM8				{ code->code2(AM_I8, $1, $2); }	
        |	I7 I16				{ code->code2(AM_I16, $1, $2); }	
		;
		
M16:		'[' R16 ']'			{ $$ = $2; }
		|	'[' RX16 ']'		{ $$ = $2; }
		;

A16:		'[' IM8 ']'			{ $$ = $2; }
		|	'[' I16 ']'			{ $$ = $2; }
		;
		
I16:	  IM16
		| UNDEF
		;

pseudo_op:	
		DECL_ORG IVAL	{ 
				if (code->isGenerating()) {
					return yyerror("origin must appear before any instructions or data");
				}
				if (code->isOriginSet()) {
					return yyerror("origin already declared");
				}
				code->setOrigin($2->val16); 
			}
		| DECL_BYTE IM8		{ code->putByte($2->val8); }
		| DECL_WORD IM8		{ code->putWord($2->val8); }
		| DECL_WORD IM16	{ code->putWord($2->val16); }
		| DECL_TEXT STRING	{ code->putString($2->name); }
		;

IVAL:	IM8	| IM16	
		;

%%	
    /* end grammar */

int yyerror(const char *s)
{
	fprintf(stderr, "(%d): %s \"%s\" in \"%s\".\n",
		yylineno, s, yytext, line.c_str());
	return 1;
}
