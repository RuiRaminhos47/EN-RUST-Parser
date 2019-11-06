#include <stdlib.h> // for malloc
#include <stdio.h>
#include "ast.h" // AST header
#include "parser.h"
#include "printAbsTree.h"

void printExpr(Expr* exp) {
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
		printExpr(exp->attr.op.left);
		printExpr(exp->attr.op.right);
	}
}

void printBool(BoolExpr* b) {
	if(b->kind==EB_CONSTANT) printf("%d\n", b->attr.bvalue);
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
		printExpr(b->attr.op.bleft);
		printExpr(b->attr.op.bright);
	}
}

void printCmd(Cmd* command) {
	switch(command->kind) {
		case CONDITIONAL:
			printf("if\n");
			printBool(command->attr.it.condition);
			printCmdList(command->attr.it.list);
			break;

		case CONDITIONAL2:
			printf("if\n");
			printBool(command->attr.ite.condition);
			printCmdList(command->attr.ite.list1);
			printf("else\n");
			printCmdList(command->attr.ite.list2);
			break;

		case LOOP:
			printf("while\n");
			printBool(command->attr.w.condition);
			printCmdList(command->attr.w.list);
			break;

		case PRINT:
			printf("println!()\n");
			printf("%s\n", command->attr.p.string);
			break;	

		case PRINT2:
			printf("println!()\n");
			printf("%s\n", command->attr.p2.string);
			printf("%s\n", command->attr.p2.var);
			break;

		case ATRIB:
			printf("let\n");
			printf("%s\n", command->attr.l.var);
			printf("=\n");
			printExpr(command->attr.l.expression);
			break;

		case READ:
			printf("read_line()\n");
			printf("&%s\n", command->attr.r.var);
			break;

		default:
			break;
	}
}

void printCmdList(commandList* x) {
	if(x!=NULL) {
		printCmd(x->elem);
		printCmdList(x->next);
	}
}