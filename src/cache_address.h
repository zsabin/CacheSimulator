
#ifndef CACHE_ADDRESS_H
#define CACHE_ADDRESS_H

typedef struct CacheAddress CacheAddress;
struct CacheAddress {
    unsigned int set_index;
    unsigned int tag;
    unsigned int block_offset;
};
/* Parses a memory address into its set index, tag, and block offset components.
 * Returns a cache address struct that encapsulates these parameters.
 */
CacheAddress * get_cache_address(int S, int B, int m, unsigned int address);

void destroy_cache_address(CacheAddress *cache_address);

#endif /* CACHE_ADDRESS_H */

