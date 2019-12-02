#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"
#include <ctype.h>
#include "parser.h"

int variavelControlo = 0;

ELEM newVar(char *s) {
  ELEM y;
  y.kind = STRINGS;
  y.content.name = strdup(s);
  return y;
}

ELEM newInt(int n) {
  ELEM y;
  y.kind = INT_CONST;
  y.content.val = n;
  return y;
}

ELEM empty() {
  ELEM y;
  y.kind = EMPTY;
  return y;
}

void printElem(ELEM x) {
  if(x.kind==EMPTY) return;
  if(x.kind==INT_CONST) printf("%d", x.content.val);
  if(x.kind==STRING) printf("%s", x.content.name);
}

INSTR *newInstr(OpKind oper, ELEM x, ELEM y, ELEM z, ELEM w) {
  INSTR *aux;
  aux->op = oper;
  aux->first = x;
  aux->second = y;
  aux->third = z;
  aux->fourth = w;
  return aux;
}

INSTRLIST *newList(INSTR *head, INSTRLIST *tail) {
  INSTRLIST *new = malloc(sizeof(struct InstrList));
  new->instruction = head;
  new->next = tail;
  return new;
}

INSTRLIST *addLast(INSTR *s, INSTRLIST *l) {
    INSTRLIST *aux = l;
    if(l == NULL) {
      return newList(s, NULL);
    }
    while((l->next) != NULL) {
      l = l->next;
    }
    l->next = newList(s, NULL);
    return aux;
}

INSTRLIST *append(INSTRLIST *s, INSTRLIST *l) {
    INSTRLIST *p;
    if(s==NULL) return l;
    for(p=s; p->next !=NULL; p=p->next) {}
    p->next = l;
    return s;
}

INSTR *getFirst(INSTRLIST *s) {
    return s->instruction;
}

INSTRLIST *nextInstrs(INSTRLIST *s) {
    return s->next;
}

void printInstr(INSTR *s) {
    switch(s->op) {
      case CPLUS:
        printElem(s->first);
        printf(" = ");
        printElem(s->second);
        printf(" + ");
        printElem(s->third);
        printf("\n");
        break;

      case CMINUS:
        printElem(s->first);
        printf(" = ");
        printElem(s->second);
        printf(" - ");
        printElem(s->third);
        printf("\n");
        break;

      case CDIV:
        printElem(s->first);
        printf(" = ");
        printElem(s->second);
        printf(" / ");
        printElem(s->third);
        printf("\n");
        break;

      case CTIMES:
        printElem(s->first);
        printf(" = ");
        printElem(s->second);
        printf(" * ");
        printElem(s->third);
        printf("\n");
        break;

      case GOTO:
        printf("GOTO %s\n", s->first.content.name);
        break;

      case LABEL:
        printf("LABEL %s\n", s->first.content.name);
        break;

      case IFG:
        printf("IF ");
        printElem(s->first);
        printf(">");
        printElem(s->second);
        printf(" THEN ");
        printElem(s->third);
        printf(" ELSE ");
        printElem(s->fourth);
        printf("\n");
        break;

      case IFL:
        printf("IF ");
        printElem(s->first);
        printf("<");
        printElem(s->second);
        printf(" THEN ");
        printElem(s->third);
        printf(" ELSE ");
        printElem(s->fourth);
        printf("\n");
        break;

      case IFGE:
        printf("IF ");
        printElem(s->first);
        printf(">=");
        printElem(s->second);
        printf(" THEN ");
        printElem(s->third);
        printf(" ELSE ");
        printElem(s->fourth);
        printf("\n");
        break;

      case IFLE:
        printf("IF ");
        printElem(s->first);
        printf("<=");
        printElem(s->second);
        printf(" THEN ");
        printElem(s->third);
        printf(" ELSE ");
        printElem(s->fourth);
        printf("\n");
        break;

      case IFEQ:
        printf("IF ");
        printElem(s->first);
        printf("==");
        printElem(s->second);
        printf(" THEN ");
        printElem(s->third);
        printf(" ELSE ");
        printElem(s->fourth);
        printf("\n");
        break;

      case IFNE:
        printf("IF ");
        printElem(s->first);
        printf("!=");
        printElem(s->second);
        printf(" THEN ");
        printElem(s->third);
        printf(" ELSE ");
        printElem(s->fourth);
        printf("\n");
        break;

      case ATRIBU:
        printf("%s = ", s->first.content.name);
        printElem(s->second);
        break;

      default:
        break;
    }
}

void printInstrList(INSTRLIST *s) {
    while((s->next) != NULL) {
      printInstr(s->instruction);
      s = s->next;
    }
}

int compileOp(int op) {
  switch(op) {
    case PLUS:
      return CPLUS;
    case MINUS:
      return CMINUS;
    case DIV:
      return CDIV;
    case TIMES:
      return CTIMES;
  }
}

INSTRLIST *compileExp(Expr* e, char *r) {
    char* r1;
    char* r2;
    switch(e->kind) {
        case E_OPERATION:
          r1 = strdup(newTemp());
          r2 = strdup(newTemp());
          INSTRLIST *code1 = compileExp(e->attr.op.left, r1);
          INSTRLIST *code2 = compileExp(e->attr.op.right, r2);
          int op = compileOp(e->attr.op.operator);
          INSTRLIST *code3 = append(code1, code2);
          INSTRLIST *code4 = append(code3, newList(newInstr(op, newVar(r), newVar(r1), newVar(r2), empty()), NULL));
          return code4;
          break;
        default:
          break;
    }
}

char* newTemp() {
  char aux[20];
  sprintf(aux, "t%d", variavelControlo++);
  char* aux2 = strdup(aux);
  return aux2;
}

void printMIPS(INSTRLIST *x) { // temos de printar as variaveis antes e dps O MIPS das operações, ou seja, criar uma
  while((x->next)!=NULL) {
    switch(x->instruction->op) { //descobrir como se acede aos registos r1,r2 e r3
      case CPLUS:
        printf("lw %s into r1\n", x->instruction->second.content.name);
        printf("lw %s into r2\n", x->instruction->third.content.name); //x->instruction->third.content.val
        printf("add r3, r1, r2"); //x->instruction->first.content.name, x->instruction->second.content.name , x->instruction->third.content.val
        printf("sw r3 into %s\n", x->instruction->first.content.name);
        break;

      case CMINUS:
        printf("lw %s into r1\n", x->instruction->second.content.name);
        printf("lw %s into r2\n", x->instruction->third.content.name);
        printf("sub r3, r1, r2");
        printf("sw r3 into %s\n", x->instruction->first.content.name);
        break;

      case CTIMES:
        printf("lw %s into r1\n", x->instruction->second.content.name);
        printf("lw %s into r2\n", x->instruction->third.content.name);
        printf("mul r3, r1, r2");
        printf("sw r3 into %s\n", x->instruction->first.content.name);
        break;

      case CDIV:
        printf("lw %s into r1\n", x->instruction->second.content.name);
        printf("lw %s into r2\n", x->instruction->third.content.name);
        printf("div r3, r1, r2");
        printf("sw r3 into %s\n", x->instruction->first.content.name);
        break;


      case GOTO:
        printf("GOTO %s:\n\n", x->instruction->first.content.name);
        break;

      case IFG:
        break;

      case IFL:
        break;

      case IFGE:
        break;

      case IFLE:
        break;

      case IFEQ:
        break;

      case IFNE:
        break;

      case LABEL:
        printf("LABEL %s:\n", x->instruction->first.content.name);
        break;

      case ATRIBU:

        if(x->instruction->second.kind==INT_CONST){
        printf("lw %s into r1\n", x->instruction->second.content.name);
        }

        if(x->instruction->second.kind == STRINGS){
          printf("lw %sinto r1\n", x->instruction->second.content.val);
        }

        printf("sw r1 into %s", x-> instruction->first.content.name);
        break;

      default:
        break;
    }
    x = x->next;
  }
}
