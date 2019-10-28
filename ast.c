// AST constructor functions

#include <stdlib.h> // for malloc
#include "ast.h" // AST header

Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}

Expr* ast_operation
(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

BoolExpr* expression_integer(int v) {
  BoolExpr* expression = (BoolExpr*) malloc(sizeof(BoolExpr));
  expression->kind = EB_CONSTANT;
  expression->attr.bvalue = v;
  return expression;
}

BoolExpr* expression_operation(int operator, Expr* left, Expr* right) {
  BoolExpr* expression = (BoolExpr*) malloc(sizeof(BoolExpr));
  expression->kind = EB_OPERATION;
  expression->attr.op.operator = operator;
  expression->attr.op.bleft = left;
  expression->attr.op.bright = right;
  return expression;
}

// ----------------------------------------------------------------------------------------------- A MUDAR

Cmd* command_construct1(int command, BoolExpr* condition, commandList* commandList) {
  Cmd* command = (Cmd*) malloc(sizeof(Cmd));
  command->kind = CONDITIONAL;
  command->attr.it.operator = command;
  command->attr.it.condition = condition;
  command->attr.it.list = commandList;
  return command;
}

Cmd* command_construct2(int command, BoolExpr* condition, commandList* commandList1, commandList* commandList2) {
  Cmd* command = (Cmd*) malloc(sizeof(Cmd));
  command->kind = CONDITIONAL;
  command->attr.ite.operator = command;
  command->attr.ite.condition = condition;
  command->attr.ite.list = commandList1;
  command->attr.ite.list2 = commandList2;
  return command;
}

Cmd* command_construct3(int command, BoolExpr* condition, commandList* commandList) {
  Cmd* command = (Cmd*) malloc(sizeof(Cmd));
  command->kind = LOOP;
  command->attr.w.operator = command;
  command->attr.w.condition = condition;
  command->attr.w.list = commandList;
  return command;
}

Cmd* command_construct4(int command, char* string) {
  Cmd* command = (Cmd*) malloc(sizeof(Cmd));
  command->kind = PRINTL;
  command->attr.p.operator = command;
  command->attr.p.string = string;
  return command;
}

Cmd* command_construct5(int command, char* var, Expr* expression) {
  Cmd* command = (Cmd*) malloc(sizeof(Cmd));
  command->kind = LET;
  command->attr.l.operator = command;
  command->attr.l.var = var;
  command->attr.l.expression = expression;
  return command;
}

Cmd* command_construct6(int command, char* var) {
  Cmd* command = (Cmd*) malloc(sizeof(Cmd));
  command->kind = READL;
  command->attr.r.operator = command;
  command->attr.r.var = var;
  return command;
}