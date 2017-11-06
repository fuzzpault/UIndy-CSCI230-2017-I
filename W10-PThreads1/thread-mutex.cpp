/*                                                                                                                     
  Name: Paul Talaga
  Date: Oct 30, 2017
  Desc: Program to demonstrate the use of pthreads
        This reads and writes to a shared variable (without any semaphore or lock)
	to show how, using threads, an incorrect result could be observed.  You
	may need to run this multiple times to see an incorrect temp value.

  To compile this, do: g++ -lpthread thread1.cpp
*/

#include <iostream>
#include <pthread.h>
#include <string>

using namespace std;

struct thread_data_t{
  int thread_id;
  int value;
};

int temp;
pthread_mutex_t lock;

void* doStuff(void* arg){
  thread_data_t* input;
  input = (thread_data_t*)arg;

  int thread_num = input->thread_id;
  int v = input->value;
  // To increase the likelyhood of an incorrect calculation of a shared variable, we do it a lot!
  pthread_mutex_lock(&lock); 
  for(int i = 0; i < 10000 ; i++){
    //pthread_mutex_lock(&lock);
    temp++;
    //pthread_mutex_unlock(&lock);
  }
  pthread_mutex_unlock(&lock);
  //cout << "Thread #: " << thread_num << " value: " << v << " temp " << temp << endl;

}


const int NUM_THREADS = 100;
int main(){

  temp = 0;

  thread_data_t passed[NUM_THREADS];
  pthread_t threads[NUM_THREADS];

  pthread_mutex_init(&lock, NULL);
  
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for(int i = 0; i < NUM_THREADS; i++){
    passed[i].thread_id = i;
    passed[i].value = 55;
    pthread_create(&threads[i], &attr, doStuff, (void*)&passed[i]);
  }


  for(int i = 0; i < NUM_THREADS; i++){
    pthread_join(threads[i], NULL);
    //cout << "Thread " << i << " done." << endl;
  }

  cout << "temp (should be 30000): " << temp << endl;
  pthread_attr_destroy(&attr);

  pthread_mutex_destroy(&lock);
  
  return 0;

}
