
#ifndef SET_H
#define SET_H

#include "replace_policy.h"
#include "cache_address.h"
#include "line.h"

typedef enum {HIT, MISS} RetrievalResult;

typedef struct Set Set;
struct Set {
    int size;
    int next_available_line;
    int access_count;
    int max_access_count;
    Line *MRU_line;
};

/* Builds a set where size is the number of lines in the set and max access 
 * count is the total number of times a set can be accessed before the access 
 * counts for each line are reset
 */
Set * build_set(int size, int max_access_count);

/* Simulates an attempt to access a block of data from the specified set with the
 * tag that matches that of the specified cache address. Returns the result of the 
 * attempted retrieval: a HIT if the address was found in the set or a MISS otherwise
 */ 
RetrievalResult retrieve_line(Set *set, CacheAddress *cache_address, 
        ReplacePolicy replace_policy);

/* Attempts to find a valid line with the specified tag within the set. Sets the 
 * parameter line to be a pointer to the located line if it was found or to the
 * the next line to write to based on the specified replacement policy. If the 
 * replacement policy is LFU then ties for the least frequently used line goes 
 * to the line that was accessed the least recently. 
 * Returns true if the line was found and false if it was not.
 */
Boolean find_line(Set *set, Line **line, unsigned int tag, 
        ReplacePolicy replace_policy);

/* Resets the access counts of this set and of each of the lines within this 
 * set.
 */
void reset_access_count(Set *set);

void destroy_set(Set *set);

#endif /* SET_H */

