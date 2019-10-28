#include <stdlib.h> // for malloc
#include <stdio.h>
#include "ast.h" // AST header
#include "parser.h"

void printExpr(Expr* exp) {
	if(exp->kind==E_INTEGER) printf("%d ", exp->attr.value);
	if(exp->kind==E_OPERATION) {
		printExpr(exp->attr.op.left);
		switch(exp->attr.op.operator) {
			case PLUS:
				printf("\n + \n");
				break;
			case MINUS:
				printf("\n - \n");
				break;
			case TIMES:
				printf("\n * \n");
				break;	
			case DIV:
				printf("\n / \n");
				break;
			case REST:
				printf("\n % \n");
				break;
			default: yyerror("Unknown operator!");
		}
		printExpr(exp->attr.op.right);
	}
}

void printBool(BoolExpr* b) {
	if(b->kind==EB_CONSTANT) printf("%d ", b->attr.bvalue);
	if(b->kind==EB_OPERATION) {
		printExpr(b->attr.op.bleft);
		switch(b->attr.op.operator) {
			case EQUALTO:
				printf("\n == \n");
				break;
			case NEQUALTO:
				printf("\n != \n");
				break;
			case GT:
				printf("\n > \n");
				break;	
			case LT:
				printf("\n < \n");
				break;
			case GET:
				printf("\n >= \n");
				break;
			case LETH:
				printf("\n <= \n");
				break;
			default: yyerror("Unknown operator!");
		}
		printExpr(b->attr.op.bright);
	}
}