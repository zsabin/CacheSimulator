#include <string.h>
#include "replace_policy.h"

const int POLICY_STR_LENGTH = 4;
static const char LFU_STRING[4] = "LFU";
static const char LRU_STRING[4] = "LRU";

ReplacePolicy str_to_replace_policy(char *string) {
    if (!strcmp(string, LFU_STRING)) {
        return LFU;
    }
    else if (!strcmp(string, LRU_STRING)) {
        return LRU;
    }
    else {
        return NULL_POLICY;
    }
}

char * replace_policy_to_str(ReplacePolicy policy) {
    if (policy == LFU) {
        return "LFU";
    }
    else if (policy == LRU) {
        return "LRU";
    }
    else {
        return "NULL";
    }
}

