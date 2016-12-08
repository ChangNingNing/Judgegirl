#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	int index;
	struct Node *next;
}Node;

void myInit(Node List[][2]){
	for(int i=0; i<26; i++){
		List[i][0].index = 0;
		List[i][0].next = List[i][1].next = NULL;
	}
	return;
}

void myInsert(Node node[2], int index){
	Node *tmp = (Node *)malloc(sizeof(Node));
	tmp->index = index;
	tmp->next = node[0].next;
	node[0].next = tmp;
	if(node[0].index==0)
		node[1].next = tmp;
	node[0].index++;
	return;
}

void myReplace(Node start[2], Node dest[2]){
	if(start == dest) return;
	if(start[0].index == 0) return;
	Node *tmp = start[0].next;
	Node *cur = dest[1].next;
	if(cur == NULL) cur = &dest[0];
	cur->next = tmp;
	dest[0].index += start[0].index;
	dest[1].next = start[1].next;
	start[0].index = 0;
	start[0].next = start[1].next = NULL;
	return;
}

void myRemove(Node node[2]){
	node[0].next = node[1].next = NULL;
	node[0].index = 0;
	return;
}

int main(){
	char S[100001];
	Node List[26][2];
	myInit(List);
	scanf("%s", S);
	int length = strlen(S);
	for(int i=0; i<length; i++)
		myInsert(List[S[i]-'a'], i);
	int left = 0, right = length;
	
	char cmd[32], ins1[5], ins2[5];
	while(scanf("%s", cmd)!=EOF){
		if(strcmp(cmd, "end")==0) break;
		else if(!strcmp(cmd, "replace")){
			scanf("%s %s", ins1, ins2);
			myReplace(List[ins1[0]-'a'], List[ins2[0]-'a']);
		}
		else if(!strcmp(cmd, "remove")){
			scanf("%s", ins1);
			myRemove(List[ins1[0]-'a']);
		}
		else if(!strcmp(cmd, "addhead")){
			scanf("%s", ins1);
			myInsert(List[ins1[0]-'a'], --left);
		}
		else if(!strcmp(cmd, "addtail")){
			scanf("%s", ins1);
			myInsert(List[ins1[0]-'a'], right++);
		}
		else{
			printf("invalid command %s\n", cmd);
			return 0;
		}
	}
	
	char tmpA[200002] = {'\0'};
	char Ans[200002] = {'\0'};
	for(int i=0; i<26; i++){
		for(Node *cur = List[i][0].next; cur!=NULL; cur=cur->next)
			tmpA[cur->index - left] = i + 'a';
	}
	int index = 0;
	for(int i=0; i<=right-left; i++){
		if(tmpA[i]!='\0')
			Ans[index++] = tmpA[i];
	}
	printf("%s\n", Ans);
	return 0;
}
