// AST constructor functions

#include <stdlib.h> // for malloc
#include "ast.h" // AST header
#include <stdio.h>

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

Expr* ast_var(char* var) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_VARIABLE;
  node->attr.var = var;
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

commandList* cmdLisT_construct(Cmd* elem, commandList* resto) {
  // OK 2
  commandList* lista = (commandList*) malloc(sizeof(commandList));
  lista->elem = elem;
  lista->next = resto;
  // OK 3
  return lista;
}

Cmd* command_construct1(int command, BoolExpr* condition, commandList* commandList) {
  Cmd* commando = (Cmd*) malloc(sizeof(Cmd));
  commando->kind = CONDITIONAL;
  commando->attr.it.operator = command;
  commando->attr.it.condition = condition;
  commando->attr.it.list = commandList;
  return commando;
}

Cmd* command_construct2(int command, BoolExpr* condition, commandList* commandList1, commandList* commandList2) {
  Cmd* commando = (Cmd*) malloc(sizeof(Cmd));
  commando->kind = CONDITIONAL2;
  commando->attr.ite.operator = command;
  commando->attr.ite.condition = condition;
  commando->attr.ite.list1 = commandList1;
  commando->attr.ite.list2 = commandList2;
  return commando;
}

Cmd* command_construct3(int command, BoolExpr* condition, commandList* commandList) {
  Cmd* commando = (Cmd*) malloc(sizeof(Cmd));
  commando->kind = LOOP;
  commando->attr.w.operator = command;
  commando->attr.w.condition = condition;
  commando->attr.w.list = commandList;
  return commando;
}

Cmd* command_construct4(int command, char* string) {
  Cmd* commando = (Cmd*) malloc(sizeof(Cmd));
  commando->kind = PRINT;
  commando->attr.p.operator = command;
  commando->attr.p.string = string;
  return commando;
}

Cmd* command_construct5(int command, char* var, Expr* expression) {
  Cmd* commando = (Cmd*) malloc(sizeof(Cmd));
  commando->kind = ATRIB;
  commando->attr.l.operator = command;
  commando->attr.l.var = var;
  commando->attr.l.expression = expression;
  return commando;
}

Cmd* command_construct6(int command, char* var) {
  // OK 1 
  Cmd* commando = (Cmd*) malloc(sizeof(Cmd));
  commando->kind = READ;
  commando->attr.r.operator = command;
  commando->attr.r.var = var;
  return commando;
}
