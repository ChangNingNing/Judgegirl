#include <stdio.h>

int main(){
	char fName[16];
	scanf("%s", fName);
	FILE *fin = fopen(fName, "rb");
	int ins, par;
	char tmp[5], tmp2;
	while(fread(&ins, sizeof(int), 1, fin)){
		switch(ins){
		case 0:
			fread(&par, sizeof(int), 1, fin);
			printf("%d", par);
			break;
		case 1:
			fread(tmp, sizeof(char), 4, fin);
			tmp[4] = '\0';
			printf("%s", tmp);
			break;
		case 2:
			fread(&par, sizeof(int), 1, fin);
			while(1){
				fread(&tmp2, sizeof(char), 1, fin);
				if(tmp2 != '\0') putchar(tmp2);
				else break;
			}
			break;
		case 3:
			fread(&par, sizeof(int), 1, fin);
			fseek(fin, par-8, SEEK_CUR);
			break;
		case 4:
			fread(&par, sizeof(int), 1, fin);
			fseek(fin, par, SEEK_SET);
			break;
		case 5:
			fread(&par, sizeof(int), 1, fin);
			fseek(fin, par, SEEK_END);
			break;
		default:
			printf("Seek end");
			return 0;
		}
	}
	return 0;
}
