#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <CL/cl.h>
#define UINT uint32_t
#define MAXN 1024
#define MAXGPU 1
#define DEVICENUM 1

cl_device_id GPU[MAXGPU];
cl_context context;
cl_command_queue commandQueue;
cl_program program;
cl_kernel kernelMul, kernelAdd;

int Preprocess(){
    cl_int status;

    /* get platform */
    cl_platform_id platform_id;
    cl_uint platform_id_got;
    status = clGetPlatformIDs(1, &platform_id, &platform_id_got);
	assert(status == CL_SUCCESS);

    /* get device */
    cl_uint GPU_id_got;
    status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, MAXGPU, GPU, &GPU_id_got);
	assert(status == CL_SUCCESS);

    /* get context */
    context = clCreateContext(NULL, DEVICENUM, GPU, NULL, NULL, &status);
	assert(status == CL_SUCCESS);

    /* get command queue */
    commandQueue = clCreateCommandQueue(context, GPU[0], 0, &status);
	assert(status == CL_SUCCESS);

    /* kernel source */
    int MAXK = 1024;
    FILE *kernelfp = fopen("matrix-lib.cl", "r");
    char kernelBuffer[MAXK];
    const char *constKernelSource = kernelBuffer;
    size_t kernelLength = fread(kernelBuffer, 1, MAXK, kernelfp);
    program = clCreateProgramWithSource(context, 1, &constKernelSource, &kernelLength, &status);
	assert(status == CL_SUCCESS);

    /* build program */
	int MAXLOG = 4096;
    status = clBuildProgram(program, 1, GPU, NULL, NULL, NULL);
    if(status != CL_SUCCESS){
        char log[MAXLOG];
        size_t logLength;
        clGetProgramBuildInfo(program, GPU[0], CL_PROGRAM_BUILD_LOG, MAXLOG, log, &logLength);
        puts(log);
        return 0;
    }

	/* create kernel */
	kernelMul = clCreateKernel(program, "matrixMul", &status);
	assert(status == CL_SUCCESS);
	kernelAdd = clCreateKernel(program, "matrixAdd", &status);
	assert(status == CL_SUCCESS);
    return 1;
}

void mul(int N, cl_mem bufferA, cl_mem bufferB, cl_mem bufferC) {
	cl_uint status;

	/* NDRange */
	size_t globalS[] = {N*N}, localS[] = {1};

	/* set arg */
	status = clSetKernelArg(kernelMul, 0, sizeof(cl_mem), (void*)&bufferA);
	status = clSetKernelArg(kernelMul, 1, sizeof(cl_mem), (void*)&bufferB);
	status = clSetKernelArg(kernelMul, 2, sizeof(cl_mem), (void*)&bufferC);
	status = clSetKernelArg(kernelMul, 3, sizeof(int), &N);

	/* start kernel */
	status = clEnqueueNDRangeKernel(commandQueue, kernelMul, 1, NULL,
				globalS, 0, 0, NULL, NULL);
	return;
}

void add(int N, cl_mem bufferA, cl_mem bufferB, cl_mem bufferC) {
	cl_uint status;

	/* NDRange */
	size_t globalS[] = {N*N}, localS[] = {1};

	/* set arg */
	status = clSetKernelArg(kernelAdd, 0, sizeof(cl_mem), (void*)&bufferA);
	status = clSetKernelArg(kernelAdd, 1, sizeof(cl_mem), (void*)&bufferB);
	status = clSetKernelArg(kernelAdd, 2, sizeof(cl_mem), (void*)&bufferC);
	status = clSetKernelArg(kernelAdd, 3, sizeof(int), &N);

	/* start kernel */
	status = clEnqueueNDRangeKernel(commandQueue, kernelAdd, 1, NULL,
				globalS, 0, 0, NULL, NULL);
	return;
}

void rand_gen(UINT c, int N, UINT A[MAXN*MAXN]) {
    UINT x = 2, n = N*N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            x = (x * x + c + i + j)%n;
            A[i*N+j] = x;
        }
    }
}

UINT signature(int N, UINT A[MAXN*MAXN]) {
    UINT h = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            h = (h + A[i*N+j]) * 2654435761LU;
    }
    return h;
}
UINT IN[6][MAXN*MAXN], TMP[6][MAXN*MAXN];
int main() {
    int N, S[6];
    scanf("%d", &N);
	for(int i=0; i<6; i++)
		scanf("%d", &S[i]);
	#pragma omp parallel for
    for (int i = 0; i < 6; i++)
        rand_gen(S[i], N, IN[i]);
	cl_uint status = Preprocess();

	#pragma omp parallel
	for(int k=0; k<6; k++){
		if(k==0 || k==2) continue;
		#pragma omp for
		for(int i=0; i<N; i++){
			for(int j=i+1; j<N; j++){
				int t = IN[k][i*N+j];
				IN[k][i*N+j] = IN[k][j*N+i];
				IN[k][j*N+i] = t;
			}
		}
	}
	cl_mem buffer[6], bufferTMP[6];
	for(int i=0; i<6; i++){
		buffer[i] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
							N*N*sizeof(UINT), IN[i], &status);
		bufferTMP[i] = clCreateBuffer(context, CL_MEM_READ_WRITE,
							N*N*sizeof(UINT), TMP[i], &status);
	}

    // AB
    mul(N, buffer[0], buffer[1], bufferTMP[0]);
    // CD
    mul(N, buffer[2], buffer[3], bufferTMP[1]);
    // AB+CD
    add(N, bufferTMP[0], bufferTMP[1], bufferTMP[2]);
 
    // ABE
    mul(N, bufferTMP[0], buffer[4], bufferTMP[3]);
    // CDF
    mul(N, bufferTMP[1], buffer[5], bufferTMP[4]);
    // ABE+CDF
    add(N, bufferTMP[3], bufferTMP[4], bufferTMP[5]);

	status = clEnqueueReadBuffer(commandQueue, bufferTMP[2], CL_TRUE, 0,
					N*N*sizeof(UINT), TMP[2], 0, NULL, NULL);
	status = clEnqueueReadBuffer(commandQueue, bufferTMP[5], CL_TRUE, 0,
					N*N*sizeof(UINT), TMP[5], 0, NULL, NULL);
	printf("%u\n%u\n", signature(N, TMP[2]), signature(N, TMP[5]));	

	clReleaseContext(context);
	clReleaseProgram(program);
	clReleaseCommandQueue(commandQueue);
	clReleaseKernel(kernelMul);
	clReleaseKernel(kernelAdd);

	for(int i=0; i<6; i++){
		clReleaseMemObject(buffer[i]);
		clReleaseMemObject(bufferTMP[i]);
	}
    return 0;
}
