#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache_simulator.h"

int main(int argc, char *argv[]) {
    CacheSimulator *cacheSimulator = build_cache_simulator(stdin);
    runCacheSimulation(cacheSimulator, stdin, stdout);
    destroy_cache_simulator(cacheSimulator);
    return (EXIT_SUCCESS);
}