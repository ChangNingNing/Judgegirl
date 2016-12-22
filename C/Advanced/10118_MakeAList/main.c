#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
 
int main() {
    int n;
    long long s;
 
    scanf("%lld", &s);
    sp_srand(s);
    while (scanf("%d", &n) == 1) {
        Node *list = mk_list(n);
        Node *u = list;
        for (int i = 0; i < n; ) {
            long long sum = 0;
            int cnt = 1;
            while (u && cnt < 100000) {
                sum += u->v * cnt;
                u = u->next, cnt++;
                i++;
            }
            printf("%lld\n", sum);
        }
        rm_list(list);
    }
    return 0;
}
