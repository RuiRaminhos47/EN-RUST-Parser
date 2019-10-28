// Tokens
%token 
  INT  
  PLUS
  MINUS
  TIMES
  DIV
  REST
  EQUALTO
  NEQUALTO
  GT
  LT
  GET
  LETH

// Operator associativity & precedence
%left PLUS
%left MINUS
%left TIMES
%left DIV
%left REST
%left EQUAL
%left NEQUALTO
%left GT
%left LT
%left GET
%left LETH


// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  Expr* exprValue; 
}

%type <intValue> INT
%type <exprValue> expr

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
Expr* root;
}

%%
program: expr { root = $1; }

expr: 
  INT { 
    $$ = ast_integer($1); 
  }
  | 
  expr PLUS expr { 
    $$ = ast_operation(PLUS, $1, $3); 
  } 
  |
  expr MINUS expr { 
    $$ = ast_operation(MINUS, $1, $3); 
  } 
  |
  expr TIMES expr { 
    $$ = ast_operation(TIMES, $1, $3); 
  } 
  |
  expr DIV expr { 
    $$ = ast_operation(DIV, $1, $3); 
  } 
  |
  expr REST expr { 
    $$ = ast_operation(REST, $1, $3); 
  } 
  |
  expr EQUALTO expr { 
    $$ = ast_operation(EQUALTO, $1, $3); 
  } 
  |
  expr NEQUALTO expr { 
    $$ = ast_operation(NEQUALTO, $1, $3); 
  }
  |
  expr GT expr { 
    $$ = ast_operation(GT, $1, $3); 
  } 
  |
  expr LT expr { 
    $$ = ast_operation(LT, $1, $3); 
  }  
  |
  expr GET expr { 
    $$ = ast_operation(GET, $1, $3); 
  } 
  |
  expr LETH expr { 
    $$ = ast_operation(LETH, $1, $3); 
  } 
  ;
%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
