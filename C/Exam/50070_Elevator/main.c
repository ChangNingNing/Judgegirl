#include "elevator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(){
    int N;
    for(scanf("%d", &N); N>0; N--){
        int u, d, F;
        char ins[MAXL];
        scanf("%d %d %d", &u, &d, &F);
        scanf("%s", ins);
        Elevator *e = newElevator(u, d, F);
        int length = strlen(ins), flag;
        for(int i=0; i<length; i++){
            switch(ins[i]){
            case 'U':
                flag = up(e);
                break;
            case 'D':
                flag = down(e);
                break;
            }
            if(flag == 1) printf("Valid %d\n", getPosition(e));
            else if(flag == 0) printf("Invalid\n");
            else{
                printf("Broken\n");
                i = length;
            }
        }
        for(int i=1; i<=F; i++)
            if(visited(e, i)) printf("%d\n", i);
    }
    return 0;
}
