#include "common.h"
#include <inttypes.h>
//主存地址： 标记；cache组号；块内地址


// cache 缺失/写回的时候需要用到它们
// 从块号为`block_num`的内存地址中读出一整个cache块大小的内容到`buf`中
void mem_read(uintptr_t block_num, uint8_t *buf);

// 往块号为`block_num`的内存地址中写入一整个cache块大小的内容`buf`
void mem_write(uintptr_t block_num, const uint8_t *buf);

static uint64_t cycle_cnt = 0;

void cycle_increase(int n) { cycle_cnt += n; }

// 从cache中读出`addr`地址处的4字节数据
// 若缺失, 需要先从内存中读入数据
uint32_t cache_read(uintptr_t addr) {
  //匹配tag并检查有效位
  if(find_tag(addr)){
    read_cache(addr);
  }
  else{
    if(group_exist_emptyrow(addr)){
      mem_read();
      read_cache(addr);
    }
    else{
      random_replace();
      read_cache();
    }
  }
  return 0;
}

// 往cache中`addr`地址所属的块写入数据`data`, 写掩码为`wmask`
// 例如当`wmask`为`0xff`时, 只写入低8比特
// 若缺失, 需要从先内存中读入数据
void cache_write(uintptr_t addr, uint32_t data, uint32_t wmask) {
}

// 初始化一个数据大小为`2^total_size_width`B, 关联度（主存块对应的cache行的个数，*路组相联）
// 为`2^associativity_width`的cache
// 例如`init_cache(14, 2)`将初始化一个16KB, 4路组相联的cache
// 将所有valid bit置为无效即可
void init_cache(int total_size_width, int associativity_width) {
  //cache数据区容量：
  //2^total_size_width = (2^6)BLOCK_SIZE(64)字/行 × 2^associativity 行/组 × group_num 组数
  B_per_line = BLOCK_SIZE;//每行字节数

  cache_datazone_size = exp2(total_size_width);//cache数据容量

  cache_lines_per_group = exp2(associativity_width);//每组的行数

  cache_group_num_width = total_size_width - associativity_width - BLOCK_WIDTH;
  cache_group_num = exp2(cache_group_num_width);//cache的组数

  //主存空间1MB
  //MEM_SIZE = 组群数 × 每个组群的块数 × BLOCK_SIZE
  mm_total_bit = 25; //主存地址位数
  block_total_num_width = mm_total_bit - BLOCK_WIDTH;
  block_total_num = exp2(block_total_num_width);//主存总块数

  mm_group_num_width = block_total_num_width - cache_group_num_width;
  mm_group_num = exp2(mm_group_num_width);//主存组群数

  mm_group_group_label_bit = cache_group_num_width;//主存地址中组号位数
  
  mm_block_addr_bit = BLOCK_WIDTH;//主存块内地址位数

  mm_tag_bit = mm_group_num_width;//主存标记位数

  for(int i=0; i<cache_group_num; i++){
    for(int j=0; j<cache_lines_per_group; j++){
      memset(whole_cache[i][j].BLOCK, 0, sizeof(whole_cache[i][j].BLOCK));
      whole_cache[i][j].valid_bit=false;
      whole_cache[i][j].dirty_bit=false;
      whole_cache[i][j].tag_bit=0;
      whole_cache[i][j].block_label=0;
    }
  }
}

void display_statistic(void) {
}
