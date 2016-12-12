#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int answer[64][5];

int main(){
	int n, r, w;
	while(scanf("%d %d %d", &n, &r, &w)==3){
		memset(answer, 0, sizeof(answer));
		char tmp[8];
		for(int i=0; i<n; i++){
			scanf("%s", tmp);
			for(int j=0; tmp[j]!='\0'; j++)
				answer[i][tmp[j]-'A'] = 1;
		}
		int nStu;
		for(scanf("%d", &nStu)==1; nStu>0; nStu--){
			int grade = 0;
			for(int i=0; i<n; i++){
				int compare[5] = {0};
				scanf("%s", tmp);
				if(!strcmp(tmp, "N/A")) continue;
				for(int j=0; tmp[j]!='\0'; j++){
					if(tmp[j] > 'E' ) tmp[j] -= ('a' - 'A');
					compare[tmp[j]-'A'] = 1;
				}
				int flag = 1;
				for(int j=0; j<5; j++){
					if(answer[i][j] != compare[j]){
						flag = 0;
						break;
					}
				}
				if(flag) grade += r;
				else grade -= w;
			}
			printf("%d\n", (grade<0)? 0: grade);
		}
	}
	return 0;
}
