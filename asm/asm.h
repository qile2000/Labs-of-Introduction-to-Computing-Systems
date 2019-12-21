#include <stdint.h>
#include <unistd.h>

// TODO: set correct array length
typedef uintptr_t asm_jmp_buf[64];
/*
0	%rbx  数据存储
8 	%rbp \
16	%r12  \
24	%r13    数据存储
32	%r14  /
40	%r15 /
48  %rsp  栈指针寄存器
56  pc    返回地址
*/
int64_t asm_add(int64_t a, int64_t b);
int asm_popcnt(uint64_t x);
void *asm_memcpy(void *dest, const void *src, size_t n);
int asm_setjmp(asm_jmp_buf env);
void asm_longjmp(asm_jmp_buf env, int val);
