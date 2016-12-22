#include "utils.h"
 
static long long seed = 1;
int sp_rand() {
       return (seed = (seed * 9301 + 49297) % 233280);
}
void sp_srand(long long t) {
    seed = t;
}
