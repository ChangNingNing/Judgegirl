#include "pangfeng.h"
#include <stdio.h>
#include <stdlib.h>
 
int main() {
    const int MAXETB = 8;
    int etb_n, dim_n;
    int cmds, cmd, tid, score[128], sort_order[128];
    char sid[32];
    ExamTable *etb = (ExamTable*) malloc(sizeof(ExamTable)*MAXETB);
    scanf("%d", &etb_n);
    for (int i = 0; i < etb_n; i++) {
        scanf("%d", &dim_n);
        init(&etb[i], dim_n);
    }
    scanf("%d", &cmds);
    for (int i = 0; i < cmds; i++) {
        scanf("%d %d", &cmd, &tid);
        if (cmd == 1) {
            scanf("%s", sid);
            for (int j = 0; j < etb[tid].dim_n; j++)
                scanf("%d", &score[j]);
            addrow(&etb[tid], sid, score);
        } else {
            for (int j = 0; j < etb[tid].dim_n; j++)
                scanf("%d", &sort_order[j]);
            print(&etb[tid], sort_order);
        }
    }
    return 0;
}
