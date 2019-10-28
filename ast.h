
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
    EB_CONSTANT,
    EB_OPERATION
  } kind;
  union {
    int bvalue; // for integer values
    struct { 
      int operator; // EQUALTO, NEQUALTO, GT, LT, GET, LETH  
      struct _Expr* bleft;
      struct _Expr* bright;
    } op; // for binary expressions
  } attr;
};

typedef struct _BoolExpr BoolExpr;

struct commandList {
  Cmd* elem;
  struct commandList *next;
};

typedef struct _commandList commandList;

struct _Cmd {
  enum { 
    CONDITIONAL,
    LOOP,
    PRINTL,
    LET,
    READL
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
      int operator; // PRINTL
      char* string;
    } p;

    struct {
      int operator; // LET
      char* var;
      struct _Expr* expression;
    } l;

    struct {
      int operator; // READL
      char* var;
    } r;

  } attr;

};

typedef struct _Cmd Cmd; 

// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
Expr* ast_var(char* var);
BoolExpr* expression_integer(int v);
BoolExpr* expression_operation(int operator, Expr* left, Expr* right);
Cmd* command_construct1(int command, BoolExpr* condition, commandList* commandList); // IF
Cmd* command_construct2(int command, BoolExpr* condition, commandList* commandList1, commandList* commandList2); // IF THEN ELSE
Cmd* command_construct3(int command, BoolExpr* condition, commandList* commandList); // WHILE
Cmd* command_construct4(int command, char* string); // PRINTL
Cmd* command_construct5(int command, char* var, Expr* expression); // LET
Cmd* command_construct6(int command, char* var); // READL

#endif
