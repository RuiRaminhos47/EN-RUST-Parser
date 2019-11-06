#include <stdlib.h> // for malloc
#include <stdio.h>
#include "ast.h" // AST header
#include "parser.h"
#include "printAbsTree.h"

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
				printf("\n %% \n");
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

void printCmd(Cmd* command) {
	printf("TESTE5");
	switch(command->kind) {
		case CONDITIONAL:
			printf("IF ");
			printBool(command->attr.it.condition);
			printCmdList(command->attr.it.list);
			break;

		case CONDITIONAL2:
			printf("IF ");
			printBool(command->attr.ite.condition);
			printCmdList(command->attr.ite.list1);
			printf("ELSE ");
			printCmdList(command->attr.ite.list2);
			break;

		case LOOP:
			printf("WHILE ");
			printBool(command->attr.w.condition);
			printCmdList(command->attr.w.list);
			break;

		case PRINTL:
			printf("PRINTL ");
			printf("%s\n", command->attr.p.string);
			break;	

		case LET:
			printf("LET ");
			printf("%s ", command->attr.l.var);
			printf("= ");
			printExpr(command->attr.l.expression);
			break;

		case READL:
			printf("READL ");
			printf("%s\n", command->attr.r.var);
			break;

		default:
			break;
	}
}

void printCmdList(commandList* x) {
	// printf("TESTE4"); NÃO CHEGA AQUI, O ERRO É A CHAMAR O ROOT
	printCmd(x->elem);
	printCmdList(x->next);
}