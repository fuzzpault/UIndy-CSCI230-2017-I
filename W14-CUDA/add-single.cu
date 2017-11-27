/*                                                                                                                    
  Name: Paul Talaga
  Date: Nov 27, 2017
  Desc: Program to add two arrays using the GPU
        Only 1 thread in 1 block, so this will NOT be fast, 
        but it is using the GPU

  To compile this, do: nvcc add-single.cu 
*/

#include <iostream>

using namespace std;

// CUDA kernel function to add to arrays element by element
// This will add all elements in the array in 1 call.
__global__
void add(int size, int* x, int* y, int* z){
    for(int i = 0; i < size; i++){
        z[i] = x[i] + y[i];
    }
}

int main(){
    
    // Size of the arrays we'll be adding
    const unsigned N = 100;
    
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
    add<<<1,1>>>(N, x, y, z);
    
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