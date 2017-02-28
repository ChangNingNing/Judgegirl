#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <CL/cl.h>
 
#define UINT uint32_t
#define MAXN 1024
 
#define MAXGPU 10
#define DEVICENUM 1
 
cl_uint A[MAXN*MAXN], B[MAXN*MAXN], C[MAXN*MAXN];
cl_device_id GPU[MAXGPU];
cl_context context;
cl_command_queue commandQueue;
cl_program program;
cl_kernel kernel;
 
int Preprocess(){
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
    FILE *kernelfp = fopen("matrixmul.cl", "r");
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
        puts(log);
        return 0;    
    }
 
    /* create kernel */
    kernel = clCreateKernel(program, "matrixMul", &status);
    assert(status == CL_SUCCESS);
    return 1;
}
 
void multiply(int N, cl_uint A[], cl_uint B[], cl_uint C[]) {
    #pragma omp parallel for
    for(int i=0; i<N; i++)
        for(int j=i+1; j<N; j++){
            int t = B[i*N + j];
            B[i*N+j] = B[j*N+i];
            B[j*N+i] = t;
        }
 
    cl_uint status;
    status = Preprocess();
    assert(status == 1);
 
    /* create buffer */
    cl_mem bufferA, bufferB, bufferC;
    bufferA = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                            N*N*sizeof(cl_uint), A, &status);
    assert(status == CL_SUCCESS);
    bufferB = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                            N*N*sizeof(cl_uint), B, &status);
    assert(status == CL_SUCCESS);
    bufferC = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR,
                            N*N*sizeof(cl_uint), C, &status);
    assert(status == CL_SUCCESS);
 
    /* NDRange */
    size_t globalS[] = {N*N};
    size_t localS[] = {1};
 
    /* set arg */
    cl_int cln = N;
    status = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&bufferA);
    assert(status == CL_SUCCESS);
    status = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&bufferB);
    assert(status == CL_SUCCESS);
    status = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&bufferC);
    assert(status == CL_SUCCESS);
    status = clSetKernelArg(kernel, 3, sizeof(int), &N);
    assert(status == CL_SUCCESS);
 
    /* start kernel */
    status = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL,
                globalS, 0, 0, NULL, NULL);
    assert(status == CL_SUCCESS);
 
    /* get result */
    status = clEnqueueReadBuffer(commandQueue, bufferC, CL_TRUE, 0,
                    N*N*sizeof(cl_uint), C, 0, NULL, NULL);
    assert(status == CL_SUCCESS);
 
    /* release */
    clReleaseContext(context);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(commandQueue);
    clReleaseMemObject(bufferA);
    clReleaseMemObject(bufferB);
    clReleaseMemObject(bufferC);
}
 
void rand_gen(cl_uint c, int N, cl_uint A[]) {
    cl_uint x = 2, n = N*N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            x = (x * x + c + i + j)%n;
            A[i*N+j] = x;
        }
    }
}
 
UINT signature(int N, cl_uint A[]) {
    cl_uint h = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            h = (h + A[i*N+j]) * 2654435761LU;
    }
    return h;
}
 
int main(int argc, char *argv[]){
    int N;
    cl_uint S1, S2;
    scanf("%d %u %u", &N, &S1, &S2);
    rand_gen(S1, N, A);
    rand_gen(S2, N, B);
    multiply(N, A, B, C);
#ifdef DEBUG
    print_matrix(N, A);
    print_matrix(N, B);
    print_matrix(N, C);
#endif
    printf("%u\n", signature(N, C));
    return 0;
}
