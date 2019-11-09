#include <stdlib.h> // for malloc
#include <stdio.h>
#include "ast.h" // AST header
#include "parser.h"
#include "printAbsTree.h"

void fazArvore(int profundidade) {
	for(int i=0; i<profundidade; i++) {
		printf("  ");
	}
}

void printExpr(Expr* exp, int profundidade) {

	fazArvore(profundidade);

	if(exp->kind==E_INTEGER) printf("%d\n", exp->attr.value);
	if(exp->kind==E_VARIABLE) printf("%s\n", exp->attr.var);
	if(exp->kind==E_OPERATION) {
		switch(exp->attr.op.operator) {
			case PLUS:
				printf("+\n");
				break;
			case MINUS:
				printf("-\n");
				break;
			case TIMES:
				printf("*\n");
				break;	
			case DIV:
				printf("/\n");
				break;
			case REST:
				printf("%%\n");
				break;
			default: yyerror("Unknown operator!");
		}
		printExpr(exp->attr.op.left, profundidade+1);
		printExpr(exp->attr.op.right, profundidade+1);
	}
}

void printBool(BoolExpr* b, int profundidade) {

	fazArvore(profundidade);

	if(b->kind==EB_CONSTANT) printf("%d\n", b->attr.bvalue);
	if(b->kind==EB_CONSTANTS) {
		switch(b->attr.operator) {
			case TRUE:
				printf("true\n");
				break;
			case FALSE:
				printf("false\n");
				break;
			default: yyerror("Unknown bool!");
		}
	}
	if(b->kind==EB_OPERATION) {
		switch(b->attr.op.operator) {
			case EQUALTO:
				printf("==\n");
				break;
			case NEQUALTO:
				printf("!=\n");
				break;
			case GT:
				printf(">\n");
				break;	
			case LT:
				printf("<\n");
				break;
			case GET:
				printf(">=\n");
				break;
			case LETH:
				printf("<=\n");
				break;
			default: yyerror("Unknown operator!");
		}
		printExpr(b->attr.op.bleft, profundidade+1);
		printExpr(b->attr.op.bright, profundidade+1);
	}
}

void printCmd(Cmd* command, int profundidade) {

	fazArvore(profundidade);

	switch(command->kind) {
		case CONDITIONAL:
			printf("if\n");
			printBool(command->attr.it.condition, profundidade+1);
			printCmdList(command->attr.it.list, profundidade+1);
			break;

		case CONDITIONAL2:
			printf("if\n");
			printBool(command->attr.ite.condition, profundidade+1);
			printCmdList(command->attr.ite.list1, profundidade+1);
			fazArvore(profundidade);
			printf("else\n");
			printCmdList(command->attr.ite.list2, profundidade+1);
			break;

		case LOOP:
			printf("while\n");
			printBool(command->attr.w.condition, profundidade+1);
			printCmdList(command->attr.w.list, profundidade+1);
			break;

		case PRINT:
			printf("println!()\n");
			fazArvore(profundidade+1);
			printf("%s\n", command->attr.p.string);
			break;	

		case PRINT2:
			printf("println!()\n");
			fazArvore(profundidade+1);
			printf("%s\n", command->attr.p2.string);
			fazArvore(profundidade+1);
			printf("%s\n", command->attr.p2.var);
			break;

		case ATRIB:
			printf("let\n");
			fazArvore(profundidade+1);
			printf("%s\n", command->attr.l.var);
			//printf("=\n");
			printExpr(command->attr.l.expression, profundidade+1);
			break;

		case READ:
			printf("read_line()\n");
			fazArvore(profundidade+1);
			printf("&%s\n", command->attr.r.var);
			break;

		default:
			break;
	}
}

void printCmdList(commandList* x, int profundidade) {
	if(x!=NULL) {
		printCmd(x->elem, profundidade);
		printCmdList(x->next, profundidade);
	}
}