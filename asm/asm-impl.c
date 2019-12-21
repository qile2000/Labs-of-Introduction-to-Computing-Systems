#include "asm.h"
#include <string.h>
#include <stdio.h>

int64_t asm_add(int64_t a, int64_t b) {
  int64_t result;
  asm volatile(
      "addq %1,  %2\n"    //b=a+b
			"movq %2,  %0\n"    //result=b
			:"=r"(result)
			:"r"(a), "r"(b)
			);
  return result;
}

int asm_popcnt(uint64_t n) {
  /*
  int num=0;
  for(;n;num++){
    n&=(n-1);
  }
  return num;
  */
  int num;
  asm volatile(
      "movl     $0x0,     %0\n"           //num = 0
      "jmp      .L_cmp\n"                 //goto L_cmp
      ".L_loop: mov %1,   %%rax\n"        //L_loop: rax=n
      "sub      $0x1,     %%rax\n"        //rax--
      "and      %%rax,    %1\n"           //n=n&rax
      "addl     $0x1,     %0\n"           //num+++
      ".L_cmp:  test  %1, %1\n"           //L_cmp: if(n!=0) goto L_loop 
      "jnz      .L_loop\n"
      :"=c"(num)
      :"r"(n)
      :"rax"
      );
  return num;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
  asm volatile(
      ".L_n_ZERO: test %2,  %2\n"
		  "je         .L_ret\n"
		  "mov        (%1),     %%rdx\n"
		  "mov        %%rdx,    (%0)\n"
		  "inc        %0\n"
		  "inc        %1\n"
		  "dec        %2\n"
		  "jmp        .L_n_ZERO\n"
		  ".L_ret:\n"
			:
			:"r"(dest), "r"(src), "r"(n)
			:"memory","rdx"
			);
  return dest;
}

/*
0	  %rbx  数据存储
8 	%rbp \            (8)
16	%r12  \           (10)
24	%r13    数据存储   (18)
32	%r14  /           (20)
40	%r15 /            (28)
48  %rsp              (30)
56  pc  返回地址       (38)
*/
int asm_setjmp(asm_jmp_buf env) {
  int val;
  asm volatile(
    "movq    %%rbx,     0(%%rdi)\n"     //将rbx, rbp, r12, r13, r14. r15, rsp放进env
    "movq    %%rbp,     8(%%rdi)\n"
    "movq    %%r12,     16(%%rdi)\n"
    "movq    %%r13,     24(%%rdi)\n"
    "movq    %%r14,     32(%%rdi)\n"
    "movq    %%r15,     40(%%rdi)\n"
    "movq    %%rsp,     48(%%rdi)\n" 

    "movq    0(%%rsp),   %%rdx\n"       // rdx暂时存放, 把返回地址（%rsp)放进env保存
    "movq    %%rdx,     56(%%rdi)\n" 

    "mov    $0,     %0\n"               // 置0返回
    :"=r"(val)
    :
    :"memory"
  );
  return val;
}

void asm_longjmp(asm_jmp_buf env, int val) {
  asm volatile(
    "movq    (%%rdi),    %%rbx\n"
    "movq    8(%%rdi),   %%rbp\n"
    "movq    16(%%rdi),  %%r12\n"
    "movq    24(%%rdi),  %%r13\n"
    "movq    32(%%rdi),  %%r14\n"
    "movq    40(%%rdi),  %%r15\n"
    "movq    48(%%rdi),  %%rsp\n"    

    "movq    56(%%rdi),  %%rdx\n"    //rdx暂时存放之前保存的返回地址（%rsp)
    "movq    %%rdx,      (%%rsp)\n"
    
    "movl    %%esi,      %%eax\n"
    "testl   %%eax,      %%eax\n"    // cannot be 0
    "jnz     .L\n"
    "movl    $1,         %%eax\n"
    ".L:     ret\n"
    :
    :
    :"memory"
  );
}
