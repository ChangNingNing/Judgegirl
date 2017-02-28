#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <CL/cl.h>
#define MAXN 2003
#define MAXGPU 1
#define DEVICENUM 1

cl_device_id GPU[MAXGPU];
cl_context context;
cl_command_queue commandQueue;
cl_program program;
cl_kernel kernel;

int Preprocess(){
    cl_uint status;

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
    FILE *kernelfp = fopen("game-of-life.cl", "r");
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
	kernel = clCreateKernel(program, "GameLife", &status);
	assert(status == CL_SUCCESS);
    return 1;
}

void Game(int N, int M, cl_mem buffer) {
	cl_uint status;
	/* NDRange */
	size_t globalS[] = {N*N}, localS[] = {1};

	for(int i=1; i<=M; i++){
		/* set arg */
		status = clSetKernelArg(kernel, 0, sizeof(int), &N);
		status = clSetKernelArg(kernel, 1, sizeof(int), &i);
		status = clSetKernelArg(kernel, 2, sizeof(cl_mem), &buffer);

		/* start kernel */
		status = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL,
					globalS, NULL, 0, NULL, NULL);
	}
	return;
}

char T[2][MAXN*MAXN] = {0};
char output[MAXN*MAXN];
int main() {
    int N, M;
    scanf("%d %d", &N, &M);
	int n = N+2;
	for(int i=1; i<=N; i++)
			scanf("%s", T[0]+i*n+1);
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++){
			if(T[0][i*n+j]=='1') T[0][i*n+j] = 1;
			else T[0][i*n+j] = 0;
		}
	cl_uint status = Preprocess();
	assert(status == 1);

	cl_mem buffer;
	buffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
						sizeof(T), T, &status);
	assert(status == CL_SUCCESS);

	Game(N, M, buffer);	
	status = clEnqueueReadBuffer(commandQueue, buffer, CL_TRUE, 0,
						sizeof(T), T, 0, NULL, NULL);
	int length = 0;
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++, length++)
			output[length] = T[M&1][(i+1)*n+j+1] + '0';
		output[length++] = '\n';
	}
	output[--length] = '\0';
	puts(output);

	clReleaseContext(context);
	clReleaseProgram(program);
	clReleaseCommandQueue(commandQueue);
	clReleaseKernel(kernel);
	clReleaseMemObject(buffer);
    return 0;
}
