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
"let" { return LET; }
";" { return ENDING; }
"&" { return ECOM; }
"(" { return PARIN; }
")" { return PAROUT; }
"{" { return COMBEG; }
"}" { return COMEND; }
"," { return VIRG; }
"println!" { return PRINTL; }
"if" { return IF; }
"else" { return ELSE; }
"while" { return WHILE; }
"read_line" { return READL; }
"fn" { return FN; }
"main" { return MAIN; }
\-?[0-9]+ { 
   yylval.intValue = atoi(yytext);
   return INT; 
}
[a-z][A-Za-z]* { 
	yylval.charValue = strdup(yytext);	
	return VAR; 
}
\".*\" { 
	yylval.charValue = strdup(yytext);	
	return STRING; 
}
.  { yyerror("unexpected character"); }

%%


