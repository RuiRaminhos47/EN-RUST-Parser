%{
// HEADERS
#include <stdlib.h>
#include "parser.h"

// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }
#.*\n { yyline++; }
\n { yyline++; }

\-?[0-9]+ { 
   yylval.intValue = atoi(yytext);
   return INT; 
}
[a-z][A-Za-z]* { 
	yylval.charValue = yytext;	
	return VAR; 
}
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return TIMES; }
"/" { return DIV; }
"%" { return REST; }
"==" { return EQUALTO; }
"!=" { return NEQUALTO; }
">" { return GT; }
"<" { return LT; }
">=" { return GET; }
"<=" { return LETH; }
"=" { return EQUALAR; }
"LET" { return LET; }
";" { return ENDING; }
"{" { return COMBEG; }
"}" { return COMEND; }
"PRINTLN" { return PRINTL; }
"IF" { return IF; }
"ELSE" { return ELSE; }
"WHILE" { return WHILE; }
\".*\" { return STRING; }
"READ_LINE" { return READL; }
.  { yyerror("unexpected character"); }

%%


