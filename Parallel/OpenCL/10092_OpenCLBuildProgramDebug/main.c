#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <CL/cl.h>

#define MAXGPU 10
#define DEVICENUM 1
cl_device_id GPU[MAXGPU];
cl_context context;
cl_command_queue commandQueue;
cl_program program;
cl_kernel kernel;

int Preprocess(char *fName){
    cl_int status;

    /* get platform */
    cl_platform_id platform_id;
    cl_uint platform_id_got;
    status = clGetPlatformIDs(1, &platform_id, &platform_id_got);
    assert(status == CL_SUCCESS && platform_id_got == 1);

    /* get device */
    cl_uint GPU_id_got;
    status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, MAXGPU, GPU, &GPU_id_got);
    assert(status == CL_SUCCESS && GPU_id_got >= DEVICENUM);

    /* get context */
    context = clCreateContext(NULL, DEVICENUM, GPU, NULL, NULL, &status);
    assert(status == CL_SUCCESS);

    /* get command queue */
    commandQueue = clCreateCommandQueue(context, GPU[0], 0, &status);
    assert(status == CL_SUCCESS);

    /* kernel source */
    int MAXK = 1024;
    FILE *kernelfp = fopen(fName, "r");
    assert(kernelfp != NULL);
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
        fputs(log, stdout);
        return 0;
    }

    /* create kernel */
    kernel = clCreateKernel(program, "mul", &status);
    assert(status == CL_SUCCESS);
    return 1;
}

int main(){
	char fName[31];
	scanf("%s", fName);
	cl_uint status = Preprocess(fName);
	return 0;
}
