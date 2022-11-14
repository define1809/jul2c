#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <lexer.h>

static bool is_jul(const char *filename) {
  size_t i = strlen(filename);
  return (filename[i - 4] == '.' && filename[i - 3] == 'j' &&
          filename[i - 2] == 'u' && filename[i - 1] == 'l');
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Not enought arguments.\n"); 
    return -1;
  }
  const char *filename = argv[1];
  if (!is_jul(filename)) {
    fprintf(stderr, ".jul file expected.\n");
    return -1;
  }
  FILE *file_jul = fopen(filename, "r");
  if (file_jul == NULL) {
    perror("fopen");
    return -1;
  }
  fseek(file_jul, 0, SEEK_END);
  size_t file_jul_size = ftell(file_jul);
  rewind(file_jul);
  char *code_jul = malloc((file_jul_size + 1) * sizeof(char));
  fread(code_jul, sizeof(char), file_jul_size, file_jul);   
  code_jul[file_jul_size] = '\0';
  fclose(file_jul);
  token_list_t *token_list = split(code_jul);
  free(code_jul);
  token_list_print(token_list);
  token_list_free(&token_list);
  return 0;
}
