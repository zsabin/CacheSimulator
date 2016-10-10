#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "cache_simulator.h"

const char HIT_CHAR = 'H';
const char MISS_CHAR = 'M';

const int MAX_ACCESS_COUNT = 1000;

static void update_retrieval_stats(RetrievalResult result, int *hit_count, int *miss_count);

CacheSimulator * build_cache_simulator(FILE *stream) {
    Cache *cache;
    int hit_time, miss_penalty;
    
    cache = build_cache(stream, MAX_ACCESS_COUNT);
    fscanf(stream, "%d %d", &hit_time, &miss_penalty);
    
    CacheSimulator *cache_simulator = malloc(sizeof(CacheSimulator));
    cache_simulator->cache = cache;
    cache_simulator->hit_time = hit_time;
    cache_simulator->miss_penalty = miss_penalty;
    
    return cache_simulator;
}

void runCacheSimulation(CacheSimulator *cache_simulator, FILE *in_stream, FILE *out_stream) {
    int hit_count = 0;
    int miss_count = 0;
    unsigned int address;
    
    do {
        fscanf(in_stream, "%x", &address);
        if (address == -1) break;
        RetrievalResult result = simulate_retrieval(cache_simulator->cache, address);
        update_retrieval_stats(result, &hit_count, &miss_count);
        char char_result = result == HIT ? HIT_CHAR : MISS_CHAR;
        fprintf(out_stream, "%02x %c\n", address, char_result);
    } while (TRUE);
    
    int total_cycles = (hit_count + miss_count) * cache_simulator->hit_time 
        + miss_count * cache_simulator->miss_penalty;
    double miss_rate = (miss_count * 1.0 / (hit_count + miss_count)) * 100;
    fprintf(out_stream, "%d %d\n", (int)round(miss_rate), total_cycles);
}

//Updates the hit count and miss count based on the result
static void update_retrieval_stats(RetrievalResult result, int *hit_count, int *miss_count) {
    if (result == HIT) {
        *hit_count = *hit_count + 1;
    }
    else if (result == MISS) {
        *miss_count = *miss_count + 1;
    }
 }

void destroy_cache_simulator(CacheSimulator *cache_simulator) {
    destroy_cache(cache_simulator->cache);
    free(cache_simulator);
}

