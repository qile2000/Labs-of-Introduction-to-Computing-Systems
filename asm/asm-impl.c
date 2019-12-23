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
0	  %rbx  
8 	pc
16	%r12              (10)
24	%r13              (18)
32	%r14              (20)
40	%r15              (28)
48  %rsp              (30)
56  %rbp
*/
int asm_setjmp(asm_jmp_buf env) {
  int val;
  asm volatile(
    "movq    %%rbx,      0(%%rdi)\n"     

    "movq    8(%%rsp),   %%rdx\n"
    "movq    %%rdx,      8(%%rdi)\n"    //pc

    "movq    %%r12,      16(%%rdi)\n"
    "movq    %%r13,      24(%%rdi)\n"
    "movq    %%r14,      32(%%rdi)\n"
    "movq    %%r15,      40(%%rdi)\n"

    "lea     0x10(%%rsp),%%rdx\n"       //rsp
    "movq    %%rdx,      48(%%rdi)\n"

    "movq    0(%%rsp),   %%rdx\n"       
    "movq    %%rdx,      56(%%rdi)\n"   //rbp

    "mov     $0,         %0\n"          // 置0返回
    :"=r"(val)
    :
    :"memory"
  );
  return val;
}
/*
0	  %rbx  数据存储
8 	pc
16	%r12 \            
24	%r13  \  数据存储  
32	%r14  /           
40	%r15 /            
48  %rsp              
56  %rbp
*/
void asm_longjmp(asm_jmp_buf env, int val) {
  asm volatile(
    "movq    (%%rdi),    %%rbx\n"
    "movq    16(%%rdi),  %%r12\n"
    "movq    24(%%rdi),  %%r13\n"
    "movq    32(%%rdi),  %%r14\n"
    "movq    40(%%rdi),  %%r15\n"
    "movq    48(%%rdi),  %%rsp\n"    

    "movq    56(%%rdi),  %%rbp\n"

    "movl    %%esi,      %%eax\n"
    
    "jmpq    *8(%%rdi)\n"           //存的pc
    :
    :
    :"memory"
  );
}
