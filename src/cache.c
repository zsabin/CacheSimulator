#include <stdio.h>
#include <stdlib.h>
#include "replace_policy.h"
#include "cache.h"
#include "cache_address.h"

Cache * build_cache(FILE *stream, int max_access_count) {
    int S, E, B, m;
    ReplacePolicy replace_policy;
    fscanf(stream, "%d %d %d %d \n", &S, &E, &B, &m);

    char replace_policy_str[POLICY_STR_LENGTH];
    fgets(replace_policy_str, POLICY_STR_LENGTH, stream);
    replace_policy = str_to_replace_policy(replace_policy_str);
    
    Set **sets = malloc(S * sizeof(Set*));
    int i;
    for (i = 0; i < S; i++) {
        sets[i] = build_set(E, max_access_count);
    }
    
    Cache *cache = malloc(sizeof(Cache));       
    cache->S = S;
    cache->E = E;
    cache->B = B;
    cache->m = m;
    cache->replace_policy = replace_policy;
    cache->sets = sets;
    
    return cache;
}

RetrievalResult simulate_retrieval(Cache *cache, unsigned int address) {
    CacheAddress *cache_address = get_cache_address(cache->S, cache->B, 
            cache->m, address);
    Set *target_set = cache->sets[cache_address->set_index];
    RetrievalResult result = retrieve_line(target_set, cache_address, cache->replace_policy);
    destroy_cache_address(cache_address);
    return result;
}

void destroy_cache(Cache *cache) {
    int i;
    for (i = 0; i < cache->S; i++) {
        destroy_set(cache->sets[i]);
    }
    free(cache);
}