#ifndef _ACTIVITY_H
#define _ACTIVITY_H 
 
typedef struct activity {
    int start;
    int end;
} Activity;
 
int select(Activity activities[], int n);
 
#endif
