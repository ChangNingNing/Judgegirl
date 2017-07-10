#include <stdio.h>

#define MAXN 2003

__device__ __host__ int CeilDiv(int a, int b) { return (a-1)/b + 1; }

__device__ int neighbor(int index, int n, char* cuT){
	int num;
	num = cuT[index-n-1] + cuT[index-n-0] + cuT[index-n+1]
		+ cuT[index-0-1] 				  + cuT[index-0+1]
		+ cuT[index+n-1] + cuT[index+n-0] + cuT[index+n+1];
	return num;
}

__global__ void myGOL( char *cuT, int W, int N){
	int tid = blockIdx.x * blockDim.x + threadIdx.x;
	if (tid >= N*N) return;

	int n = N + 2;
	int x = tid / N + 1, y = tid % N + 1;
	int R = W ^ 1;
	int Rindex = x*n+y + R*n*n;
	int Windex = x*n+y + W*n*n;

	int num = neighbor( Rindex, n, cuT );
	cuT[Windex] = cuT[Rindex]? num==2 || num==3: num==3;
}

int main(){
	int N, M;
	static char T[MAXN*MAXN] = {0};
	char *cuT;

	scanf("%d %d", &N, &M);
	int n = N + 2;
	for (int i=1; i<=N; i++)
		scanf("%s", T+i*n+1);
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			T[i*n+j] = T[i*n+j]=='1'? 1: 0;

	cudaMalloc( &cuT, sizeof(char)*n*n*2 );
	cudaMemset( cuT, 0, sizeof(char)*n*n*2 );
	cudaMemcpy( cuT, T, sizeof(char)*n*n, cudaMemcpyHostToDevice );

	int flag = 0;
	dim3 grid(CeilDiv(N*N, 256)), block(256);
	for (int i=0; i<M; i++){
		flag ^= 1;
		myGOL<<< grid, block >>>( cuT, flag, N );
	}

	cudaMemcpy( T, cuT + flag*n*n, sizeof(char)*n*n, cudaMemcpyDeviceToHost );
	cudaFree(cuT);

	static char out[MAXN*MAXN];
	int length = 0;
	for (int i=1; i<=N; i++){
		for (int j=1; j<=N; j++)
			out[length++] = T[i*n+j] + '0';
		out[length++] = '\n';
	}
	out[--length] = '\0';
	puts(out);
	return 0;
}
