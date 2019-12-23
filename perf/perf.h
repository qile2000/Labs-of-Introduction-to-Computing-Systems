#include <stdint.h>
#include <stdlib.h>

#define PROGRAMS(_) \
  _(dummy) \
  _(print_hello) \
  _(print_error) \
  _(simple_loop) \
  _(multimod_p1) \
  _(multimod_p2) \
  _(multimod_p3) 

int64_t a;
int64_t b;
int64_t m;

#define LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

