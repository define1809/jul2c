#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <token.h>

static bool is_identifier(const char *lexeme) {
  for (size_t i = 0; lexeme[i]; ++i) {
    if (!((lexeme[i] >= 'a' && lexeme[i] <= 'z') ||
        (lexeme[i] >= 'A' && lexeme[i] <= 'Z')))
      return false;
  }
  return true;
}

static bool is_number(const char *lexeme) {
  for (size_t i = 0; lexeme[i]; ++i) {
    if (!((lexeme[i] >= '0' && lexeme[i] <= '9'))) 
      return false;
  }
  return true;
}

token_type_t lexeme2type(const char *lexeme) {
  if (lexeme == NULL)
    return TYPE_UNDEFINED;
  size_t lexeme_len = strlen(lexeme);

  if (lexeme_len == 1) {
    if (*lexeme == '=')
      return TYPE_ASSIGN;
    if (*lexeme == '+')
      return TYPE_PLUS;
    if (*lexeme == '-')
      return TYPE_MINUS;
    if (*lexeme == '*')
      return TYPE_MINUS;
    if (*lexeme == '\\')
      return TYPE_DIV;
    if (*lexeme == '%')
      return TYPE_MOD;
    if (*lexeme == '(')
      return TYPE_LPAR;
    if (*lexeme == ')')
      return TYPE_RPAR;
  } 
  if (is_identifier(lexeme))
    return TYPE_IDENTIFIER;
  if (is_number(lexeme))
    return TYPE_NUMBER;
  return TYPE_UNDEFINED;
}

void token_print(token_t *token) {
  printf("[token] <lexeme = %s ; type = %d>\n",
         token->lexeme, token->type);
}
