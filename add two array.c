%%cu

// Add two array using n block & n thread.
// One thread per block

#include <stdio.h>
#include <cuda.h>

        __global__ void
        arradd(int *x, int *y, int *z)
{
    int id = blockIdx.x;
    z[id] = x[id] + y[id];
}

int main()
{
    int a[6] = {1, 2, 3, 4, 5, 6};
    int b[6] = {3, 4, 5, 6, 7, 8};
    int c[6];
    int *d, *e, *f;
    int i;
    // freopen("H:/CSE/4Y1S/Parallel Processing/Lab/input1.txt","r", stdin);

    /* cudaMalloc() allocates memory from Global memory on GPU */
    cudaMalloc((void **)&d, 6 * sizeof(int));
    cudaMalloc((void **)&e, 6 * sizeof(int));
    cudaMalloc((void **)&f, 6 * sizeof(int));

    /* cudaMemcpy() copies the contents from destination to source. Here destination is GPU(d,e) and source is CPU(a,b) */
    cudaMemcpy(d, a, 6 * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(e, b, 6 * sizeof(int), cudaMemcpyHostToDevice);

    /* call to kernel. Here 6 is number of blocks, 1 is the number of threads per block and d,e,f are the arguments */
    arradd<<<6, 1>>>(d, e, f);

    /* Here we are copying content from GPU(Device) to CPU(Host) */
    cudaMemcpy(c, f, 6 * sizeof(int), cudaMemcpyDeviceToHost);

    printf("\nSum of two arrays:\n ");
    for (i = 0; i < 6; i++)
    {
        printf("%d\t", c[i]);
    }

    /* Free the memory allocated to pointers d,e,f */
    cudaFree(d);
    cudaFree(e);
    cudaFree(f);

    return 0;
}