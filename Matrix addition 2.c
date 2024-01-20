%%cu
//One block and two dimesional threads in that block
// using blockDim.x

#include <stdio.h>
#include <cuda.h>
__global__ void matadd(int *l, int *m, int *n)
{
    int x = threadIdx.x;
    int y = threadIdx.y;
    int id = blockDim.x * y + x;
    n[id] = l[id] + m[id];
}
int main()
{
    int a[2][3] = {{1, 2, 3},
                   {2, 3, 4}};
    int b[2][3] = {{3, 4, 5},
                   {6, 7, 8}};
    int c[2][3];
    int *d, *e, *f;
    int i, j;
    
    cudaMalloc((void **)&d, 2 * 3 * sizeof(int));
    cudaMalloc((void **)&e, 2 * 3 * sizeof(int));
    cudaMalloc((void **)&f, 2 * 3 * sizeof(int));
    cudaMemcpy(d, a, 2 * 3 * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(e, b, 2 * 3 * sizeof(int), cudaMemcpyHostToDevice);

    dim3 threadBlock(3, 2);
    /* Here we are defining two dimensional Block(collection of threads) structure. Syntax is dim3 threadBlock(no. of columns,no. of rows) */

    matadd<<<1, threadBlock>>>(d, e, f);

    cudaMemcpy(c, f, 2 * 3 * sizeof(int), cudaMemcpyDeviceToHost);
    printf("\nSum of two matrices:\n ");
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%d\t", c[i][j]);
        }
        printf("\n");
    }
    cudaFree(d);
    cudaFree(e);
    cudaFree(f);
    return 0;
}