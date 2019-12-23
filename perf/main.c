#include "perf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdint.h>

#define DECL(fn) void fn();

PROGRAMS(DECL)

char function[30];

int64_t rand_64_bit();
void gen_rand_abm();
static void run(void (*func)(), int rounds);
static double gettime();
static void (*lookup(const char *fn))();

int main(int argc, char **argv) {
  if(argc!=3 && argc!=5){
    printf("arg should be --> perf [-r num] function\n");
    return -1;
  }
  if(strcmp(argv[1],"perf")!=0){
    printf("the first arg should be perf\n");
    return -1;
  }
  int rounds=1;
  if(argc==3){
    strcpy(function,argv[2]);
  }
  else{
    if(strcmp(argv[2],"-r")!=0){
      printf("arg 3 only can be -r now\n");
      return -1;
    }
    int num=atoi(argv[3]);
    if(num<=0){
      printf("rounds num should be number which > 0\n");
      return -1;
    }
    rounds=num;
    strcpy(function,argv[4]);
  }
  void (*func)() = lookup(function);
  run(func, rounds);
}

static double gettime() {
  int64_t current_time=clock();
  double return_time= current_time;
  return return_time;
}

static void (*lookup(const char *fn))() {
  #define PAIR(fn) { #fn, fn },
  struct pair {
    const char *name;
    void *ptr;
  };
  struct pair lut[] = {
    PROGRAMS(PAIR)
  };

  for (int i = 0; i < LENGTH(lut); i++) {
    struct pair *p = &lut[i];
    if (strcmp(fn, p->name) == 0) return p->ptr;
  }
  return print_error;
}

static void run(void (*func)(), int rounds) {
  
  double *elapsed = malloc(sizeof(uint64_t) * rounds);
  if (!elapsed) {
    perror("elapsed");
    return;
  }
  int is_multimod=0;
  if(strcmp(function,"multimod_p1")==0 ||\
     strcmp(function,"multimod_p2")==0 ||\
     strcmp(function,"multimod_p3")==0){
        is_multimod=1;
  }
  FILE* file =fopen("timedata","w");
  for (int round = 0; round < rounds; round++) {
    if(is_multimod){
      gen_rand_abm();
    }
    int64_t tempb = b;
    double st = gettime();
    func();
    double ed = gettime();
    elapsed[round] = ed - st;
    b=tempb;
    if(is_multimod){
      fprintf(file,"%f, %lld, %lld, %lld\n",elapsed[round],a,b,m);
    }
    else{
      fprintf(file,"%f\n",elapsed[round]);
    }
  }
  fclose(file);
  char command[100];
  sprintf(command,"python perform.py %s",function);
  system(command);
  system("rm timedata");
  free(elapsed);
}

int64_t rand_64_bit() {
  int a = rand();
  int b = rand();
  int c = rand();
  int d = rand();
  long long e = (long long)a*b;
  e = abs(e);
  long long f = (long long)c*d;
  f = abs(f);

  long long answer = (long long)e*f;

  return answer;
}

void gen_rand_abm(){
    srand((unsigned)clock());
    a=rand_64_bit();
    if(a<0){
      a=-a;
    }
    b=rand_64_bit();
    if(b<0){
      b=-b;
    }
    m=rand_64_bit();
    if(m<0){
      m=-m;
    }
}
