#include "multimod.h"

int64_t multimod_p2(int64_t a, int64_t b, int64_t m) {
   // TODO: implement
  int64_t ret = 0;
  a %= m;
  b %= m;
  
  while (b) {
    if (b & 1) {
      ret = (ret + a) % m;
    }
    a = a*2%m;
    b >>= 1;
  }
  return ret;
}
