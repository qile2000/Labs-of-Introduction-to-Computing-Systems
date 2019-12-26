#include "common.h"
#include <inttypes.h>
#include <string.h>
#include <time.h>
//主存地址： 标记；cache组号；块内地址
//          13 ;    6    ;   6

// cache 缺失/写回的时候需要用到它们
// 从块号为`block_num`的内存地址中读出一整个cache块大小的内容到`buf`中
void mem_read(uintptr_t block_num, uint8_t *buf);

// 往块号为`block_num`的内存地址中写入一整个cache块大小的内容`buf`
void mem_write(uintptr_t block_num, const uint8_t *buf);

static uint64_t cycle_cnt = 0;

void cycle_increase(int n) { cycle_cnt += n; }

//是否有匹配的有效tag
uint32_t find_hit_tag(uintptr_t addr, uint32_t group_label, uint32_t mm_tag){
  for(int i=0; i<cache_lines_per_group; i++){
    if((mm_tag==whole_cache[group_label][i].tag_bit) &&
       (whole_cache[group_label][i].valid_bit==1)){
      return i;
    }
  }
  return -1;
}

//组内是否有空闲行
uint32_t find_empty(uintptr_t addr, uint32_t group_label){
  for (int i=0; i<cache_lines_per_group; i++){
		if (whole_cache[group_label][i].valid_bit==false) {
      return i;
		}
  }
  return -1;
}

//根据地址更新cacheline
uint32_t* update_cacheline(uintptr_t addr, uint32_t group_label, uint32_t line){
  uint32_t* ret_addr;
  whole_cache[group_label][line].valid_bit = true;
	whole_cache[group_label][line].tag_bit = addr >> (mm_group_label_bit+mm_block_addr_bit);
	whole_cache[group_label][line].block_label = (addr >> mm_block_addr_bit);
	mem_read(addr>>BLOCK_WIDTH,whole_cache[group_label][line].BLOCK);
	ret_addr = (void *)whole_cache[group_label][line].BLOCK +
             ((addr & (exp2(BLOCK_WIDTH)-1)) & ~0x3); 
  return ret_addr;
}

//随机替换
uint32_t* rand_replace_line(uintptr_t addr, uint32_t group_label, uint32_t line){
  //未被修改过，直接替换
  if (whole_cache[group_label][line].dirty_bit == false){
    return update_cacheline(addr, group_label, line);
  }
  //被修改过，先写回，再替换
  else{
    mem_write(whole_cache[group_label][line].block_label, whole_cache[group_label][line].BLOCK);
    whole_cache[group_label][line].dirty_bit = false;
    return update_cacheline(addr, group_label, line);
  }
}

// 从cache中读出`addr`地址处的4字节数据
// 若缺失, 需要先从内存中读入数据
uint32_t cache_read(uintptr_t addr) {
  //主存地址： 标记；cache组号；块内地址
  //          13 ;    6    ;   6
  uint32_t* ret_addr=NULL;

  //获得cache组号
  uint32_t cache_group_label= (addr>>mm_block_addr_bit)%mm_group_label_bit;

  //获得标记位
  uint32_t mm_tag = addr >> (mm_block_addr_bit+mm_group_label_bit);

  //匹配tag并检查有效位
  uint32_t find_hit_line = find_hit_tag(addr,cache_group_label,mm_tag);
  //命中
  if(find_hit_line>=0){
    ret_addr = (void *)whole_cache[cache_group_label][find_hit_line].BLOCK +
               ((addr & (exp2(BLOCK_WIDTH)-1)) & ~0x3);                ///////////////////////////
  }
  //未命中
  else{
    uint32_t find_empty_line = find_empty(addr, cache_group_label);
    //组中有空行
    if(find_empty_line>=0){
      ret_addr = update_cacheline(addr,cache_group_label,find_empty_line);   
    }
    //组中已满
    else{
      srand(clock());
      uint32_t rand_line = rand()%cache_lines_per_group;
      ret_addr = rand_replace_line(addr,cache_group_label,rand_line);
    }
  }
  return *ret_addr;
}

//往cache中写入数据
void write_data(uintptr_t addr, uint32_t group_label, uint32_t line, uint32_t data, uint32_t wmask){
  whole_cache[group_label][line].dirty_bit = true;
  uint32_t *write_addr = (void *)whole_cache[group_label][line].BLOCK + 
                         ((addr & (exp2(BLOCK_WIDTH)-1)) & ~0x3);   
	*write_addr = (*write_addr & ~wmask) | (data & wmask);
}

// 往cache中`addr`地址所属的块写入数据`data`, 写掩码为`wmask`
// 例如当`wmask`为`0xff`时, 只写入低8比特
// 若缺失, 需要从先内存中读入数据
void cache_write(uintptr_t addr, uint32_t data, uint32_t wmask) {
  uint32_t cache_group_label= (addr>>mm_block_addr_bit)%mm_group_label_bit;
  uint32_t mm_tag = addr >> (mm_block_addr_bit+mm_group_label_bit);
  uint32_t find_hit_line = find_hit_tag(addr,cache_group_label,mm_tag);
  //命中
  if(find_hit_line>=0){
    write_data(addr, cache_group_label, find_hit_line, data, wmask); 
  }
  //缺失
  else{
    uint32_t find_empty_line = find_empty(addr, cache_group_label);
    //组中有空行
    if(find_empty_line>=0){
      whole_cache[cache_group_label][find_empty_line].valid_bit = true;
	    whole_cache[cache_group_label][find_empty_line].tag_bit = addr >> (mm_group_label_bit+mm_block_addr_bit);
	    whole_cache[cache_group_label][find_empty_line].block_label = (addr >> mm_block_addr_bit);
	    mem_read(addr>>BLOCK_WIDTH,whole_cache[cache_group_label][find_empty_line].BLOCK); 
      write_data(addr, cache_group_label, find_empty_line, data, wmask); 
    }
    //组中已满
    else{
      srand(clock());
      uint32_t rand_line = rand()%cache_lines_per_group;
      uint32_t* temp = NULL;
      temp = rand_replace_line(addr,cache_group_label,rand_line);
      write_data(addr, cache_group_label, rand_line, data, wmask); 
    }
  }
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

  cache_lines_per_group = exp2(associativity_width);//每组的行数                  //4

  cache_group_num_width = total_size_width - associativity_width - BLOCK_WIDTH;  //6
  cache_group_num_bit = cache_group_num_width;//cache组号位                       //6
  cache_group_num = exp2(cache_group_num_width);//cache的组数

  cache_block_addr_bit = BLOCK_WIDTH;//cache的块内地址位数                  //6
  

  //主存空间1MB
  //MEM_SIZE = 组群数 × 每个组群的块数 × BLOCK_SIZE
  //主存地址： 标记；cache组号；块内地址
  mm_total_bit = 25; //主存地址位数
  block_total_num_width = mm_total_bit - BLOCK_WIDTH;                     //19
  block_total_num = exp2(block_total_num_width);//主存总块数

  cache_tag_bit = block_total_num_width-cache_group_num_bit;//cache标记位  //13

  mm_group_num_width = block_total_num_width - cache_group_num_width;     //13
  mm_group_num = exp2(mm_group_num_width);//主存组群数                      

  mm_group_label_bit = cache_group_num_width;//主存地址中组号位数      //6
  
  mm_block_addr_bit = BLOCK_WIDTH;//主存块内地址位数                         //6

  mm_tag_bit = mm_group_num_width;//主存标记位数                            //13

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
