#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"
 
void init_storage(Employee **storage, int n)
{
    // allocate memory space to store employee data
    // no need to understand this function now.
 
    (*storage) = (Employee *)malloc(sizeof(Employee) * n);
}
 
void free_storage(Employee **storage)
{
    free(*storage);
    *storage = 0;
}

Employee* find_employee_by_id( Employee *set, int n, int id){
	for(int i=0; i<n; i++){
		if(set[i].id == id) return &(set[i]);
	}
}

Employee* find_employee_by_name( Employee *set, int n, const char *first_name, const char *last_name){
	for(int i=0; i<n; i++){
		if(strncmp(set[i].first_name, first_name, 32)==0){
			if(strncmp(set[i].last_name, last_name, 32)==0){
				return &(set[i]);
			}
		}
	}
}

Employee* find_root_boss( Employee *set, int n, Employee *employee){
	while((*employee).boss_id!=(*employee).id){
		employee = find_employee_by_id(set, n, (*employee).boss_id);
	}
	return employee;
}

int check_relationship( Employee *set, int n, Employee *A, Employee *B){
	Employee *current = A;
	while((*current).boss_id!=(*current).id){
		if((*current).boss_id==(*B).id){
			return 1;
		}
		current = find_employee_by_id( set, n, (*current).boss_id);
	}
	
	current = B;
	while((*current).boss_id!=(*current).id){
		if((*current).boss_id==(*A).id){
			return 2;
		}
		current = find_employee_by_id( set, n, (*current).boss_id);
	}

	if(find_root_boss( set, n, A)==find_root_boss( set, n, B))
		return 3;
	return 4;
}
