#include "hangman.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
struct Hangman {
	char s[MAXL];
	char T[26], isT[26];
	int G, nG, L;
};
 
Hangman* newGame(char *answer, int G){
	Hangman *hangman = (Hangman *)malloc(sizeof(Hangman));
	strcpy(hangman->s, answer);
	hangman->G = G, hangman->nG = 0;

	memset(hangman->T, 0, sizeof(hangman->T));
	memset(hangman->isT, 0, sizeof(hangman->isT));
	hangman->L = strlen(answer);
	for(int i=0; i<hangman->L; i++) hangman->T[answer[i]-'a'] = 1;
	return hangman;
}

int guess(Hangman* hangman, char ch){
	if(hangman->T[ch-'a']==1){
		hangman->isT[ch-'a'] = 1;
		return 1;
	}
	else{
		if(++hangman->nG >= hangman->G) return -1;
		else return 0;
	}

}

void printStatus(Hangman* hangman){
	for(int i=0; i<hangman->L; i++){
		if(hangman->isT[hangman->s[i]-'a']) putchar(hangman->s[i]);
		else putchar('*');
	}
	puts("");
	return;
}

int solved(Hangman* hangman){
	for(int i=0; i<26; i++)
		if(hangman->T[i] && hangman->isT[i]==0) return 0;
	return 1;
}
