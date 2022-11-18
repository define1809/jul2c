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
  TYPE_PLUSPLUS,              // ++
  TYPE_MINUSMINUS,            // --
  TYPE_LPAR,                  // (
  TYPE_RPAR,                  // ) 
  TYPE_LSQR,                  // [
  TYPE_RSQR,                  // ]
  TYPE_COMMA,                 // ,     
  TYPE_OR,                    // keyword: or
  TYPE_AND,                   // keyword: and
  TYPE_NOT,                   // keyword: not
  TYPE_BITOR,                 // |
  TYPE_BITXOR,                // ^
  TYPE_BITAND,                // &
  TYPE_EQ,                    // ==
  TYPE_NEQ,                   // !=
  TYPE_LT,                    // <
  TYPE_LEQ,                   // <=
  TYPE_GT,                    // >
  TYPE_GEQ,                   // >=
  TYPE_SHL,                   // <<
  TYPE_SHR,                   // >>
  TYPE_FUNCTION,              // keyword: function
  TYPE_RETURN,                // keyword: return
  TYPE_PRINTLN,               // keyword: println
  TYPE_PRINT,                 // keyword: print
  TYPE_NEWLINE,               // keyword: newline
  TYPE_SPACE,                 // keyword: space
  TYPE_IF,                    // keyword: if
  TYPE_THEN,                  // keyword: then
  TYPE_ELSE,                  // keyword: else
  TYPE_ENDIF,                 // keyword: endif
  TYPE_WHILE,                 // keyword: while
  TYPE_ENDWHILE,              // keyword: endwhile
  TYPE_LOCAL,                 // keyword: local
  TYPE_GLOBAL,                // keyword: global
  TYPE_GOTO,                  // keyword: goto
  TYPE_LABEL,                 // IDENTIFIER:
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
