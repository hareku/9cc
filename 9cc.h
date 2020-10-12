#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * parse.c
 */
typedef struct Token Token;

typedef enum {
  TK_RESERVED, // Keywords or punctuators
  TK_IDENT,    // Identifier
  TK_NUM,      // Integer literals
  TK_EOF,      // End-of-file markers
  TK_RETURN,   // "return"
} TokenKind;

struct Token {
  TokenKind kind; // Token kind
  Token *next;    // Next token
  int val;        // If kind is TK_NUM, its value
  char *str;      // Token string
  int len;        // Token length
};

char *user_input;
Token *token;

Token *tokenize();
bool consume(char *op);
Token *consume_ident();
void expect(char *op);
int expect_number();
bool at_eof();
bool consume_return();

typedef struct LVar LVar;
struct LVar {
  LVar *next;
  char *name;
  int len;
  int offset;
};
LVar *locals;
LVar *find_lvar(Token *tok);

/**
 * codegen.c
 */
typedef struct Node Node;
Node *code[100];

typedef enum {
  ND_ADD, // +
  ND_SUB, // -
  ND_MUL, // *
  ND_DIV, // /
  ND_NUM, // integer
  ND_EQ,  // ==
  ND_NE,  // !=
  ND_LT,  // <
  ND_LE,  // <=
  ND_ASSIGN, // =
  ND_LVAR, // local val
  ND_RETURN, // return
} NodeKind;

struct Node {
  NodeKind kind;
  Node *lhs; // left
  Node *rhs; // right
  int val;   // Use if kind is ND_NUM
  int offset; // Use if kind is ND_LVAR
};

Node *expr();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *primary();
Node *unary();

void gen(Node *node);
void program();

/**
 * container.c
 */
void error(char *fmt, ...);
