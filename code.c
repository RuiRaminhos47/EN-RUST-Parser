#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"
#include <ctype.h>
#include "parser.h"
#include "hash.h"

int variavelControlo = 0;
int variavelControlo2 = 0;

ELEM* newVar(char *s) {
  ELEM* y = (ELEM*) malloc(sizeof(ELEM));
  y->kind = STRINGS;
  y->content.name = strdup(s);
  return y;
}

ELEM* newInt(int n) {
  ELEM* y = (ELEM*) malloc(sizeof(ELEM));
  y->kind = INT_CONST;
  y->content.val = n;
  return y;
}

ELEM* empty() {
  ELEM* y = (ELEM*) malloc(sizeof(ELEM));
  y->kind = EMPTY;
  return y;
}

void printElem(ELEM* x) {
  if(x->kind==EMPTY) return;
  if(x->kind==INT_CONST) printf("%d", x->content.val);
  if(x->kind==STRINGS) printf("%s", x->content.name);
}

int getValue(ELEM* x) { 
  if(x->kind==STRINGS) {
    if(lookup(x->content.name)!=NULL) return lookup(x->content.name)->valor;
    else return -1000;
  }
  if(x->kind==INT_CONST) {
    return x->content.val;
  }
  else return -1000;
}

INSTR *newInstr(OpKind oper, ELEM* x, ELEM* y, ELEM* z, ELEM* w) {
  INSTR *aux = (INSTR*) malloc(sizeof(INSTR));
  aux->op = oper;
  aux->first = x;
  aux->second = y;
  aux->third = z;
  aux->fourth = w;
  return aux;
}

INSTRLIST *newList(INSTR *head, INSTRLIST *tail) {
  INSTRLIST* aux = (INSTRLIST*) malloc(sizeof(*aux)); 
  aux->instruction = head;
  aux->next = tail;
  return aux;
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
        printf("GOTO %s\n", s->first->content.name);
        break;

      case LABEL:
        printf("LABEL %s\n", s->first->content.name);
        break;

      case IFBOOLCONST:
        printf("IF ");
        printElem(s->first);
        printf(" THEN ");
        printElem(s->second);
        printf(" ELSE ");
        printElem(s->third);
        printf("\n");
        break;

      case IFBOOLTRUEORFALSE:
        printf("IF ");
        printElem(s->first);
        printf(" THEN ");
        printElem(s->second);
        printf(" ELSE ");
        printElem(s->third);
        printf("\n");
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
        printf("%s = ", s->first->content.name);
        printElem(s->second);
        printf("\n");
        break;

      default:
        break;
    }
}

void printInstrList(INSTRLIST *s) {
    while((s) != NULL) {
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


INSTRLIST* compileExp(Expr* e, char *r) {
    char* r1;
    char* r2;
    INSTRLIST* code1;
    INSTRLIST* code2;
    INSTRLIST* code3;
    INSTRLIST* code4;

    switch(e->kind) {
        
        case E_OPERATION:
          r1 = strdup(newTemp());
          r2 = strdup(newTemp());
          code1 = compileExp(e->attr.op.left, r1);
          code2 = compileExp(e->attr.op.right, r2);
          int op = compileOp(e->attr.op.operator);
          code3 = append(code1, code2);
          code4 = append(code3, newList(newInstr(op, newVar(r), newVar(r1), newVar(r2), empty()), NULL));
          return code4;
          break;
        
        case E_INTEGER:
          r1 = strdup(r);
          code1 = newList(newInstr(ATRIBU, newVar(r1), newInt(e->attr.value), empty(), empty()), NULL); 
          return code1;
          break;

        case E_VARIABLE:
          r1 =  strdup(r);
          code1 = newList(newInstr(ATRIBU, newVar(r1), newVar(e->attr.var), empty(), empty()), NULL);
          return code1;
        
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
char* newLabel() {
  char aux[20];
  sprintf(aux, "label%d", variavelControlo++);
  char* aux2 = strdup(aux);
  return aux2;
}

INSTRLIST* compileBool(BoolExpr* cond, char* labelTrue, char* labelFalse) {
  char* r1;
  char* r2;
  INSTRLIST* code1;
  INSTRLIST* code2;
  INSTRLIST* code3;
  INSTRLIST* code4;

  switch(cond->kind) {

    case(EB_CONSTANT):
      r1 = strdup(newTemp());
      code1 = newList(newInstr(IFBOOLCONST, newVar(r1), newVar(labelTrue), newVar(labelFalse), empty()), NULL);
      return code1;
      break;

    case(EB_CONSTANTS):
      r1 = strdup(newTemp());
      code1 = newList(newInstr(IFBOOLTRUEORFALSE, newVar(r1), newVar(labelTrue), newVar(labelFalse), empty()), NULL);
      return code1;
      break;

    case(EB_OPERATION):
      r1 = strdup(newTemp());
      r2 = strdup(newTemp());
      code1 = compileExp(cond->attr.op.bleft, r1);
      code2 = compileExp(cond->attr.op.bright, r2);
      code3 = append(code1, code2);
      switch(cond->attr.op.operator) { // EQUALTO, NEQUALTO, GT, LT, GET, LETH - IFG, IFL, IFGE, IFLE, IFEQ, IFNE
          case EQUALTO:
            code4 = append(code3, newList(newInstr(IFEQ, newVar(r1), newVar(r2), newVar(labelTrue), newVar(labelFalse)),NULL)); 
            break;

          case NEQUALTO:  
            code4 = append(code3, newList(newInstr(IFNE, newVar(r1), newVar(r2), newVar(labelTrue), newVar(labelFalse)),NULL)); 
            break;

          case GT:
            code4 = append(code3, newList(newInstr(IFG, newVar(r1), newVar(r2), newVar(labelTrue), newVar(labelFalse)),NULL)); 
            break;

          case LT:
            code4 = append(code3, newList(newInstr(IFL, newVar(r1), newVar(r2), newVar(labelTrue), newVar(labelFalse)),NULL)); 
            break;

          case GET:
            code4 = append(code3, newList(newInstr(IFGE, newVar(r1), newVar(r2), newVar(labelTrue), newVar(labelFalse)),NULL)); 
            break;

          case LETH:
            code4 = append(code3, newList(newInstr(IFLE, newVar(r1), newVar(r2), newVar(labelTrue), newVar(labelFalse)),NULL)); 
            break;

          default:
            break;
      }
      return code4;
      break;
      
    default:
      break;
  }
}

INSTRLIST* compileCmd(Cmd* comando) {
  char* r1;
  char* r2;
  char* labelTrue; 
  char* labelFalse;
  char* labelStart;
  char* labelEnd;
  INSTRLIST* code1;
  INSTRLIST* code2;
  INSTRLIST* code3;
  INSTRLIST* code4;
  INSTRLIST* code5;
  INSTRLIST* code6;
  INSTRLIST* code7;

  switch(comando->kind) { // CONDITIONAL, CONDITIONAL2, LOOP, PRINT, ATRIB, READ, PRINT2

    case CONDITIONAL: // IF
      labelTrue = newLabel();
      labelEnd = newLabel();
      code1 = compileBool(comando->attr.it.condition, labelTrue, labelEnd);
      code2 = append(code1, newList(newInstr(LABEL, newVar(labelTrue), empty(), empty(), empty()), NULL));
      code3 = append(code2, compileCmdList(comando->attr.it.list));
      code4 = append(code3, newList(newInstr(LABEL, newVar(labelEnd), empty(), empty(), empty()), NULL));
      return code4;
      break;

    case CONDITIONAL2: // IF ELSE
      labelTrue = newLabel();
      labelFalse = newLabel();
      labelEnd = newLabel();
      code1 = compileBool(comando->attr.ite.condition, labelTrue, labelFalse);
      code2 = append(code1, newList(newInstr(LABEL, newVar(labelTrue), empty(), empty(), empty()), NULL));
      code3 = append(code2, compileCmdList(comando->attr.ite.list1));
      code4 = append(code3, newList(newInstr(GOTO, newVar(labelEnd), empty(), empty(), empty()), NULL));
      code5 = append(code4, newList(newInstr(LABEL, newVar(labelFalse), empty(), empty(), empty()), NULL));
      code6 = append(code5, compileCmdList(comando->attr.ite.list2));
      code7 = append(code6, newList(newInstr(LABEL, newVar(labelEnd), empty(), empty(), empty()), NULL));
      return code7;
      break;

    case LOOP: // WHILE
      labelStart = newLabel();
      labelEnd = newLabel();
      code1 = compileBool(comando->attr.w.condition, labelStart, labelEnd);
      code2 = append(code1, newList(newInstr(LABEL, newVar(labelStart), empty(), empty(), empty()), NULL));
      code3 = append(code2, compileCmdList(comando->attr.w.list));
      code4 = append(code3, compileBool(comando->attr.w.condition, labelStart, labelEnd));
      code5 = append(code4, newList(newInstr(LABEL, newVar(labelEnd), empty(), empty(), empty()), NULL));
      return code5;
      break;
 
    case ATRIB: // ATRIB
      r1 = strdup(newTemp());
      r2 = strdup(newTemp());
      code1 = compileExp(comando->attr.l.expression, r1);
      code2 = append(code1, newList(newInstr(ATRIB, newVar(comando->attr.l.var), newVar(r1), empty(), empty()), NULL));
      return code2;
      break;

    default:
      break;
  }
}

INSTRLIST* compileCmdList(commandList* l) {
  if(l==NULL) return NULL;
  else {
    INSTRLIST* l1 = compileCmd(l->elem);
    INSTRLIST* l2 = compileCmdList(l->next);
    return (append(l1,l2));
  }
}

// PRINT MIPS DO RUI
void printaMIPS(INSTRLIST *x) {
  while(x!=NULL) {
    switch(x->instruction->op) {
      case CPLUS:
        printf("add %s, %s, %s\n", x->instruction->first->content.name, x->instruction->second->content.name, x->instruction->third->content.name);
        break;

      case CMINUS:
        printf("sub %s, %s, %s\n", x->instruction->first->content.name, x->instruction->second->content.name, x->instruction->third->content.name);
        break;

      case CTIMES:
        printf("mul %s, %s, %s\n", x->instruction->first->content.name, x->instruction->second->content.name, x->instruction->third->content.name);
        break;

      case CDIV:
        printf("div %s, %s, %s\n", x->instruction->first->content.name, x->instruction->second->content.name, x->instruction->third->content.name);
        break;

      case GOTO:
        printf("j %s\n", x->instruction->first->content.name);
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
        printf("beq %s, %s, %s\n", x->instruction->first->content.name, x->instruction->second->content.name, x->instruction->third->content.name);
        printf("%s: \n", x->instruction->fourth->content.name);
        break;

      case IFNE:
        printf("bne %s, %s, %s\n", x->instruction->first->content.name, x->instruction->second->content.name, x->instruction->third->content.name);
        printf("%s: \n", x->instruction->fourth->content.name);
        break;

      case LABEL:
        printf("%s: \n", x->instruction->first->content.name);
        break;

      case ATRIBU:
        printf("addi %s, 0, %s\n", x->instruction->first->content.name, x->instruction->second->content.name);
        break;  

      case IFBOOLCONST:

        break;

      case IFBOOLTRUEORFALSE:

        break;

      default:
        break;
    }
    x = x->next;
  }
}



/* PRINT MIPS DO RUBEN
void printMIPS(INSTRLIST *x) { // temos de printar as variaveis antes e dps O MIPS das operações, ou seja, criar uma
  while((x)!=NULL) {
    switch(x->instruction->op) { //descobrir como se acede aos registos r1,r2 e r3
      
      case CPLUS:
        printf("lw %s into r1\n", x->instruction->second->content.name);
        printf("lw %s into r2\n", x->instruction->third->content.name); //x->instruction->third.content.val
        printf("add r3, r1, r2"); //x->instruction->first.content.name, x->instruction->second.content.name , x->instruction->third.content.val
        printf("sw r3 into %s\n", x->instruction->first->content.name);
        break;

      case CMINUS:
        printf("lw %s into r1\n", x->instruction->second->content.name);
        printf("lw %s into r2\n", x->instruction->third->content.name);
        printf("sub r3, r1, r2");
        printf("sw r3 into %s\n", x->instruction->first->content.name);
        break;

      case CTIMES:
        printf("lw %s into r1\n", x->instruction->second->content.name);
        printf("lw %s into r2\n", x->instruction->third->content.name);
        printf("mul r3, r1, r2");
        printf("sw r3 into %s\n", x->instruction->first->content.name);
        break;

      case CDIV:
        printf("lw %s into r1\n", x->instruction->second->content.name);
        printf("lw %s into r2\n", x->instruction->third->content.name);
        printf("div r3, r1, r2");
        printf("sw r3 into %s\n", x->instruction->first->content.name);
        break;


      case GOTO:
        printf("GOTO %s:\n\n", x->instruction->first->content.name);
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
        printf("LABEL %s:\n", x->instruction->first->content.name);
        break;

      case ATRIBU:

        if(x->instruction->second->kind==INT_CONST){
        printf("lw %s into r1\n", x->instruction->second->content.name);
        }

        if(x->instruction->second->kind == STRINGS){
          printf("lw %d into r1\n", x->instruction->second->content.val);
        }

        printf("sw r1 into %s", x-> instruction->first->content.name);
        break;

      default:
        break;
    }
    x = x->next;
  }
}
*/

