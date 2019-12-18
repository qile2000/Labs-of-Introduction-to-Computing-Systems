#include "multimod.h"

int64_t multimod_p1(int64_t a, int64_t b, int64_t m) {
  int64_t ans = ((__int128)(a * b) % m);
  return ans;
}
