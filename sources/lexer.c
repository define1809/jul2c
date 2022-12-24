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
          ch == '&'  || ch == '^'  || ch == '|'  ||
          ch == '!'  || ch == ','                  );
}

static bool is_2len_lex(char ch1, char ch2, token_type_t *token_type) {
  if (ch1 == '+' && ch2 == '+') {
    *token_type = TYPE_PLUSPLUS;
  } else if (ch1 == '-' && ch2 == '-') {
    *token_type = TYPE_MINUSMINUS;
  } else if (ch1 == '=' && ch2 == '=') {
    *token_type = TYPE_EQ;
  } else if (ch1 == '!' && ch2 == '=') {
    *token_type = TYPE_NEQ;
  } else if (ch1 == '<' && ch2 == '=') {
    *token_type = TYPE_LEQ;
  } else if (ch1 == '>' && ch2 == '=') {
    *token_type = TYPE_GEQ;
  } else if (ch1 == '<' && ch2 == '<') {
    *token_type = TYPE_SHL;
  } else if (ch1 == '>' && ch2 == '>') {
    *token_type = TYPE_SHR;
  }
  return *token_type != TYPE_UNDEFINED;
}

token_list_t *split(const char *code_jul) {
  if (code_jul == NULL)
    return NULL;
  bool is_2len_lex_flag = false;
  token_list_t *head = NULL;
  token_t *token = NULL;
  char *lexeme = NULL;
  token_type_t token_type = TYPE_UNDEFINED;
  for (size_t i = 0, j = 2; code_jul[i]; ++i, ++j) {
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
      if (is_2len_lex(code_jul[i], code_jul[i + 1], &token_type)) {
        token = malloc(sizeof(token_t));
        token->lexeme = NULL;
        token->type = token_type;
        head = token_list_push(head, token); 
        token_type = TYPE_UNDEFINED;
        i += 2;
        is_2len_lex_flag = true;
      }
      if (!is_space_symbol(code_jul[i]) && !is_2len_lex_flag) {
        token = malloc(sizeof(token_t)); 
        token->lexeme = NULL;
        char tmp_lexeme[2];
        tmp_lexeme[0] = code_jul[i];
        tmp_lexeme[1] = '\0'; 
        token->type = lexeme2type(tmp_lexeme);
        head = token_list_push(head, token);
      }
      if (is_2len_lex_flag) {
        is_2len_lex_flag = false;
        --i;
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
