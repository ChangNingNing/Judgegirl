#include <stdio.h>
#include <assert.h>
#include <omp.h>
#include <inttypes.h>
#include "utils.h"
#include <CL/cl.h>
 
#define MAXGPU 3
#define MAXCODESZ 32767
#define DEVICENUM 1

#define CHUNK 1024
#define threads 256
#define MAXN (((16777216 + CHUNK - 1)/CHUNK) + threads - 1) / threads

static cl_uint C[MAXN];

cl_context context;
cl_command_queue commandQueue;
cl_program program;
cl_kernel kernel_dot;
int preProcess(){
	cl_int status;

	/* get platform */
	cl_platform_id platform_id;
	cl_uint platform_id_got;
	status = clGetPlatformIDs(1, &platform_id, &platform_id_got);
	assert(status == CL_SUCCESS && platform_id_got == 1);

	/* get device */
	cl_device_id GPU[MAXGPU];
	cl_uint GPU_id_got;
	status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, MAXGPU, GPU, &GPU_id_got);
	assert(status == CL_SUCCESS && GPU_id_got >= DEVICENUM);

	/* get context */
	context = clCreateContext(NULL, DEVICENUM, GPU, NULL, NULL, &status);
	assert(status == CL_SUCCESS);

	/* command queue */
	commandQueue = clCreateCommandQueue(context, GPU[0], 0, &status);
	assert(status == CL_SUCCESS);

	/* Kernel source */
	FILE *kernelfp = fopen("vecdot.cl", "r");
	assert(kernelfp != NULL);
	char kernelBuffer[MAXCODESZ];
	const char *constKernelSource = kernelBuffer;
	size_t kernelLength = fread(kernelBuffer, 1, MAXCODESZ, kernelfp);
	program = clCreateProgramWithSource(context, 1, &constKernelSource,
						&kernelLength, &status);
	assert(status == CL_SUCCESS);

	/* build program */
	const int MAXLOG = 4096;
	status = clBuildProgram(program, DEVICENUM, GPU, NULL, NULL, NULL);
	if(status != CL_SUCCESS){
		char log[MAXLOG];
		size_t logLength;
		clGetProgramBuildInfo(program, GPU[0], CL_PROGRAM_BUILD_LOG, MAXLOG, log, &logLength);
		puts(log);
		return 0;
	}

	/* create kernel */
	kernel_dot = clCreateKernel(program, "myDot", &status);
	assert(status == CL_SUCCESS);

	return 1;
}

int main(int argc, char *argv[]) {
    int N;
    uint32_t key1, key2;
	cl_int status = preProcess();
	assert(status);

	/* create buffer */
	cl_mem bufferC = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR,
						MAXN * sizeof(cl_uint), C, &status); 
	assert(status == CL_SUCCESS);

    while (scanf("%d %" PRIu32 " %" PRIu32, &N, &key1, &key2) == 3) {
		int nGroups = (((N + CHUNK - 1)/CHUNK) + threads - 1)/threads;
		int groups = nGroups * threads;

		/* set arguments*/
		status = clSetKernelArg(kernel_dot, 0, sizeof(cl_mem), (void*)&bufferC);
		assert(status == CL_SUCCESS);
		status = clSetKernelArg(kernel_dot, 1, sizeof(uint32_t), (void*)&N);
		assert(status == CL_SUCCESS);
		status = clSetKernelArg(kernel_dot, 2, sizeof(uint32_t), (void*)&key1);
		assert(status == CL_SUCCESS);
		status = clSetKernelArg(kernel_dot, 3, sizeof(uint32_t), (void*)&key2);
		assert(status == CL_SUCCESS);
		/* run */
		size_t gS[] = {(size_t)groups};
		size_t lS[] = {(size_t)threads};
		status = clEnqueueNDRangeKernel(commandQueue, kernel_dot, 1, NULL, gS, lS, 0, NULL, NULL);
		assert(status == CL_SUCCESS);

		/* get result */
		status = clEnqueueReadBuffer(commandQueue, bufferC, CL_TRUE, 0,
					nGroups*sizeof(cl_uint), C, 0, NULL, NULL);
		assert(status == CL_SUCCESS);	
 
		uint32_t sum = 0;
		for (int i=0; i<nGroups; i++)
			sum += C[i];
        printf("%" PRIu32 "\n", sum);
    }
	clReleaseContext(context);
	clReleaseCommandQueue(commandQueue);
	clReleaseProgram(program);
	clReleaseKernel(kernel_dot);
	clReleaseMemObject(bufferC);
    return 0;
}
