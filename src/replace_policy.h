
#ifndef REPLACEPOLICY_H
#define REPLACEPOLICY_H

extern const int POLICY_STR_LENGTH;
/* LFU: Least-Frequently Used
 * LRU: Least-Recently Used
 */
typedef enum {NULL_POLICY, LFU, LRU} ReplacePolicy;

ReplacePolicy str_to_replace_policy(char* string);

char * replace_policy_to_str(ReplacePolicy policy);

#endif /* REPLACEPOLICY_H */

