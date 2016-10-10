#include <stdlib.h>
#include "set.h"

static Boolean line_match_found(Line *line, unsigned int tag);
static void update_LFU(Line **LFU_line, Line *current_line);
static void move_line_to_head(Set *set, Line *line);

Set * build_set(int size, int max_access_count) {
    Line *first_line, *line;
    first_line = line = build_line();
    first_line->prev_line = NULL;
    int i;
    for (i = 1; i < size; i++) {
        line->next_line = build_line();
        line->next_line->prev_line = line;
        line = line->next_line;
    }
    line->next_line = NULL;
    
    Set *set = malloc(sizeof(Set));
    set->size = size;
    set->access_count = 0;
    set->max_access_count = max_access_count;
    set->MRU_line = first_line;
    return set;
}

RetrievalResult retrieve_line(Set *set, CacheAddress *cache_address, 
        ReplacePolicy replace_policy) {
    RetrievalResult result = HIT;
    Line *line;
    if (set->access_count == set->max_access_count) {
        reset_access_count(set);
    }
    if (!find_line(set, &line, cache_address->tag, replace_policy)) {
        update_line(line, cache_address->tag);
        result = MISS;
    }   
    move_line_to_head(set, line);
    access_line(line);
    set->access_count++;
    return result;
}

Boolean find_line(Set *set, Line **line, unsigned int tag, 
        ReplacePolicy replace_policy) {
    Line *LRU_line = NULL;
    Line *LFU_line = NULL;
    Line *next_available_line = NULL;
    *line = set->MRU_line;
    while (*line != NULL) {
        if (tag_matches_line(*line, tag)) {
            return TRUE;
        }
        if (!(*line)->valid) {
            next_available_line = *line;
        }
        LRU_line = *line;
        update_LFU(&LFU_line, *line);
        *line = (*line)->next_line;
    }
    *line = next_available_line != NULL ? next_available_line : 
        replace_policy == LFU ? LFU_line : LRU_line;

    return FALSE;
}

static void update_LFU(Line **LFU_line, Line *line) {
    if (line->valid) {
        if (*LFU_line == NULL || line->access_count <= (*LFU_line)->access_count) {
            *LFU_line = line;
        }
    }
}

static void move_line_to_head(Set *set, Line *line) {
   if (set->MRU_line != line) {
       connect_lines(line->prev_line, line->next_line);
       connect_lines(line, set->MRU_line);
       line->prev_line = NULL;
       set->MRU_line = line;
    } 
}

void reset_access_count(Set *set) {
    set->access_count = 0;
    Line *line = set->MRU_line;
    while (line != NULL) {
        line->access_count = 0;
        line = line->next_line;
    }
}

void destroy_set(Set *set) {
    Line *line = set->MRU_line;
    while (line != NULL) {
        destroy_line(line);
        line = line->next_line;
    }
    free(set);
}