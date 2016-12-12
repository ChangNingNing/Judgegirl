#include "locker.h"
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
 
void test_specall() {
#define UNLOCK 0
#define LOCKED 1
#define OPERROR -1
#define PEERROR 10000
    int n, cmds, cmd, lid, combination;
    scanf("%d", &n);
    Lock *locker[32];
    for (int i = 0; i < n; i++)
        locker[i] = (Lock *) malloc(sizeof(Lock));
    for (int i = 0; i < n; i++)
        init(locker[i]);
    scanf("%d", &cmds);
    for (int i = 0; i < cmds; i++) {
        scanf("%d %d", &cmd, &lid);
        if (cmd == 1) {
            int ret = isLocked(locker[lid]);
            printf("isLocked %d %s\n", lid, ret == OPERROR ? "NOTHING HAPPENED" :
                ((ret == LOCKED) ? "LOCKED" : (ret == UNLOCK ? "UNLOCK" : "INVALID VALUE")));
        } else if (cmd == 2) {
            scanf("%d", &combination);
            int ret = lock(locker[lid], combination);
            if (ret == OPERROR)
                printf("lock %d %s\n", lid, "NOTHING HAPPENED");
            else if (ret == PEERROR)
                printf("lock %d %s\n", lid, "INVALID COMBINATION");
            else
                printf("lock %d new pwd: %d\n", lid, ret);
        } else if (cmd == 3) {
            scanf("%d", &combination);
            int ret = unlock(locker[lid], combination);
            printf("unlock %d %s\n", lid, ret == OPERROR ? "NOTHING HAPPENED" :
                ((ret == LOCKED) ? "LOCKED" : (ret == UNLOCK ? "UNLOCK" : "INVALID VALUE")));
        } else {
            assert(0);
        }
    }
}
int main() {
    test_specall();
    return 0;
}
