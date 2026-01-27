#include <stdio.h>
#include <stdlib.h>
#include <klee/klee.h>

void to_upper(char *text, int n) {
  for (int i = 0; i < n; i++) {
    #ifdef MERGE
    klee_open_merge();
    #endif
    if ((text[i] >= 'a') & (text[i] <= 'z')) {
      text[i] = text[i] - 'a' + 'A';
    }
    #ifdef MERGE
    klee_close_merge();
    #endif
  }
}

// void to_upper_dead_code(char *text, int n) {
//   for (int i = 0; i < n; i++) {
//     int t1, t2, t3, t4, t5, t6;
//     #ifdef MERGE
//     klee_open_merge();
//     #endif
//     if ((text[i] >= 'a') & (text[i] <= 'z')) {
//       t1 = text[i] - 'a';
//       t2 = t1 + 'A';
//       t3 = text[i];
//       text[i] = t2;
//     }
//     else {
//       t4 = text[i] - 0;
//       t5 = t4 + 0;
//       t6 = text[i];
//       text[i] = t6;
//     }
//     #ifdef MERGE
//     klee_close_merge();
//     #endif
//   }
// }

// void to_upper_final(char *text, int n) {
//   for (int i = 0; i < n; i++) {
//     int s1, t1_t4, s2, t2_t5, t3_t6, s3;
//     #ifdef MERGE
//     klee_open_merge();
//     #endif
//     unsigned is_lower = (text[i] >= 'a') & (text[i] <= 'z');
//     s1    = is_lower == 0 ? 0 : 'a'; // select
//     t1_t4 = text[i] - s1;
//     s2    = is_lower == 0 ? 0 : 'A'; // select
//     t2_t5 = t1_t4 + s2;
//     t3_t6 = text[i];
//     s3    = is_lower == 0 ? t3_t6 : t2_t5; // select
//     text[i] = s3;
//     #ifdef MERGE
//     klee_close_merge();
//     #endif
//   }
// }

int main() {
  int n = SIZE;
  char *text = (char*)malloc(n*sizeof(char));

  klee_make_symbolic(text, n*sizeof(char), "text");

  to_upper(text, n);

#ifdef VERIFY
  // to_upper_final(text, n);
  for (int i = 0; i < n; i++)
    klee_assert(!((text[i] >= 'a') & (text[i] <= 'z')));
  printf("verified\n");
#endif // VERIFY

  return 0;
}
