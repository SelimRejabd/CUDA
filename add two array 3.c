%%cu
// m blocks and n threads per block (In this example m=2 and n=3)

#include <stdio.h>
#include <cuda.h>
        __global__ void
        arradd(int *x, int *y, int *z)
{
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    // blockIdx.x gives the respective block id which starts from 0 
    // threadIdx.x gives the respective thread id which starts from 0
    // blockDim.x gives the dimension of block i.e. number of threads in one block
    z[id] = x[id] + y[id];
}
int main()
{
    int a[6] = {1, 2, 3, 4, 5, 6};
    int b[6] = {3, 4, 5, 6, 7, 8};
    int c[6];
    int *d, *e, *f;
    int i;

    cudaMalloc((void **)&d, 6 * sizeof(int));
    cudaMalloc((void **)&e, 6 * sizeof(int));
    cudaMalloc((void **)&f, 6 * sizeof(int));
    cudaMemcpy(d, a, 6 * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(e, b, 6 * sizeof(int), cudaMemcpyHostToDevice);
    arradd<<<2, 3>>>(d, e, f);
    cudaMemcpy(c, f, 6 * sizeof(int), cudaMemcpyDeviceToHost);
    printf("\nSum of two arrays:\n ");
    for (i = 0; i < 6; i++)
    {
        printf("%d\t", c[i]);
    }
    cudaFree(d);
    cudaFree(e);
    cudaFree(f);
    return 0;
}