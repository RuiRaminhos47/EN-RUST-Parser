#ifndef __printAbsTree_h__
#define __printAbsTree_h__

void printExpr(Expr* exp, int profundidade);
void printBool(BoolExpr* b, int profundidade);
void printCmd(Cmd* command, int profundidade);
void printCmdList(commandList* x, int profundidade);

#endif