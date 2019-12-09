#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "printAbsTree.h"
#include "hash.h"
#include "code.h"

int eval(Expr* expr) {
  int result = 0;
  if (expr == 0) {
    yyerror("Null expression!!");
  }
  else if (expr->kind == E_INTEGER) {
    result = expr->attr.value; 
  } 
  else if (expr->kind == E_OPERATION) {
    int vLeft = eval(expr->attr.op.left);
    int vRight = eval(expr->attr.op.right);
    switch (expr->attr.op.operator) {
      case PLUS: 
        result = vLeft + vRight; 
        break;
      case MINUS:
        result = vLeft - vRight;
        break;
      case TIMES:
        result = vLeft * vRight;
        break;
      case DIV:
        result = vLeft / vRight;
        break;
      case REST:
        result = vLeft % vRight;
        break;
      default: yyerror("Unknown operator!");
    }
  }
  return result;
}

int main(int argc, char** argv) {
  /*--argc; ++argv;
  
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } 
  
  if (yyparse() == 0) {
      // Primeiro trabalho
      // printCmdList(root, 0);

  }*/

  // Expressões
  /*
  Expr* e1 = ast_integer(1);
  Expr* e2 = ast_integer(5);
  Expr* e3 = ast_operation(MINUS, e2, e1);
  Expr* e4 = ast_operation(PLUS, e1, e2);
  Expr* e5 = ast_operation(TIMES, e4, e3);
  INSTRLIST* aux = compileExp(e5, "x");
  printInstrList(aux);
  return 0;*/

  // Booleano expressões
  /*
  BoolExpr* e1 = expression_string(TRUE);
  INSTRLIST* aux = compileBool(e1, "labelV", "labelF");
  printInstrList(aux);
  */
  /*
  Expr* e1 = ast_integer(2);
  Expr* e2 = ast_integer(3);
  Expr* e3 = ast_operation(PLUS, e1, e2);
  Expr* e4 = ast_integer(4);
  Expr* e5 = ast_integer(5);
  Expr* e6 = ast_operation(MINUS, e4, e5);
  INSTRLIST* aux = compileBool(expression_operation(GT, e3, e6), "labelV", "labelF");
  printInstrList(aux);
  */
  
  // Comandos


}
