#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"
#include <ctype.h>
#include "parser.h"

int variavelControlo = 0;
int variavelControlo2 = 0;
char* jaExistem[30];
int variavelControloJaExistem=0;

MAPEIADATA* newData(char* inicio, MAPEIADATA* cauda) {
  MAPEIADATA* hashM = (MAPEIADATA*) malloc(sizeof(*hashM));
  hashM->var = inicio;
  hashM->next = cauda;
  return hashM;
}

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

MAPEIADATA* appendHash(MAPEIADATA* one, MAPEIADATA* two) {
    MAPEIADATA* p;
    if(one==NULL) return two;
    for(p=one; p->next != NULL; p = p->next) {}
    p->next = two;
    return one;
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

      case PRINTS:
        printf("PRINT "); 
        printElem(s->first);
        printf("\n");
        break;

      case PRINTS2:
        printf("PRINT "); 
        printElem(s->first);
        printf(" ");
        printElem(s->second);
        printf("\n");
        break;

      case READS:
        printf("READ "); 
        printElem(s->first);
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

void printaMAPA(MAPEIADATA* mapa) {
    while(mapa!=NULL) {
      printf("int: .%s\n", mapa->var);
      mapa = mapa->next;
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
          code2 = append(code1, compileExp(e->attr.op.right, r2));
          int op = compileOp(e->attr.op.operator);
          code3 = append(code2, newList(newInstr(op, newVar(r), newVar(r1), newVar(r2), empty()), NULL));
          return code3;
          break;
        
        case E_INTEGER:
          code1 = newList(newInstr(ATRIBU, newVar(r), newInt(e->attr.value), empty(), empty()), NULL); 
          return code1;
          break;

        case E_VARIABLE:
          code1 = newList(newInstr(ATRIBU, newVar(r), newVar(e->attr.var), empty(), empty()), NULL);
          return code1;
        
        default:
          break;
    }
}

char* newTemp() {
  if(variavelControlo==8) variavelControlo=0;
  char aux[20];
  sprintf(aux, "t%d", variavelControlo++);
  char* aux2 = strdup(aux);
  return aux2;
} 
char* newLabel() {
  char aux[20];
  sprintf(aux, "label%d", variavelControlo2++);
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
      if(cond->attr.operator==TRUE) code1 = newList(newInstr(IFBOOLTRUEORFALSE, newVar("true"), newVar(labelTrue), newVar(labelFalse), empty()), NULL);
      if(cond->attr.operator==FALSE) code1 = newList(newInstr(IFBOOLTRUEORFALSE, newVar("false"), newVar(labelTrue), newVar(labelFalse), empty()), NULL);
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

MAPEIADATA* compileMapAtrib(Cmd* c) {
  if(c->kind!=ATRIB || existeNoMap(c->attr.l.var)==1) return NULL;
  MAPEIADATA* code1;
  code1 = newData(c->attr.l.var, NULL);
  jaExistem[variavelControloJaExistem++] = c->attr.l.var;
  return code1;
}

MAPEIADATA* compileMap(commandList* l) {
  if(l==NULL) return NULL;
  else {
    MAPEIADATA* l1 = compileMapAtrib(l->elem);
    if(l1==NULL) return compileMap(l->next);
    return (appendHash(l1,compileMap(l->next)));
  }
}

int existeNoMap(char* var) {
  int aux=0;
  while(aux<variavelControloJaExistem) {
    if(strcmp(jaExistem[aux], var)==0) return 1;
    aux++;
  }
  return 0;
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
      code1 = compileExp(comando->attr.l.expression, r1);
      return code1;
      break;

    case PRINT:
      code1= newList(newInstr(PRINTS, newVar(comando->attr.p.string), empty(), empty(), empty()), NULL);
      return code1;
      break;

    case READ:
      r1 = strdup(newTemp());
      code1 = newList(newInstr(READS, newVar(r1), empty(), empty(), empty()), NULL);
      return code1;
      break;

    case PRINT2:
      r1 = strdup(newTemp());
      code1 = newList(newInstr(PRINTS2, newVar(comando->attr.p2.string), newVar(r1), empty(), empty()), NULL);
      return code1;
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
        printf("j %s \n", x->instruction->fourth->content.name);
        break;

      case IFNE:
        printf("bne %s, %s, %s\n", x->instruction->first->content.name, x->instruction->second->content.name, x->instruction->third->content.name);
        printf("j %s \n", x->instruction->fourth->content.name);
        break;

      case LABEL:
        printf("%s: \n", x->instruction->first->content.name);
        break;

      case ATRIBU:
        if(x->instruction->second->kind==INT_CONST) printf("li %s, %d\n", x->instruction->first->content.name, x->instruction->second->content.val);
        if(x->instruction->second->kind==STRINGS) printf("li %s, %s\n", x->instruction->first->content.name, x->instruction->second->content.name);
        break;  

      case IFBOOLCONST:

        break;

      case IFBOOLTRUEORFALSE:

        break;

      case PRINTS:
        printf("li $v0, 4\n");
        printf("la $a0, %s\n", x->instruction->first->content.name);
        printf("syscall\n");
        break;

      case PRINTS2:
        printf("li $v0, 1\n");
        printf("move $a0, %s\n", x->instruction->second->content.name);
        printf("syscall\n");
        break;

      case READS:

        break;

      default:
        break;
    }
    x = x->next;
  }
}


