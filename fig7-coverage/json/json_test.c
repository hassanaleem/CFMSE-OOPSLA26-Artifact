
#include "json.h"

int main(int argc, char **argv) {

  char json_string[20];
  klee_make_symbolic(json_string, 20, "arr");
  klee_assume(json_string[19] == '\0');

  struct json_value_s *root = json_parse(json_string, 19);

  if (root == 0) {
    printf("parsing error!!\n");
  } else {
    printf("success!!\n");
  }

  return 0;
}
