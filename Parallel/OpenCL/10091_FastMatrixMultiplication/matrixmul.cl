__kernel void matrixMul(__global int A[], __global int B[], __global int C[], int N){
	int globalID = get_global_id(0);
	int row = globalID / N, col = globalID % N;
	A += row*N, B += col*N;
	unsigned sum = 0;
	for(int i=0; i<N; i++, A++, B++)
		sum += *A * *B;
	C[globalID] = sum;
}
