#include <stdio.h>
#include <assert.h>
#include <omp.h>
#include <inttypes.h>
#include "utils.h"
#include <CL/cl.h>
 
#define MAXGPU 3
#define MAXCODESZ 32767

#define DEVICENUM 3
#define CHUNK 1024
#define threads 256
#define AtomicN 8
#define MAXN 10005

cl_platform_id		platform_id;
cl_device_id		GPU[MAXGPU];
const char *constKernelSource;
size_t kernelLength;

int preProcess(){
	cl_int status;

	/* get platform */
	cl_uint platform_id_got;
	status = clGetPlatformIDs(1, &platform_id, &platform_id_got);
	assert(status == CL_SUCCESS && platform_id_got == 1);

	/* get device */
	cl_uint GPU_id_got;
	status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, MAXGPU, GPU, &GPU_id_got);
	assert(status == CL_SUCCESS && GPU_id_got >= DEVICENUM);

	/* Kernel source */
	FILE *kernelfp = fopen("vecdot.cl", "r");
	assert(kernelfp != NULL);
	char kernelBuffer[MAXCODESZ];
	constKernelSource = kernelBuffer;
	kernelLength = fread(kernelBuffer, 1, MAXCODESZ, kernelfp);
	return 1;
}

uint32_t N[MAXN], key1[MAXN], key2[MAXN];
static cl_uint C[MAXN];

int main(int argc, char *argv[]) {
	cl_int status = preProcess();
	assert(status);

	// read in
	uint32_t nCase = 0, maxN = 0;
    while (scanf("%d %" PRIu32 " %" PRIu32, &N[nCase], &key1[nCase], &key2[nCase]) == 3){
		if (N[nCase] > maxN) maxN = N[nCase];
		nCase++;
	}

	// partition
	uint32_t nCaseD[DEVICENUM], leftD[DEVICENUM];
	if (nCase < 1024){
		nCaseD[0] = nCase, leftD[0] = 0;
		nCaseD[1] = nCaseD[2] = 0;
		leftD[1] = leftD[2] = 0;
	}
	else {
		nCaseD[0] = nCase * 5 / 9, leftD[0] = 0;
		nCaseD[1] = nCase * 3 / 9, leftD[1] = nCaseD[0];
		nCaseD[2] = nCase - nCaseD[0] - nCaseD[1], leftD[2] = leftD[1] + nCaseD[1];
	}

	#pragma omp parallel for schedule(static, 1)
	for (int i=0; i<DEVICENUM; i++){
		if (nCaseD[i] == 0) continue;
		// get context
		cl_context context = clCreateContext(NULL, 1, GPU + i, NULL, NULL, &status);
		assert(status == CL_SUCCESS);

		// command queue
		cl_command_queue commandQueue = clCreateCommandQueue(context, GPU[i], 0, &status);
		assert(status == CL_SUCCESS);

		// create program
		cl_program program = clCreateProgramWithSource(context, 1, &constKernelSource,
							&kernelLength, &status);
		assert(status == CL_SUCCESS);

		// build program
		const int MAXLOG = 4096;
		status = clBuildProgram(program, 1, GPU + i, NULL, NULL, NULL);
		if(status != CL_SUCCESS){
			char log[MAXLOG];
			size_t logLength;
			clGetProgramBuildInfo(program, GPU[i], CL_PROGRAM_BUILD_LOG, MAXLOG, log, &logLength);
			puts(log);
		}
		
		// create kernel		
		cl_kernel kernel_dot = clCreateKernel(program, "myDot", &status);
		assert(status == CL_SUCCESS);

		// create buffer
		cl_mem bufC = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
								nCaseD[i]*sizeof(cl_uint), C+leftD[i], &status); 
		assert(status == CL_SUCCESS);

		// initial
		const int zero = 0;
		status = clEnqueueFillBuffer(commandQueue, bufC, &zero, sizeof(int),
								0, nCaseD[i]*sizeof(cl_uint), 0, NULL, NULL);
		assert(status == CL_SUCCESS);

		uint32_t *_N = &N[leftD[i]];
		uint32_t *_key1 = &key1[leftD[i]];
		uint32_t *_key2 = &key2[leftD[i]];
		for (int j=0; j<nCaseD[i]; j++){
			int nGroups = (((_N[j] + CHUNK - 1)/CHUNK) + threads - 1)/threads;
			int groups = nGroups * threads;

			// set arguments
			status = clSetKernelArg(kernel_dot, 0, sizeof(cl_mem), (void*)&bufC);
			assert(status == CL_SUCCESS);
			status = clSetKernelArg(kernel_dot, 1, sizeof(uint32_t), (void*)&(_N[j]));
			assert(status == CL_SUCCESS);
			status = clSetKernelArg(kernel_dot, 2, sizeof(uint32_t), (void*)&(_key1[j]));
			assert(status == CL_SUCCESS);
			status = clSetKernelArg(kernel_dot, 3, sizeof(uint32_t), (void*)&(_key2[j]));
			assert(status == CL_SUCCESS);
			status = clSetKernelArg(kernel_dot, 4, sizeof(uint32_t), (void*)&j);
			assert(status == CL_SUCCESS);

			// run
			size_t gS[] = {(size_t)groups};
			size_t lS[] = {(size_t)threads};
			status = clEnqueueNDRangeKernel(commandQueue, kernel_dot, 1, NULL, gS, lS, 0, NULL, NULL);
			assert(status == CL_SUCCESS);
		}

		// get result
		status = clEnqueueReadBuffer(commandQueue, bufC, CL_TRUE, 0,
								nCaseD[i]*sizeof(cl_uint), C+leftD[i], 0, NULL, NULL);
		assert(status == CL_SUCCESS);

		clReleaseContext(context);
		clReleaseCommandQueue(commandQueue);
		clReleaseProgram(program);
		clReleaseKernel(kernel_dot);
		clReleaseMemObject(bufC);
	}

	for (int i=0; i<nCase; i++)
			printf("%" PRIu32 "\n", C[i]);
    return 0;
}
