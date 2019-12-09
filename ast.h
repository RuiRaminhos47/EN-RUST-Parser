
// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions
struct _Expr {
  enum { 
    E_INTEGER,
    E_OPERATION,
    E_VARIABLE
  } kind;
  union {
    int value; // for integer values
    struct { 
      int operator; // PLUS, MINUS, etc 
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
    char* var;
  } attr;
};

typedef struct _Expr Expr; // Convenience typedef

struct _BoolExpr {
  enum { 
    EB_CONSTANT, // 1 ou 0
    EB_CONSTANTS, // true ou false
    EB_OPERATION
  } kind;
  union {
    int bvalue; // for integer values
    int operator; // TRUE AND FALSE
    struct { 
      int operator; // EQUALTO, NEQUALTO, GT, LT, GET, LETH  
      struct _Expr* bleft;
      struct _Expr* bright;
    } op; // for binary expressions
  } attr;
};

typedef struct _BoolExpr BoolExpr;

struct _Cmd {
  enum { 
    CONDITIONAL,
    CONDITIONAL2,
    LOOP,
    PRINT,
    ATRIB,
    READ,
    PRINT2
  } kind;
  union {

    struct { 
      int operator; // IF
      struct _BoolExpr* condition;
      struct _commandList* list;
    } it; 

    struct {
      int operator; // IF (CONDIÇAO) ELSE
      struct _BoolExpr* condition;
      struct _commandList* list1;
      struct _commandList* list2;
    } ite; 

    struct { 
      int operator; // WHILE
      struct _BoolExpr* condition;
      struct _commandList* list;
    } w;

    struct {
      int operator; // PRINT
      char* string;
    } p;

    struct {
      int operator; // ATRIB
      char* var;
      struct _Expr* expression;
    } l;

    struct {
      int operator; // READ
      char* var;
    } r;

    struct {
      int operator; // PRINT2
      char* string;
      char* var;
    } p2;

  } attr;

};

typedef struct _Cmd Cmd; // podemos chamar struct _Cmd ou Cmd

struct _commandList {
  Cmd* elem;
  struct _commandList *next;
};

typedef struct _commandList commandList;

// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
Expr* ast_var(char* var);
BoolExpr* expression_integer(int v);
BoolExpr* expression_string(int operator);
BoolExpr* expression_operation(int operator, Expr* left, Expr* right);
Cmd* command_construct1(int command, BoolExpr* condition, commandList* commandList); // IF
Cmd* command_construct2(int command, BoolExpr* condition, commandList* commandList1, commandList* commandList2); // IF THEN ELSE
Cmd* command_construct3(int command, BoolExpr* condition, commandList* commandList); // WHILE
Cmd* command_construct4(int command, char* string); // PRINT
Cmd* command_construct5(int command, char* var, Expr* expression); // ATRIB
Cmd* command_construct6(int command, char* var); // READ
Cmd* command_construct7(int command, char* string, char* var);
commandList* cmdLisT_construct(Cmd* elem, commandList* resto);

#endif
