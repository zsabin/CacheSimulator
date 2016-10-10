
#ifndef LINE_H
#define LINE_H

#include "util.h"

typedef struct Line Line;
struct Line {
    Boolean valid;
    unsigned int tag;
    int access_count;
    Line *next_line;
    Line *prev_line;
};

Line * build_line();

/* Provides the specified parent and child lines with pointers to one another,
 * connecting them into a linked list.
 */
void connect_lines(Line *parent, Line *child);

/* Returns true if the specified line is valid and has a tag that matches the
 * specified tag
 */
Boolean tag_matches_line(Line *line, unsigned int tag);

/* Updates the line with the specified tag. Additionally, resets the valid and 
 * access count parameters of the line
 */
void update_line(Line *line, unsigned int tag);

/* Attempt to access the current line to simulate a retrieval of data from the 
 line. Returns a boolean representing the result of the attempt.
 */
Boolean access_line(Line *line);

void destroy_line(Line *line);

#endif /* LINE_H */

