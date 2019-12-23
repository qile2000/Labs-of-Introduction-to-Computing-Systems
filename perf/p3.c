#include "perf.h"
#include <stdint.h>

int64_t multimod_p3() {
  int64_t t = (a * b - (int64_t)((double)a * b / m) * m) % m;
  return t < 0 ? t + m : t;
}
