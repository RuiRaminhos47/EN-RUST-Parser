#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "printAbsTree.h"
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
  --argc; ++argv;
  
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
      
      INSTRLIST* auxiliar = compileCmdList(root);
      printInstrList(auxiliar);

      FILE *fp;

      if((fp=freopen("MIPS.txt", "w" ,stdout))==NULL) {
        printf("Cannot open file.\n");
        exit(1);
      }

      MAPEIADATA* hashM = compileMap(root);
      printf(".data \n");
      printaMAPA(hashM);
      printf("\n.text \n");
      printaMIPS(auxiliar);

      fclose(fp);

  }
}
