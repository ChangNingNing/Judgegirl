#include "hangman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int N;
	scanf("%d", &N);
	while(N--){
		char Answer[MAXL], Guess[MAXGL];
		int G;
		scanf("%s %d", Answer, &G);
		scanf("%s", Guess);

		Hangman *hangman = newGame(Answer, G);
		int length = strlen(Guess), flag;
		for(int i=0; i<length; i++){
			flag = guess(hangman, Guess[i]);
			printf("%d ", flag);
			printStatus(hangman);
			if(flag == -1){
				printf("You Lose\n");
				flag = 2;
				break;
			}
			else if(solved(hangman)){
				printf("You Win\n");
				flag = 2;
				break;
			}
		}
		if(flag != 2) printf("You Quit\n");
	}
	return 0;
}
