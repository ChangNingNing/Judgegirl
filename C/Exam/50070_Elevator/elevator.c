#include "elevator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
struct Elevator {
    int u, d, F, cur, nU, nD;
    char isVisited[MAXF+1];
};
 
Elevator* newElevator(int u, int d, int F){
    Elevator *e = (Elevator *)malloc(sizeof(Elevator));
    e->u = u, e->d = d, e->F = F, e->cur = 1, e->nU = e->nD = 0;
    memset(e->isVisited, 0, sizeof(char)*(F+1));
    e->isVisited[1] = 1;
    return e;
}
 
int up(Elevator* elevator){
    if(elevator->cur + elevator->u > elevator->F){
        elevator->nD = 0, elevator->nU++;
        if(elevator->nU > 3) return -1;
        return 0;
    }
    elevator->nD = elevator->nU = 0;
    elevator->cur += elevator->u;
    elevator->isVisited[elevator->cur] = 1;
    return 1;
}
 
int down(Elevator* elevator){
    if(elevator->cur - elevator->d < 1){
        elevator->nU = 0, elevator->nD++;
        if(elevator->nD > 3) return -1;
        return 0;
    }
    elevator->nD = elevator->nU = 0;
    elevator->cur -= elevator->d;
    elevator->isVisited[elevator->cur] = 1;
    return 1;
}
 
int visited(Elevator* elevator, int floor){
    return elevator->isVisited[floor];
}
 
int getPosition(Elevator* elevator){
    return elevator->cur;
}
