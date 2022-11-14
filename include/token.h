#ifndef __TOKEN_H__
#define __TOKEN_H__

enum TOKEN_TYPE {
  TYPE_UNDEFINED = 0,         // undefined token
  TYPE_IDENTIFIER,            //
  TYPE_NUMBER,                // 
  TYPE_ASSIGN,                // =
  TYPE_PLUS,                  // +
  TYPE_MINUS,                 // -
  TYPE_MULT,                  // *
  TYPE_DIV,                   // /
  TYPE_MOD,                   // %
  TYPE_LPAR,                  // (
  TYPE_RPAR,                  // ) 

};
typedef enum TOKEN_TYPE token_type_t;

struct token {
  char *lexeme;
  token_type_t type;
}; 
typedef struct token token_t;

token_type_t lexeme2type(const char *lexeme);
void token_print(token_t *token);

#endif
