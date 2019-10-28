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
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return TIMES; }
"/" { return DIV; }
"%" { return REST; }
"==" { return EQUAL; }
"!=" { return NEQUALTO; }
">" { return GT; }
"<" { return LT; }
">=" { return GET; }
"<=" { return LETH; }
"if" { return IF; }
"else" { return ELSE; }
"while" { return WHILE; }
"=" { return LET; }
";" { return ENDING; }
"{" { return COMBEG; }
"}" { return COMEND; }
"println!" { return PRINTL; }
""" { return ASPA; }
"read_line" { return READL; }
.  { yyerror("unexpected character"); }
%%

// (while, if, then, else, = , ; , { , }).

