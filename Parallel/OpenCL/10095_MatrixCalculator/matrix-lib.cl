__kernel void matrixMul(__global int A[], __global int B[], __global int C[], int N){
	int globalID = get_global_id(0);
	int row = globalID / N, col = globalID % N;
	unsigned sum = 0;
	A += row*N, B += col*N;
	for(int i=0; i<N; i++)
		sum += *A++ * *B++;
	C[globalID] = sum;
}

__kernel void matrixAdd(__global int A[], __global int B[], __global int C[], int N){
	int globalID = get_global_id(0);
	C[globalID] = A[globalID] + B[globalID];
}
