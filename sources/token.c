#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <token.h>

static bool is_identifier(const char *lexeme) {
  for (size_t i = 0; lexeme[i]; ++i) {
    if (!isalpha(lexeme[i]))
      return false;
  }
  return true;
}

static bool is_number(const char *lexeme) {
  for (size_t i = 0; lexeme[i]; ++i) {
    if (!isdigit(lexeme[i])) 
      return false;
  }
  return true;
}

token_type_t lexeme2type(const char *lexeme) {
  if (lexeme == NULL)
    return TYPE_UNDEFINED;
  size_t lexeme_len = strlen(lexeme);

  if (lexeme_len == 1) {
    switch (*lexeme) {
    case '=': return TYPE_ASSIGN;
    case '+': return TYPE_PLUS;
    case '*': return TYPE_MINUS;
    case '/': return TYPE_DIV;
    case '%': return TYPE_MOD;
    case '(': return TYPE_LPAR;
    case ')': return TYPE_RPAR;
    default : break;
    }
  } 
  if (is_identifier(lexeme))
    return TYPE_IDENTIFIER;
  if (is_number(lexeme))
    return TYPE_NUMBER;
  return TYPE_UNDEFINED;
}

static char *type2str(const token_type_t type) {
  switch (type) {
    case TYPE_UNDEFINED:  return "UNDEFINED";
    case TYPE_IDENTIFIER: return "IDENTIFIER";
    case TYPE_NUMBER:     return "NUMBER";
    case TYPE_ASSIGN:     return "ASSIGN";
    case TYPE_PLUS:       return "PLUS";
    case TYPE_MINUS:      return "MINUS";
    case TYPE_MULT:       return "MULT";
    case TYPE_DIV:        return "DIV";
    case TYPE_MOD:        return "MOD";
    case TYPE_LPAR:       return "LPAR";
    case TYPE_RPAR:       return "RPAR";
    default:              return "Unknown token type";
  } 
}

void token_print(token_t *token) {
  printf("[token] <%s :: %s>\n",
         type2str(token->type), token->lexeme);
}
