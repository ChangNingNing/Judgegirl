#include "employee.h"
#include <stdio.h>

int relation(Employee *employee1, Employee *employee2) {
    Employee *current = employee1;
    while((*current).boss != current){
    	if((*current).boss == employee2) return 1;
	current = (*current).boss;
    }
    Employee *boss1 = current;

    current = employee2;
    while((*current).boss != current){
    	if((*current).boss == employee1) return 2;
	current = (*current).boss;
    }

    if(boss1 == current) return 3;
    return 4;
}
