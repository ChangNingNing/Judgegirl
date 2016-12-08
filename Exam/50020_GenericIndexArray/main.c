#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
 
#define OUTOFBOUND -2147483648
#define HAVENOTSET -2147483647
#define SETSUCCESS 1
void test_specall() {
    int n, l, r;
    int cmds, cmd, aid;
    int index, value;
    scanf("%d", &n);
    ARRAY *a = (ARRAY *) malloc(sizeof(ARRAY)*n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &l, &r);
        init(&a[i], l, r);
    }
    scanf("%d", &cmds);
    for (int i = 0; i < cmds; i++) {
        scanf("%d %d", &cmd, &aid);
        if (cmd == 1) {
            print(&a[aid]);
        } else if (cmd == 2) {
            scanf("%d %d", &index, &value);
            int ret = set(&a[aid], index, value);
            printf("ARRAY ID %d, set(%d, %d) %s\n", aid, index, value, 
                ret == SETSUCCESS ? "SUCCESS" : (ret == OUTOFBOUND ? "OUTOFBOUND" : "HAVENOTSET"));
        } else if (cmd == 3) {
            scanf("%d", &index);
            int ret = get(&a[aid], index);
            printf("ARRAY ID %d, get(%d) ", aid, index);
            if (ret == OUTOFBOUND)    
                printf(": OUTOFBOUND\n");
            else if (ret == HAVENOTSET)
                printf(": HAVENOTSET\n");
            else
                printf("= %d\n", ret);
        } else if (cmd == 4) {
            sort(&a[aid]);
        } else {
            assert(0);
        }
    }
}
int main() {
    int spec = 0;
    void (*FUNC[])() = {test_specall};
    FUNC[spec]();
    return 0;
}
