#ifndef __LEXER_H__
#define __LEXER_H__

#include <token.h>

struct token_list {
  token_t *token;
  struct token_list *next;
};
typedef struct token_list token_list_t;

token_list_t *token_list_push(token_list_t *head, token_t *token);
void token_list_print(token_list_t *head);
void token_list_free(token_list_t **head);
token_list_t *split(const char *code_jul);

#endif
