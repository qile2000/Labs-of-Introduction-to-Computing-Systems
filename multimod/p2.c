#include "multimod.h"

int64_t multimod_p2(int64_t a, int64_t b, int64_t m) {

  int64_t result=0;

  if (a>=m) {
    a%=m;   
  }
  if (b>=m) {
    b%=m;  
  }

  if(m< ((int64_t)1<< 62)){
    while (b) {
      if (b&1) {
        result=(result+a)%m;
      }
      a=(a<<1)%m;
      b>>=1;
    }
  }

  else{
    while (b) {
      if (b&1)  {
        if(m-result>a){
          result+=a;
        }
        else{
          result+=a-m;
        }
      }   
      b >>= 1;
      if (b){
        if(m-a>a){
          a<<=1;
        }
        else{
          a=(a<<=1)-m;
        }
      }      
    }
  }
  
  return result;
}
