#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int letter[26] = {0};
char M[26][26] = {0};

void construct(char *ans, int index, int length){
	if(index == length){
		ans[index] = '\0';
		puts(ans);
		return;
	}
	for(int i=0; i<26; i++){
		if(index > 0 && M[ans[index-1]-'a'][i]) continue;
		if(letter[i]>0){
			ans[index] = i + 'a';
			letter[i]--;
			construct(ans, index+1, length);
			letter[i]++;
		}
	}
}

int main(){
	char input[22];
	scanf("%s", input);
	int length = strlen(input);
	for(int i=0; i<length; i++)
		letter[input[i]-'a']++;
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		char rule[4];
		scanf("%s", rule);
		M[rule[0]-'a'][rule[1]-'a'] = 1;
	}
	char output[22];
	construct(output, 0, length);
	return 0;
}
