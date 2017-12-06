/*                                                                                                                    
  Name: Paul Talaga
  Date: Dec 1, 2017
  Desc: Program to add two arrays using the GPU
        Multiple threads but 1 block, so this will NOT be superfast, 
        but it is using the GPU.

  To compile this, do: nvcc add-thread.cu 
*/

#include <iostream>

using namespace std;

#define numThreads 32 // Max is 1024


// CUDA kernel function to add to arrays element by element
// This will add some of the elements in the array, but over
// all threads the entire array will be computed.
__global__
void add(int size, int* x, int* y, int* z){
    //threadIdx.x
    //blockIdx.x
    int index = threadIdx.x;
    int stride = gridDim.x; // gridDim is numThreada
    for(int i = index; i < size; i+= stide){
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