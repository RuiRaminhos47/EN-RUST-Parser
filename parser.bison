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
  IF
  ELSE
  WHILE
  PRINTL
  READL
  LET
  STRING
  VAR
  COMBEG
  ENDING
  COMEND
  EQUALAR
  PARIN
  PAROUT
  ECOM
  FN
  MAIN
  VIRG
  TRUE
  FALSE

// Operator associativity & precedence
%left PLUS MINUS
%left TIMES DIV
%left REST

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  char* charValue;
  Expr* exprValue; 
  BoolExpr* exprBool;
  Cmd* cmdd;
  commandList* cmdl;
}

%type <intValue> INT
%type <charValue> VAR
%type <charValue> STRING
%type <charValue> TRUE
%type <charValue> FALSE
%type <exprValue> expr
%type <exprBool> boolexpr
%type <cmdd> cmd
%type <cmdl> commandlist

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
// commandList* root;
Expr* root;
}

%%
// program: FN MAIN PARIN PAROUT COMBEG commandlist COMEND { root = $6; }
program: expr { root = $1; }

expr: 
  INT { 
    $$ = ast_integer($1); 
  }
  |
  VAR {
    $$ =  ast_var($1);
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
  ;

boolexpr:
  expr EQUALTO expr { 
    $$ = expression_operation(EQUALTO, $1, $3); 
  } 
  |
  expr NEQUALTO expr { 
    $$ = expression_operation(NEQUALTO, $1, $3); 
  }
  |
  expr GT expr { 
    $$ = expression_operation(GT, $1, $3); 
  } 
  |
  expr LT expr { 
    $$ = expression_operation(LT, $1, $3); 
  }  
  |
  expr GET expr { 
    $$ = expression_operation(GET, $1, $3); 
  } 
  |
  expr LETH expr { 
    $$ = expression_operation(LETH, $1, $3); 
  }
  |
  TRUE {
    $$ = expression_string(TRUE);
  }
  |
  FALSE {
    $$ = expression_string(FALSE);
  }
  ;

commandlist:
  {
    $$ = NULL;
  }
  |
  cmd commandlist {
    $$ = cmdLisT_construct($1, $2);
  }
  ;

cmd:
  IF boolexpr COMBEG commandlist COMEND {
    $$ = command_construct1(IF, $2, $4);
  }
  |
  IF boolexpr COMBEG commandlist COMEND ELSE COMBEG commandlist COMEND {
    $$ = command_construct2(IF, $2, $4, $8);
  }
  |
  WHILE boolexpr COMBEG commandlist COMEND {
    $$ = command_construct3(WHILE, $2, $4);
  }
  |
  PRINTL PARIN STRING PAROUT ENDING {
    $$ = command_construct4(PRINT, $3);
  }
  |
  LET VAR EQUALAR expr ENDING {
    $$ = command_construct5(ATRIB, $2, $4);
  }
  |
  READL PARIN ECOM VAR PAROUT ENDING {
    $$ = command_construct6(READ, $4);
  }
  |
  PRINTL PARIN STRING VIRG VAR PAROUT ENDING {
    $$ = command_construct7(PRINT2, $3, $5);
  }
  ;
%%


void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}

