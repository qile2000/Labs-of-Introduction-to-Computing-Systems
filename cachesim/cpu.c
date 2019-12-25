#include "common.h"

#define addr_offset_bit(addr) (((addr) & 0x3) * 8)

//一套 CPU 接口 cpu_read() 和 cpu_write(), 
//会调用你实现的 cache_read() 和 cache_write(). 
//uncache 的接口 cpu_uncache_read() 和 cpu_uncache_write(), 
//用于直接访问另一个独立的内存. 这样是为了对实现进行对比测试


uint32_t cache_read(uintptr_t addr);
void cache_write(uintptr_t addr, uint32_t data, uint32_t wmask);
uint32_t mem_uncache_read(uintptr_t addr);
void mem_uncache_write(uintptr_t addr, uint32_t data, uint32_t wmask);

const uint32_t len2datamask [] = { 0x0, 0xff, 0xffff, 0xffffff, 0xffffffff };

uint32_t cpu_read(uintptr_t addr, int len) {
  cycle_increase(1);
  return (cache_read(addr) >> addr_offset_bit(addr)) & len2datamask[len];
}

void cpu_write(uintptr_t addr, int len, uint32_t data) {
  cycle_increase(1);
  cache_write(addr, data << addr_offset_bit(addr), len2datamask[len] << addr_offset_bit(addr));
}

uint32_t cpu_uncache_read(uintptr_t addr, int len) {
  return (mem_uncache_read(addr) >> addr_offset_bit(addr)) & len2datamask[len];
}

void cpu_uncache_write(uintptr_t addr, int len, uint32_t data) {
  mem_uncache_write(addr, data << addr_offset_bit(addr), len2datamask[len] << addr_offset_bit(addr));
}
