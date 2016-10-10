#include "line.h"

Line * build_line(Line *prev_line, Line *next_line) {
    Line *line = malloc(sizeof(Line));
    line->valid = FALSE;
    line->access_count = 0;
    line->prev_line = prev_line;
    line->next_line = next_line;
    return line;
}

void update_line(Line *line, unsigned int tag) {
    line->valid = TRUE;
    line->tag = tag;
    line->access_count = 0;
}

void connect_lines(Line *parent, Line *child) {
    if (parent != NULL) {
        parent->next_line = child;
    }
    if (child != NULL) {
        child->prev_line = parent;  
    }
}

Boolean tag_matches_line(Line *line, unsigned int tag) {
    return line->valid && line->tag == tag;
}

Boolean access_line(Line *line) {
    if (line->valid) {
        line->access_count++;
        return TRUE;
    }
    return FALSE;
}

void destroy_line(Line *line) {
    free(line);
}

