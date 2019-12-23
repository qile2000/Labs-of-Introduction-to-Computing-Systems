#include <stdint.h>
#include "perf.h"
#include <stdio.h>
int64_t multimod_p1() {
  printf("multimod_p1's runtime is very large, please don't wait\n");
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
