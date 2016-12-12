#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
 
#define MAXN 20

typedef struct Word {
	char name[64];
	int cost, bit;
	float unitCost;
} Word;

int N;
Word word[MAXN];
int Bound = INT_MAX, answer = 0x03ffffff;

void WordSelection(int index, int cost, int bit){
    if(cost >= Bound) return;
    if(bit >= answer && cost < Bound) Bound = cost;
    if(index >= N) return;

    int tmpBit = bit | word[index].bit;
	if(tmpBit != bit)
    	WordSelection(index+1, cost+word[index].cost, tmpBit);
    WordSelection(index+1, cost, bit);
    return;
}

int compare(const void *a, const void *b){
	Word *A = (Word *)a, *B = (Word *)b;
	return A->unitCost - B->unitCost;
}

int main(){
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        scanf("%s %d", word[i].name, &(word[i].cost));
        int length = strlen(word[i].name);
        for(int j=0; j<length; j++)
            word[i].bit |= (1 << (word[i].name[j]-'a'));
        int tmp = 0;
        for(int j=0; j<26; j++)
            if((word[i].bit>>j) & 1) tmp++;
        if(tmp) word[i].unitCost = (float)word[i].cost / tmp;
        else word[i].unitCost = -1;
    }
	qsort(word, N, sizeof(word[0]), compare);
 
    // Recursion
    WordSelection(0, 0, 0);

    printf("%d\n", Bound);
    return 0;
}
