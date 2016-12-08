#ifndef _LOCKER_H
#define _LOCKER_H
 
typedef struct Lock{
	int isLock;
	int combination;
} Lock;
 
void init(Lock *lock);
int lock(Lock *lock, int combination);
int unlock(Lock *lock, int combination);
int isLocked(Lock *lock);
#endif
