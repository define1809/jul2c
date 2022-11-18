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

static token_type_t get_keyword(const char *lexeme, size_t lexeme_len) {
  switch (lexeme_len) {
  case 2:
    if (!strncmp(lexeme, "if", 2))
      return TYPE_IF;
    if (!strncmp(lexeme, "or", 2))
      return TYPE_OR;
    break;
  case 3:
    if (!strncmp(lexeme, "not", 3))
      return TYPE_NOT;
    if (!strncmp(lexeme, "and", 3))
      return TYPE_AND;
    break;
  case 4:
    if (!strncmp(lexeme, "then", 4))
      return TYPE_THEN;
    if (!strncmp(lexeme, "else", 4))
      return TYPE_ELSE;
    if (!strncmp(lexeme, "goto", 4))
      return TYPE_GOTO;
    break;
  case 5:
    if (!strncmp(lexeme, "print", 5))
      return TYPE_PRINT;
    if (!strncmp(lexeme, "endif", 5))
      return TYPE_ENDIF;
    if (!strncmp(lexeme, "while", 5))
      return TYPE_WHILE;
    if (!strncmp(lexeme, "local", 5))
      return TYPE_LOCAL; 
    if (!strncmp(lexeme, "space", 5))
      return TYPE_SPACE;
    break;
  case 6:
    if (!strncmp(lexeme, "return", 6))
      return TYPE_RETURN;
    if (!strncmp(lexeme, "global", 6))
      return TYPE_GLOBAL;
    break;
  case 7:
    if (!strncmp(lexeme, "println", 7))
      return TYPE_PRINTLN;
    if (!strncmp(lexeme, "newline", 7))
      return TYPE_NEWLINE;
    break;
  case 8:
    if (!strncmp(lexeme, "function", 8))
      return TYPE_FUNCTION;
    if (!strncmp(lexeme, "endwhile", 8))
      return TYPE_ENDWHILE;
    break;
  default: break;
  }
  if (lexeme[lexeme_len - 1] == ':')
    return TYPE_LABEL;
  return TYPE_IDENTIFIER;
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
    case '-': return TYPE_MINUS;
    case '*': return TYPE_MULT;
    case '/': return TYPE_DIV;
    case '%': return TYPE_MOD;
    case '(': return TYPE_LPAR;
    case ')': return TYPE_RPAR;
    case '[': return TYPE_LSQR;
    case ']': return TYPE_RSQR;
    case ',': return TYPE_COMMA;
    case '|': return TYPE_BITOR;
    case '^': return TYPE_BITXOR;
    case '&': return TYPE_BITAND;
    case '<': return TYPE_LT;
    case '>': return TYPE_GT; 
    default : break;
    }
  } 
  if (is_identifier(lexeme) || lexeme[lexeme_len - 1] == ':') {
    return get_keyword(lexeme, lexeme_len);
  }
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
    case TYPE_PLUSPLUS:   return "PLUSPLUS";
    case TYPE_MINUSMINUS: return "MINUSMINUS";
    case TYPE_LPAR:       return "LPAR";
    case TYPE_RPAR:       return "RPAR";
    case TYPE_LSQR:       return "LSQR";
    case TYPE_RSQR:       return "RSQR";
    case TYPE_COMMA:      return "COMMA";
    case TYPE_OR:         return "OR";
    case TYPE_AND:        return "AND";
    case TYPE_NOT:        return "NOT";
    case TYPE_BITOR:      return "BITOR";
    case TYPE_BITXOR:     return "BITXOR";
    case TYPE_BITAND:     return "BITAND";
    case TYPE_EQ:         return "EQ";
    case TYPE_NEQ:        return "NEQ";
    case TYPE_LT:         return "LT";
    case TYPE_LEQ:        return "LEQ";
    case TYPE_GT:         return "GT";
    case TYPE_GEQ:        return "GEQ";
    case TYPE_SHL:        return "SHL";
    case TYPE_SHR:        return "SHR";
    case TYPE_FUNCTION:   return "FUNCTION";
    case TYPE_RETURN:     return "RETURN";
    case TYPE_PRINTLN:    return "PRINTLN";
    case TYPE_PRINT:      return "PRINT";
    case TYPE_NEWLINE:    return "NEWLINE";
    case TYPE_SPACE:      return "SPACE";
    case TYPE_IF:         return "IF";
    case TYPE_THEN:       return "THEN";
    case TYPE_ELSE:       return "ELSE";
    case TYPE_ENDIF:      return "ENDIF";
    case TYPE_WHILE:      return "WHILE";
    case TYPE_ENDWHILE:   return "ENDWHILE";
    case TYPE_LOCAL:      return "LOCAL";
    case TYPE_GLOBAL:     return "GLOBAL";
    case TYPE_GOTO:       return "GOTO";
    case TYPE_LABEL:      return "LABEL";  
    default:              return "Unknown token type";
  } 
}

void token_print(token_t *token) {
  printf("[token] <%s :: %s>\n",
         type2str(token->type), token->lexeme);
}
