#include "multimod.h"

int64_t multimod_p1(int64_t a, int64_t b, int64_t m) {
  
  int64_t ret = 0;
  
  __int128 alarge=(__int128)a;
  __int128 blarge=(__int128)b;

  while(blarge) {

    if(blarge&1){
      ret = (ret + alarge) % m;
    }

    alarge<<= 1;
    alarge=alarge% m;
    blarge>>= 1;
  }
  return ret;
  
}
