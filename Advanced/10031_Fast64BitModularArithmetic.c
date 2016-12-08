#include <stdio.h>
#include <stdlib.h>

#define bios 32
int main(){
	unsigned long long a, b, n;
	while(scanf("%llu %llu %llu", &a, &b, &n)!=EOF){
		unsigned long long a_2, b_2;
		a_2 = (a >> bios);
		b_2 = (b >> bios);
		a = (a << bios) >> bios;
		b = (b << bios) >> bios;
		if(a_2==0 && b_2==0){
			printf("%llu\n", ((a % n) * (b % n)) % n);
			continue;
		}
		unsigned long long ab, a2b2, ab2, a2b;
		ab = ((a % n)*(b % n)) % n;
		a2b2 = ((a_2 % n) * (b_2 % n)) % n;
		ab2 = ((a % n) * (b_2 % n)) % n;
		a2b = ((a_2 % n) * (b % n)) % n;
		for(int i=0; i<bios*2; i++) a2b2 = (a2b2 << 1) % n;
		for(int i=0; i<bios; i++){
			ab2 = (ab2 << 1) % n;
			a2b = (a2b << 1) % n;
		}
		unsigned long long ans = ((ab%n)+(a2b2%n)+(ab2%n)+(a2b%n))%n;
		printf("%llu\n", ans);
	}
	return 0;
}
