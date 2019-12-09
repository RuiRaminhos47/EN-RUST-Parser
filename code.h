// AST definitions
#ifndef __code_h__
#define __code_h__
#include "ast.h"

typedef enum { CPLUS, CMINUS, CTIMES, CDIV, GOTO, IFG, IFL, IFGE, IFLE, IFEQ, IFNE, LABEL, ATRIBU } OpKind;

typedef enum { EMPTY, INT_CONST, STRINGS } ElemKind;

typedef struct {
  ElemKind kind;
  union { // pode ser uma variavel em formato string ou um valor int
    int val;
    char *name;
  } content;
} ELEM;

typedef struct {
  OpKind op;
  ELEM* first;
  ELEM* second;
  ELEM* third;
  ELEM* fourth;
} INSTR;

typedef struct InstrList { // lsita de instruçoes
  INSTR *instruction;
  struct InstrList *next;
} INSTRLIST;

ELEM* newVar(char *s);
ELEM* newInt(int n);
ELEM* empty();
int getValue(ELEM* x);
void printElem(ELEM* x);

INSTR *newInstr(OpKind oper, ELEM* x, ELEM* y, ELEM* z, ELEM* w);

INSTRLIST *addLast(INSTR *s, INSTRLIST *l); // adiciona INSTR s ao fim da lista l
INSTRLIST *append(INSTRLIST *s, INSTRLIST *l); // concatena duas listas
INSTRLIST *newList(INSTR *head, INSTRLIST *tail); // criar lista
INSTR *getFirst(INSTRLIST *s); // retorna o primeiro elemento da lista s
INSTRLIST *nextInstrs(INSTRLIST *s); // retorna a cauda
void printInstr(INSTR *s);
void printInstrList(INSTRLIST *s);

INSTRLIST *compileExp(Expr* e, char *r);
int compileOp(int operator);
char* newTemp();
INSTRLIST* compileBool(BoolExpr* cond, char* labelTrue, char* labelFalse);
INSTRLIST* compileCmd(Cmd* c);
INSTRLIST* compileCmdList(commandList* l);

void printMIPS(INSTRLIST *x);
#endif
