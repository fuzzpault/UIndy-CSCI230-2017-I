/*                                                                                                                    
  Name: Paul Talaga
  Date: Dec 5, 2017
  Desc: Program to add two arrays using the GPU
        It uses multiple threads and multiple blocks, so this is
        as fast it can go.

  To compile this, do: nvcc add-blockthreads.cu 
*/

#include <iostream>

using namespace std;

#define numThreads 32 // upper limit of 1024
#define numBlocks 1000


// CUDA kernel function to add to arrays element by element
// This isn't a great demonstration because there isn't much
// work for this function to do, so you'll likely not see
// a big speedup over the CPU.
__global__
void add(int size, int* x, int* y, int* z){
    //threadIdx.x
    //blockIdx.x
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x; // gridDim is numThreads
    for(int i = index; i < size; i+= stride){
        z[i] = x[i] + y[i];
    }
}

int main(void){
    
    // Size of the arrays we'll be adding
    const unsigned N = 10000000;
    
    cout << "Size: " << N*3*sizeof(int) / 1024 / 1024 << " MB" << endl;
    
    // To used unified memory (CUDA takes care of data movement)
    // all memory must be allocated via the cudaMallocManaged call below.
    int* x;
    int* y;
    int* z;
    
    cudaMallocManaged(&x, N * sizeof(int));
    cudaMallocManaged(&y, N * sizeof(int));
    cudaMallocManaged(&z, N * sizeof(int));
    
    // Fill the arrays with numbers
    for(int i = 0; i < N; i++){
        x[i] = i;
        y[i] = 2 * i;
    }
    
    // Call the add function, with 1 block, and 1 thread
    add<<<numBlocks,numThreads>>>(N, x, y, z);
    
    // Wait until the device is done before proceeding, otherwise we'd be
    // accessing x, y, and z in the loop below before the add function completes
    // on the device.
    cudaDeviceSynchronize();
    
    // Check to see if the math is correct
    int errors = 0;
    for(int i = 0; i < N; i++){
        if(z[i] != x[i] + y[i]){
            cout << i << " did not add correctly!" << endl;
            errors++;
        }
    }
    if(!errors)cout << "All good!" << endl;
    
    return 0;
}