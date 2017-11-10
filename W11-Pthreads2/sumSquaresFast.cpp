/*                                                                                                                     
  Name: Paul Talaga
  Date: Nov 7, 2017
  Desc: Program to demonstrate the use of pthreads
        This finds the sum of all the squares from 0 to a 'large number', using 
	     multiple threads. More here.

      Compile: g++ -O3 sumSquaresFast.cpp -lpthread        (With full optimizations enabled)
      Time: time ./a.out
*/

#include <iostream>
#include <pthread.h>
#include <string>

using namespace std;

// Break the work up into many smaller batches, or range of numbers.  The only
// way to pass parameters to a thread is via a pointer to a struct containing
// the information, so the struct is defined here, with a start and ending values
// included.  thread_id and value

struct thread_data_t{
  int thread_id;
  unsigned long long start;
  unsigned long long end;
};

unsigned long long total;   // Will store the total sum calculated by each thread.

pthread_mutex_t lock;       // Global lock mutex so only 1 thread can modify total above.

void* doStuff(void* arg){
  thread_data_t* input;
  input = (thread_data_t*)arg;

  //  int thread_num = input->thread_id;  // Not used
  unsigned long long start = input->start;
  unsigned long long end = input->end;
  unsigned long long sum = 0;
  for(unsigned long long i = start; i <= end; i++){
    sum += i * i;
  }
  pthread_mutex_lock(&lock);    // Make sure only 1 thread is updating the shared variable total.
  total += sum;
  pthread_mutex_unlock(&lock);
  
}


const int NUM_THREADS = 6;
const unsigned long MAX = 100000000;
int main(){

  total = 0;

  thread_data_t passed[NUM_THREADS];
  pthread_t threads[NUM_THREADS];

  pthread_mutex_init(&lock, NULL);
  
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for(int i = 0; i < NUM_THREADS; i++){
    passed[i].thread_id = i;
    // So we cover all the values, make all ranges equally-sized, except allow the 
    // last to be large if there was a non-even division.
    if(i < NUM_THREADS -1){
      passed[i].start = (MAX / NUM_THREADS) * i + 1;
      passed[i].end = (MAX / NUM_THREADS) * (i + 1) ;
    }else{
      passed[i].start = (MAX / NUM_THREADS) * i + 1;
      passed[i].end = MAX;
    }
    pthread_create(&threads[i], &attr, doStuff, (void*)&passed[i]);
  }

  // Wait for all threads to be done.
  for(int i = 0; i < NUM_THREADS; i++){
    pthread_join(threads[i], NULL);
    // cout << "Thread " << i << " done." << endl;  // This slows it down, so don't print!
  }

  cout << "Sum is: " << total << endl;
  pthread_attr_destroy(&attr);

  pthread_mutex_destroy(&lock);
  
  return 0;

}
