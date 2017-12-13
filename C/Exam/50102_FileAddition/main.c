#include <stdio.h>
#include <stdint.h>

#define BUFN 4096
uint8_t buf1[BUFN], buf2[BUFN], buf3[BUFN];

uint8_t ByteAdd(uint8_t a, uint8_t b, uint8_t *carry){
	int sum = (int)a + b + *carry;
	if (sum > 255) *carry = 1;
	else *carry = 0;
	return (uint8_t)sum;
}

int main(){
	char in1[32], in2[32], out[32];
	scanf("%s %s %s", in1, in2, out);
	FILE *fin1 = fopen(in1, "rb");
	FILE *fin2 = fopen(in2, "rb");
	FILE *fout = fopen(out, "wb");
	fseek(fin1, 0, SEEK_END);
	fseek(fin2, 0, SEEK_END);
	int s1 = ftell(fin1), s2 = ftell(fin2);

	if (s1 < s2){
		int t = s1;
		s1 = s2;
		s2 = t;
		FILE *ft = fin1;
		fin1 = fin2;
		fin2 = ft;
	}

	fseek(fout, s1, SEEK_SET);
	uint8_t carry = 0;

	while (s1 > 0 || s2 > 0){
		int fn1 = ftell(fin1);
		int fn2 = ftell(fin2);
		int rn =fn2!=0?	fn2>=BUFN? BUFN: fn2:
						fn1>=BUFN? BUFN: fn1;
		if (fn2 != 0){
			fseek(fin1, -rn, SEEK_CUR);
			fseek(fin2, -rn, SEEK_CUR);
			fseek(fout, -rn, SEEK_CUR);
			fread(buf1, sizeof(uint8_t), rn, fin1);
			fread(buf2, sizeof(uint8_t), rn, fin2);
			for (int i=rn-1; i>=0; i--)
				buf3[i] = ByteAdd(buf1[i], buf2[i], &carry);
			fwrite(buf3, sizeof(uint8_t), rn, fout);
			fseek(fin1, -rn, SEEK_CUR);
			fseek(fin2, -rn, SEEK_CUR);
			fseek(fout, -rn, SEEK_CUR);
			s1 -= rn, s2 -= rn;
		}
		else if (fn1 > 0){
			fseek(fin1, -rn, SEEK_CUR);
			fseek(fout, -rn, SEEK_CUR);
			fread(buf1, sizeof(uint8_t), rn, fin1);
			for (int i=rn-1; i>=0; i--)
				buf3[i] = ByteAdd(buf1[i], 0, &carry);
			fwrite(buf3, sizeof(uint8_t), rn, fout);
			fseek(fin1, -rn, SEEK_CUR);
			fseek(fout, -rn, SEEK_CUR);
			s1 -= rn;
		}
	}

	fclose(fin1);
	fclose(fin2);
	fclose(fout);
	return 0;
}
