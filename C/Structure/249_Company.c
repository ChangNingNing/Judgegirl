#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct employee {
	int id;
	char first_name[32];
	char last_name[32];
	int boss_id;
	int boss_index;
} Employee;

int main(){
	int nEmployee;
	scanf("%d", &nEmployee);
	Employee E[nEmployee];
	for(int i=0; i<nEmployee; i++){
		scanf("%d %s %s %d", &E[i].id, E[i].first_name, E[i].last_name, &E[i].boss_id);
	}
	for(int i=0; i<nEmployee; i++){
		for(int j=0; j<nEmployee; j++){
			if(E[j].id==E[i].boss_id){
				E[i].boss_index = j;
				break;
			}
		}
	}

	int nRelation;
	scanf("%d", &nRelation);
	while(nRelation--){
		char name[2][2][32];
		scanf("%s %s %s %s", name[0][0], name[0][1], name[1][0], name[1][1]);
		int index[2];
		for(int i=0; i<nEmployee; i++){
			if(strncmp(E[i].first_name, name[0][0], 32)==0 &&
				strncmp(E[i].last_name, name[0][1], 32)==0) index[0] = i;
			if(strncmp(E[i].first_name, name[1][0], 32)==0 &&
				strncmp(E[i].last_name, name[1][1], 32)==0) index[1] = i;
		}
		int flag = 0;/* 0:unrelated; 1:subordinate; 2:supervisor; 3:colleague; */
		int boss1, boss2;
		int current = index[0];
		while(E[current].boss_id!=E[current].id){
			if(E[current].boss_id==E[index[1]].id){
				flag = 1;
				break;
			}
			current = E[current].boss_index;
		}
		if(flag){
			printf("subordinate\n");
			continue;
		}
		boss1 = E[current].id;
		
		current = index[1];
		while(E[current].boss_id!=E[current].id){
			if(E[current].boss_id==E[index[0]].id){
				flag = 2;
				break;
			}
			current = E[current].boss_index;
		}
		if(flag){
			printf("supervisor\n");
			continue;
		}
		boss2 = E[current].id;

		if(boss1==boss2){
			printf("colleague\n");
			continue;
		}
		
		printf("unrelated\n");
		continue;
	}

	return 0;
}
