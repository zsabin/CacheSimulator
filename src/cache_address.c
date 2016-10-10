#include <stdlib.h>
#include "cache_address.h"

static unsigned int get_binary_subset(unsigned int value, int start_index, int size);

CacheAddress * get_cache_address(int S, int B, int m, unsigned int address) {
    int s = log_2(S);
    int b = log_2(B); 
    int t = m - (s + b);
    
    unsigned int tag = get_binary_subset(address, b + s, t);
    unsigned int set_index = get_binary_subset(address, b, s);
    unsigned int block_offset = get_binary_subset(address, 0, b);

    CacheAddress *cache_address = malloc(sizeof(CacheAddress));
    cache_address->tag = tag;
    cache_address->set_index = set_index;
    cache_address->block_offset = block_offset;
    
    return cache_address;
}

static unsigned int get_binary_subset(unsigned int value, int start_index, int size) {
    if (size == 0) return 0;
    unsigned int mask = (exp_2(size) - 1) << start_index;
    return (mask & value) >> start_index;
}

void destroy_cache_address(CacheAddress *cache_address) {
    free(cache_address);
}

