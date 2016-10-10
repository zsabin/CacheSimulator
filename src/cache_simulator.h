#ifndef CACHE_SIMULATOR_H
#define CACHE_SIMULATOR_H

#include "cache.h"

typedef struct CacheSimulator CacheSimulator;

struct CacheSimulator {
    Cache *cache;
    int hit_time;
    int miss_penalty;
};

/* Reads in the cache simulator parameters from the specified input stream and
 * builds a cache simulator. Returns a pointer to the cache simulator
 */
CacheSimulator * build_cache_simulator(FILE *stream);

/* Runs a cache access simulation. It reads addresses from the specified input
 * stream and attempts to retrieve them from the cache simulator's cache. It will
 * then print the results of the retrievals to the specified output stream. It
 * will continue to read in addresses until it receives a -1. At that point it 
 * will print out the miss rate and the duration of the simulation in clock cycles
 * based on the hit time and miss penalty of the cache simulator
 */
void runCacheSimulation(CacheSimulator *cache_simulator, FILE *in_stream, FILE *out_stream);

void destroy_cache_simulator(CacheSimulator *cache_simulator);

#endif /* CACHE_SIMULATOR_H */

