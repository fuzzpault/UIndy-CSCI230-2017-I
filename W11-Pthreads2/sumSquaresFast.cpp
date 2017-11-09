/*                                                                                                                     
  Name: Paul Talaga
  Date: Nov 7, 2017
  Desc: Program to demonstrate the use of pthreads
        This finds the sum of all the squares from 0 to a 'large number', using 
	multiple threads. More here.

  To compile this, do: g++ -lpthread thread1.cpp
*/

#include <iostream>
#include <pthread.h>
#include <string>

using namespace std;

struct thread_data_t{
  int thread_id;
  int value;
  unsigned long long start;
  unsigned long long end;
};

unsigned long long temp;
pthread_mutex_t lock;

void* doStuff(void* arg){
  thread_data_t* input;
  input = (thread_data_t*)arg;

  int thread_num = input->thread_id;
  int v = input->value;
  unsigned long long start = input->start;
  unsigned long long end = input->end;
  //cout << start << " ->  " << end << endl;
  unsigned long long sum = 0;
  for(unsigned long long i = start; i <= end; i++){
    sum += i * i;
  }
  pthread_mutex_lock(&lock);
  temp += sum;
  pthread_mutex_unlock(&lock);
  
}


const int NUM_THREADS = 30;
const unsigned long MAX = 100000000;
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
    if(i < NUM_THREADS -1){
      passed[i].start = (MAX / NUM_THREADS) * i + 1;
      passed[i].end = (MAX / NUM_THREADS) * (i + 1) ;
    }else{
      passed[i].start = (MAX / NUM_THREADS) * i + 1;
      passed[i].end = MAX;
    }
    pthread_create(&threads[i], &attr, doStuff, (void*)&passed[i]);
  }


  for(int i = 0; i < NUM_THREADS; i++){
    pthread_join(threads[i], NULL);
    cout << "Thread " << i << " done." << endl;
  }

  cout << "sum is: " << temp << endl;
  pthread_attr_destroy(&attr);

  pthread_mutex_destroy(&lock);
  
  return 0;

}
