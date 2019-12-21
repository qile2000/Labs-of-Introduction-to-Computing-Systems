#include "asm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

static void setjmp_test0();
static void setjmp_test1();

int main() {
  // TODO: add more tests here!
  assert(asm_add(1, 2) == 3);
  assert(asm_add(123,456)== 579);
  assert(asm_popcnt(0b1111111111000000000011111000000000000000111111111100000000001111) == 29);
  assert(asm_popcnt(0xfffffffffffffff0ull) == 60);
  assert(asm_popcnt(0xffffffffffffffffull) == 64);
  printf("YEAH, PASS TEST ADD and POPCNT!\n");

  char _src[10]="123456789";
	char _dst[20]="0";
	printf("%s\n", _dst);
  assert(asm_memcpy(_dst, _src, 10) == _dst);
	printf("%s\n", _dst);
  // TODO: add memcpy tests here!
  char* src="The first NJU!!!";
  char dest1[30];
  char dest2[30];
  asm_memcpy(dest1,src+10,3);
  asm_memcpy(dest2,src,9);
  dest1[3]='\0';
  dest2[9]='\0';
  char* test1="NJU";
  char* test2="The first";
  assert(strcmp(dest1,test1)==0);
  assert(strcmp(dest2,test2)==0);
  printf("%s\n",dest2);
  printf("%s\n",dest1);
  printf("%s\n",src);
  assert(asm_memcpy(NULL, NULL, 0) == NULL);
  printf("YEAH, PASS TEST MEMCPY!\n");
  
  // setjmp test starts here
  setjmp_test0();
  setjmp_test1();
  printf("YEAH, FINISH THE TEST!\n");
}

struct log_entry {
  const char *str;
  int value;
};
static asm_jmp_buf bufferA, bufferB;
static struct log_entry expected[] = {
  // expected output sequence for setjmp tests
  { "A", 0 },
  { "B", 999 },
  { "A1", 0 },
  { "B1", 0 },
  { "A2", 10001 },
  { "B2", 20001 },
  { "A3", 10002 },
  { "B3", 20002 },
  { "A4", 10003 },
  { NULL, 0 },
};
static struct log_entry *head = expected;

static void setjmp_log(const char *str, int value) {
  assert(head->str != NULL);
  assert(strcmp(head->str, str) == 0);
  assert(head->value == value);
  head++;
}

static void setjmp_test2();
static void setjmp_test1() {
  int r = 0;
  setjmp_log("A1", r);
  if ((r = asm_setjmp(bufferA)) == 0) {
    setjmp_test2();
  }
  setjmp_log("A2", r);
  if ((r = asm_setjmp(bufferA)) == 0) {
    asm_longjmp(bufferB, 20001);
  }
  setjmp_log("A3", r);
  if ((r = asm_setjmp(bufferA)) == 0) {
    asm_longjmp(bufferB, 20002);
  }
  setjmp_log("A4", r);
  assert(head->str == NULL);
  printf("YEAH, PASS JMP TEST1!\n");
}

static void setjmp_test2() {
  int r = 0;
  setjmp_log("B1", r);
  if ((r = asm_setjmp(bufferB)) == 0) {
    asm_longjmp(bufferA, 10001);
  }
  setjmp_log("B2", r);
  if ((r = asm_setjmp(bufferB)) == 0) {
    asm_longjmp(bufferA, 10002);
  }
  setjmp_log("B3", r);
  if ((r = asm_setjmp(bufferB)) == 0) {
    asm_longjmp(bufferA, 10003);
  }
}

static asm_jmp_buf buf;

static void setjmp_test_simple() {
  asm_longjmp(buf, 999);
}

static void setjmp_test0() {
  int r;
  if ((r = asm_setjmp(buf)) == 0) {
    setjmp_log("A", r);
    setjmp_test_simple();
  }
  setjmp_log("B", r);
  printf("YEAH, PASS JMP TEST0!\n");
}
