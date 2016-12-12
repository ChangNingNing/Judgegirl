#include "locker.h"

void init(Lock *lock){ lock->isLock = 0; }

int lock(Lock *lock, int combination){
	if(lock->isLock) return -1;
	if(combination < 0 || combination > 9999) return 10000;
	lock->combination = combination;
	lock->isLock = 1;
	return combination;
}

int unlock(Lock *lock, int combination){
	if(!lock->isLock) return -1;
	if(lock->combination != combination) return 1;
	lock->isLock = 0;
	return 0;
}

int isLocked(Lock *lock){ return lock->isLock; }
