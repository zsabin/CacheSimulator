#include "util.h"

int log_2(int val) {
    int ans = 0;
    while (val>>=1) {
            ans++;
    }
    return ans;
}

int exp_2(int exp) {
    int ans = exp >= 1 ? 2 << (exp - 1) : 2 >> (exp - 1);
    return ans;
}

