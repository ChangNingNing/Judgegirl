#include <stdio.h>
#include <stdlib.h>
 
char A[1024][513];
 
int main(){
    int N, M;
    while(scanf("%d %d", &N, &M)!=EOF){
        int S = 0;
        for(int i=0; i<N; i++){
            scanf("%s", A[i]);
        }
        for(int i=0; i<N; i++){
            for(int j=i+1; j<N; j++){
                int con = 0, uni = 0;
                for(int k=0; k<M; k++){
                    if(A[i][k]=='1' && A[j][k]=='1') con++;
                    if(A[i][k]=='1' || A[j][k]=='1') uni++;
                }
		printf("%d %d\n", con, uni);
                float sim = (float)con/uni;
                if(sim >= 0.8) S++;
            }
        }
        printf("%.2f\n", (float)(S*100)/(N*(N-1)/2));
    }
    return 0;
}
