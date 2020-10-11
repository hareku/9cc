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
  TK_NUM,      // Integer literals
  TK_EOF,      // End-of-file markers
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
void expect(char *op);
int expect_number();

/**
 * codegen.c
 */
typedef struct Node Node;

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
} NodeKind;

struct Node {
  NodeKind kind;
  Node *lhs; // left
  Node *rhs; // right
  int val;   // Use if kind is ND_NUM
};

Node *expr();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *primary();
Node *unary();

void gen(Node *node);

/**
 * container.c
 */
void error(char *fmt, ...);
