#include <stdio.h>
#include <string.h>

#define MAXL 1024
#define MAXI 1024
char S[MAXL], ins[MAXI];

int main(){
	scanf("%s", S);
	char del[2] = " ";
	char *A, *B;
	while (scanf("%s",ins)==1){
		if (ins[0] == 's'){
			del[0] = ins[1];
			A = strtok(ins+2, del);
			B = strtok(NULL, del);

			char *S1 = strstr(S, A);
			if (S1 == NULL) continue;

			int lenA = strlen(A);
			int lenB = strlen(B);
			strcpy(S1 + lenB, S1 + lenA);
			strncpy(S1, B, lenB);
		}
		else printf("%s\n", S);
	}
	return 0;
}
