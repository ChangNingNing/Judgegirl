#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char Var[101][8];
int Value[101] = {0};
int nVar = 0;
char Ins[1001][8];
int InsInt[1001][10] = {0};
/*
0:Goto -> line
1:if -> index -> 0:==, 1:!=, 2:>, 3:<, 4:>=, 5:<= -> index -> line
2:print -> index
3:assignment -> index -> index -> 0:+, 1:0, 2:*, 3:/, 4:% -> index
4:stop
*/
int nIns = 1;

int Find(char tmp[]){
	for(int i=0; i<nVar; i++){
		if(strncmp(Var[i], tmp, 8)==0) return i;
	}
	return -1;
}

int main(){
	while(scanf("%s", Var[nVar]) && strncmp(Var[nVar], "END", 8)!=0){
		char tmp[2];
		scanf(" = %d", &Value[nVar]);
		nVar++;
	}
	
	while(scanf("%s", Ins[nIns])!=EOF){
		if(strncmp(Ins[nIns], "GOTO", 8)==0){
			InsInt[nIns][0] = 0;
			scanf("%d", &InsInt[nIns][1]);
		}
		else if(strncmp(Ins[nIns], "IF", 8)==0){
			char tmp[8];
			InsInt[nIns][0] = 1;
			scanf("%s", tmp);
			InsInt[nIns][1] = Find(tmp);
			scanf("%s", tmp);
			if(tmp[0]=='=') InsInt[nIns][2] = 0;
			else if(tmp[0]=='!') InsInt[nIns][2] = 1;
			else if(tmp[0]=='>'){
				if(tmp[1]=='=') InsInt[nIns][2] = 4;
				else InsInt[nIns][2] = 2;
			}
			else{
				if(tmp[1]=='=') InsInt[nIns][2] = 5;
				else InsInt[nIns][2] = 3;
			}
			scanf("%s", tmp);
			InsInt[nIns][3] = Find(tmp);
			scanf("%s", tmp);
			scanf("%d", &InsInt[nIns][4]);
		}
		else if(strncmp(Ins[nIns], "PRINT", 8)==0){
			char tmp[8];
			InsInt[nIns][0] = 2;
			scanf("%s", tmp);
			InsInt[nIns][1] = Find(tmp);
		}
		else if(strncmp(Ins[nIns], "STOP", 8)==0){
			InsInt[nIns][0] = 4;
		}
		else{
			char tmp[8];
			InsInt[nIns][0] = 3;
			InsInt[nIns][1] = Find(Ins[nIns]);
			scanf("%s", tmp);
			scanf("%s", tmp);
			InsInt[nIns][2] = Find(tmp);
			scanf("%s", tmp);
			if(tmp[0] == '+') InsInt[nIns][3] = 0;
			else if(tmp[0]=='-') InsInt[nIns][3] = 1;
			else if(tmp[0]=='*') InsInt[nIns][3] = 2;
			else if(tmp[0]=='/') InsInt[nIns][3] = 3;
			else if(tmp[0]=='%') InsInt[nIns][3] = 4;
			scanf("%s", tmp);
			InsInt[nIns][4] = Find(tmp);
		}
		nIns++;
	}
	int line = 1;
	int flag = 1;
	while(flag){
		switch(InsInt[line][0]){
		case 0:
			line = InsInt[line][1];
			break;
		case 1:
			switch(InsInt[line][2]){
			case 0:
				if(Value[InsInt[line][1]]==Value[InsInt[line][3]]) line = InsInt[line][4];
				else line++;
				break;
			case 1:
				if(Value[InsInt[line][1]]!=Value[InsInt[line][3]]) line = InsInt[line][4];
				else line++;
				break;
			case 2:
				if(Value[InsInt[line][1]] > Value[InsInt[line][3]]) line = InsInt[line][4];
				else line++;
				break;
			case 3:
				if(Value[InsInt[line][1]] < Value[InsInt[line][3]]) line = InsInt[line][4];
				else line++;
				break;
			case 4:
				if(Value[InsInt[line][1]]>=Value[InsInt[line][3]]) line = InsInt[line][4];
				else line++;
				break;
			case 5:
				if(Value[InsInt[line][1]]<=Value[InsInt[line][3]]) line = InsInt[line][4];
				else line++;
				break;
			}
			break;
		case 2:
			printf("%d\n", Value[InsInt[line][1]]);
			line++;
			break;
		case 3:
			switch(InsInt[line][3]){
			case 0:
				Value[InsInt[line][1]] = Value[InsInt[line][2]] + Value[InsInt[line][4]];
				break;
			case 1:
				Value[InsInt[line][1]] = Value[InsInt[line][2]] - Value[InsInt[line][4]];
				break;
			case 2:
				Value[InsInt[line][1]] = Value[InsInt[line][2]] * Value[InsInt[line][4]];
				break;
			case 3:
				Value[InsInt[line][1]] = Value[InsInt[line][2]] / Value[InsInt[line][4]];
				break;
			case 4:
				Value[InsInt[line][1]] = Value[InsInt[line][2]] % Value[InsInt[line][4]];
				break;
			}
			line++;
			break;
		case 4:
			flag = 0;
			break;
		}
	}
	return 0;
}
