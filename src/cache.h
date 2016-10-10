#ifndef CACHE_H
#define CACHE_H

#include "util.h"
#include "replace_policy.h"
#include "set.h"

typedef struct Cache Cache;
/* S: The number of sets in the cache
 * E: The number of lines in each set
 * B: The number of bytes per block
 * m: The word size
 * replace_policy: Either LFU or LRU
 */
struct Cache {
    int S;
    int E;
    int B;
    int m;
    ReplacePolicy replace_policy;
    Set **sets;
};

/* Reads in the cache parameters from the specified input stream and builds a
 * cache. Max access count is the total number of times a set can be accessed
 * before the access counts for each line are reset
 */
Cache * build_cache(FILE *stream, int max_access_count);

/* Attempts to read the specified address from the cache. Returns the result
 * of the attempt: either a HIT or a MISS
 */
RetrievalResult simulate_retrieval(Cache *cache, uint address);

void destroy_cache(Cache * cache);

#endif /* CACHE_H */

