#include "activity.h"
#include <stdio.h>
 
#define MAXN 262144
Activity A[MAXN];
int main() {
    int n, cases = 0;
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++)
            scanf("%d %d", &A[i].start, &A[i].end);
        int ret = select(A, n);
        printf("%d\n", ret);
    }
    return 0;
}
