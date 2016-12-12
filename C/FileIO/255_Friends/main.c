#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HashF(x, y) (((x)*10000+(y))%97)

struct person{
	unsigned int id;
	char name[32];
};

struct friends {
	unsigned id1;
	unsigned id2;
};

struct person P[97][10001];
int countP[97] = {0};
struct friends F[97][10001];
int countF[97] = {0};

int main(){
	FILE *fin = fopen("friends", "rb");
	int nP, nF;
	fread(&nP, sizeof(int), 1, fin);
	for(int i=0; i<nP; i++){
		struct person tmpP;
		fread(&tmpP, sizeof(struct person), 1, fin);
		int tmpH = HashF(tmpP.name[0], tmpP.name[1]);
		P[tmpH][countP[tmpH]] = tmpP;
		countP[tmpH]++;
	}
	fread(&nF, sizeof(int), 1, fin);
	for(int i=0; i<nF; i++){
		struct friends tmpF;
		fread(&tmpF, sizeof(struct friends), 1, fin);
		int tmpH = HashF(tmpF.id1, tmpF.id2);
		F[tmpH][countF[tmpH]] = tmpF;
		countF[tmpH]++;
	}

	char tmp1[32], tmp2[32];
	while(scanf("%s", tmp1)!=EOF){
		if(strncmp(tmp1, "end", 32)==0)break;
		scanf("%s", tmp2);
		
		int hashP1, hashP2, index1, index2;
		int hash = HashF(tmp1[0], tmp1[1]);
		for(int i=0; i<countP[hash]; i++){
			if(strncmp(P[hash][i].name, tmp1, 32)==0){
				hashP1 = hash;
				index1 = i;
				break;
			}
		}
		hash = HashF(tmp2[0], tmp2[1]);
		for(int i=0; i<countP[hash]; i++){
			if(strncmp(P[hash][i].name, tmp2, 32)==0){
				hashP2 = hash;
				index2 = i;
			}
		}

		int isFriend = 0;
		hash = HashF(P[hashP1][index1].id, P[hashP2][index2].id);
		for(int i=0; i<countF[hash]; i++){
			if(F[hash][i].id1==P[hashP1][index1].id && F[hash][i].id2==P[hashP2][index2].id) isFriend = 1;
			if(F[hash][i].id1==P[hashP2][index2].id && F[hash][i].id2==P[hashP1][index1].id) isFriend = 1;
			if(isFriend) break;
		}
		if(isFriend){
			printf("yes\n");
			continue;
		}
		hash = HashF(P[hashP2][index2].id, P[hashP1][index1].id);
		for(int i=0; i<countF[hash]; i++){
			if(F[hash][i].id1==P[hashP1][index1].id && F[hash][i].id2==P[hashP2][index2].id) isFriend = 1;
			if(F[hash][i].id1==P[hashP2][index2].id && F[hash][i].id2==P[hashP1][index1].id) isFriend = 1;
			if(isFriend) break;
		}
		if(isFriend) printf("yes\n");
		else printf("no\n");
	}
	return 0;
}
