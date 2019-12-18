#include "multimod.h"

int64_t multimod_p1(int64_t a, int64_t b, int64_t m) {
  
  int64_t result=0;
  
  if(b>a){
    int64_t temp = a;
    a = b;
    b = temp;
  }

  for(int64_t i = 0; i<b; i++){
    result=(result+a%m)%m;
  }

  return result;
}
