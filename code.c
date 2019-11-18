#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"
#include <ctype.h>

ELEM newVar(char *s) {
  ELEM y;
  y.kind = STRING;
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

INSTR newInstr(OpKind oper, ELEM x, ELEM y, ELEM z, ELEM w) { 
  INSTR aux;
  aux.op = oper;
  aux.first = x;
  aux.second = y;
  aux.third = z;
  aux.fourth = w;
  return aux;
}

INSTRLIST newList(INSTR head, INSTRLIST tail) {
  INSTRLIST new = malloc(sizeof(struct InstrList));
  new -> instruction = head;
  new -> next = tail;
  return new;
}

INSTRLIST addLast(INSTR s, INSTRLIST l) {
    INSTRLIST aux = l;
    if(l == NULL) {
      return newList(s, NULL);
    }
    while((l->next) != NULL) {
      l = l->next;
    }
    l->next = newList(s, NULL);
    return aux;
}

INSTRLIST append(INSTRLIST s, INSTRLIST l) {
    INSTRLIST aux = s;
    if(s == NULL) {
      return l;
    }
    if(l == NULL) {
      return s;
    }
    while((s->next) != NULL) {
      s = s->next;
    }
    s->next = l;
    return aux;
}

INSTR getFirst(INSTRLIST s) {
    return s->instruction;
}

INSTRLIST nextInstrs(INSTRLIST s) {
    return s->next;
}

void printInstr(INSTR s) {
    switch(s.op) {
      case PLUS:
        printElem(s.first);
        printf(" = ");
        printElem(s.second);
        printf(" + ");
        printElem(s.third);
        printf("\n");
        break;

      case MINUS:
        printElem(s.first);
        printf(" = ");
        printElem(s.second);
        printf(" - ");
        printElem(s.third);
        printf("\n");
        break;

      case DIV:
        printElem(s.first);
        printf(" = ");
        printElem(s.second);
        printf(" / ");
        printElem(s.third);
        printf("\n");
        break;

      case MULT:
        printElem(s.first);
        printf(" = ");
        printElem(s.second);
        printf(" * ");
        printElem(s.third);
        printf("\n");
        break;
      
      case GOTO:
        printf("GOTO %s\n", s.first.content.name);
        break;

      case LABEL:
        printf("LABEL %s\n", s.first.content.name);
        break;
      
      case IFG:
        printf("IF "); 
        printElem(s.first);
        printf(">");
        printElem(s.second);
        printf(" THEN ");
        printElem(s.third);
        printf(" ELSE ");
        printElem(s.fourth);
        printf("\n");
        break;

      case IFL:
        printf("IF "); 
        printElem(s.first);
        printf("<");
        printElem(s.second);
        printf(" THEN ");
        printElem(s.third);
        printf(" ELSE ");
        printElem(s.fourth);
        printf("\n");
        break;

      case IFGE:
        printf("IF "); 
        printElem(s.first);
        printf(">=");
        printElem(s.second);
        printf(" THEN ");
        printElem(s.third);
        printf(" ELSE ");
        printElem(s.fourth);
        printf("\n");
        break;

      case IFLE:
        printf("IF "); 
        printElem(s.first);
        printf("<=");
        printElem(s.second);
        printf(" THEN ");
        printElem(s.third);
        printf(" ELSE ");
        printElem(s.fourth);
        printf("\n");
        break;

      case IFEQ:
        printf("IF "); 
        printElem(s.first);
        printf("==");
        printElem(s.second);
        printf(" THEN ");
        printElem(s.third);
        printf(" ELSE ");
        printElem(s.fourth);
        printf("\n");
        break;

      case IFNE:
        printf("IF "); 
        printElem(s.first);
        printf("!=");
        printElem(s.second);
        printf(" THEN ");
        printElem(s.third);
        printf(" ELSE ");
        printElem(s.fourth);
        printf("\n");
        break;
      
      case ATRIB:
        printf("%s = ", s.first.content.name);
        printElem(s.second);
        break;
     
      default:
        break;
    }
}

void printInstrList(INSTRLIST s) {
    while((s->next) != NULL) {
      printInstr(s->instruction);
      s = s->next;
    }
}

InstrList compileExp(Expr e, char *r) {
  // acabar!
}