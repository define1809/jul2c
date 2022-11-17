#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <lexer.h>
#include <token.h>

static token_list_t *get_tail(token_list_t *head) {
  if (head == NULL)
    return NULL;
  while (head->next) {
    head = head->next;
  }  
  return head;
}

token_list_t *token_list_push(token_list_t *head, token_t *token) {
  token_list_t *new_tail = malloc(sizeof(token_list_t));
  new_tail->token = token;
  new_tail->next = NULL;
  if (head == NULL) 
    return new_tail;
  token_list_t *old_tail = get_tail(head);
  old_tail->next = new_tail;
  return head; 
}

void token_list_print(token_list_t *head) {
  while (head) {
    token_print(head->token);
    head = head->next; 
  }
}

void token_list_free(token_list_t **head) {
  if (*head == NULL)
    return;
  token_list_t *tmp = NULL, *I = NULL;
  for (I = *head; I; I = tmp) {
    tmp = I->next;
    if (I->token->lexeme != NULL)
      free(I->token->lexeme);
    free(I->token);
    free(I);
  }
  *head = NULL;
}

static bool is_space_symbol(const char ch) {
  return (ch == ' ' || ch == '\t' || ch == '\n' ||
          ch == '#' || ch == '\0');
}

static bool is_split_symbol(const char ch) {   
  return (is_space_symbol(ch)      ||
          ch == '+'  || ch == '-'  || ch == '*'  ||
          ch == '/'  || ch == '%'  || ch == '('  ||
          ch == ')'  || ch == '='  || ch == '['  ||
          ch == ']'  || ch == '>'  || ch == '<'  ||
          ch == '&'  || ch == '^'  || ch == '|');
}

token_list_t *split(const char *code_jul) {
  if (code_jul == NULL)
    return NULL;
  token_list_t *head = NULL;
  token_t *token = NULL;
  char *lexeme = NULL;
  size_t j = 2;
  for (size_t i = 0; code_jul[i]; ++i, ++j) {
    if (code_jul[i] == '#') {
      while (code_jul[i] && code_jul[i] != '\n')
        ++i;
    }
    if (is_split_symbol(code_jul[i])) {
      if (lexeme != NULL) {
        token = malloc(sizeof(token_t)); 
        token->lexeme = lexeme;
        token->type = lexeme2type(lexeme);
        head = token_list_push(head, token);
      }  
      if (!is_space_symbol(code_jul[i])) {
        token = malloc(sizeof(token_t)); 
        token->lexeme = NULL;
        char tmp_lexeme[2];
        tmp_lexeme[0] = code_jul[i];
        tmp_lexeme[1] = '\0'; 
        token->type = lexeme2type(tmp_lexeme);
        head = token_list_push(head, token);
      }
      j = 1;
      lexeme = NULL;
    } else {
      lexeme = realloc(lexeme, j * sizeof(char));
      lexeme[j - 2] = code_jul[i];
      lexeme[j - 1] = '\0';
    }
  } 
  return head;
} 
