#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define exp2(x) (1 << (x))
#define mask_with_len(x) (exp2(x) - 1)

#define MEM_SIZE (1 << 25) // 1MB
#define BLOCK_WIDTH  6     // 64B
#define BLOCK_SIZE exp2(BLOCK_WIDTH)

#define TOTAL_SIZE_WIDTH 20
#define ASSOCIATIVITY_WIDTH 2

//命中数量
uint32_t hit_num;

//cache数据区容量：
//2^total_size_width = (2^6)BLOCK_SIZE(64)字/行 × 2^associativity 行/组 × group_num 组数
uint32_t B_per_line;//每行字节数

uint32_t cache_datazone_size;//cache数据容量

uint32_t cache_lines_per_group;//每组的行数

uint32_t cache_group_num_width;
uint32_t cache_group_num;//cache的组数     
uint32_t cache_group_num_bit;//cache组号位

uint32_t cache_block_addr_bit;//cache的块内地址位数    

uint32_t cache_tag_bit;//cache的标记位

//主存空间1MB
//MEM_SIZE = 组群数 × 每个组群的块数 × BLOCK_SIZE
uint32_t mm_total_bit; //主存地址位数

uint32_t block_total_num_width;
uint32_t block_total_num;//主存总块数

uint32_t mm_group_num_width;
uint32_t mm_group_num;//主存组群数

uint32_t mm_group_label_bit;//主存地址中组号位数

uint32_t mm_block_addr_bit;//主存块内地址位数

uint32_t mm_tag_bit;//主存标记位数

typedef uint8_t bool;
#define true 1
#define false 0

typedef struct{
  bool valid_bit;           //有效位
  bool dirty_bit;           //脏位
  uint32_t tag_bit;         //标记位
  uint32_t block_label;     //块号
  uint8_t BLOCK[BLOCK_SIZE];//块大小为 64B 
} cache_row;

cache_row whole_cache[exp2(TOTAL_SIZE_WIDTH-ASSOCIATIVITY_WIDTH-BLOCK_WIDTH)][exp2(ASSOCIATIVITY_WIDTH)];

void cycle_increase(int n);

#endif
