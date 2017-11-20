/*                                                                                                                    
  Name: Paul Talaga
  Date: Nov 16, 2017
  Desc: Program to simulate as many rolls of 2 die as possible using multiple threads
        running for a specified number of seconds.

  To compile this, do: g++ rollDieTime.cpp -lpthread
*/

#include <iostream>
#include <pthread.h>
#include <string>
#include <cstdlib>
#include <sys/time.h>

using namespace std;

int numberCounts[13];
pthread_mutex_t lock;

double start;
double running_time;

// Convenience function to get the current time as a double.
double getTimeAsDoubleSeconds(){
  struct timeval now;
  gettimeofday(&now, NULL);
  return (double)now.tv_sec + (double)now.tv_usec / 1000000.0;
}

long unsigned int rand(long unsigned int &seed){
  long unsigned int hi, lo;
  lo = 16807 * (seed & 0xFFFF);
  hi = 16807 * (seed >> 16);

  lo += (hi & 0x7FFF) << 16;
  lo += (hi >> 15);

  if (lo > 0x7FFFFFFF) lo -= 0x7FFFFFFF;

  return (seed = (long) lo);
}

int rollDie(long unsigned int &seed){
  int die1 = (rand(seed) % 6) + 1;
  int die2 = (rand(seed) % 6) + 1;
  return die1 + die2;
}

void simulateDie(int rolls){
  long unsigned int seed = rand();
  int internalCounts[13];
  for(int i = 0; i < 13; i++){
    internalCounts[i] = 0;
  }

  //for(int i = 0; i < rolls; i++){
  while(true){
    int number = rollDie(seed);
    internalCounts[number]++;
    if(getTimeAsDoubleSeconds() - start > running_time){
      break;
    }
  }

  pthread_mutex_lock(&lock);
  for(int i = 0; i < 13; i++){
    numberCounts[i] += internalCounts[i];
  }
  pthread_mutex_unlock(&lock);
}



void* doStuff(void* arg){
  
  simulateDie(4000000);
  // To increase the likelyhood of an incorrect calculation of a shared variable, we do it a lot!
  /* pthread_mutex_lock(&lock); 
  for(int i = 0; i < 10000 ; i++){
    //pthread_mutex_lock(&lock);
    //temp++;
    //pthread_mutex_unlock(&lock);
  }
  pthread_mutex_unlock(&lock);
  //cout << "Thread #: " << thread_num << " value: " << v << " temp " << temp << endl;
 */
}


const int NUM_THREADS = 10;
int main(){

  srand(time(0));
  // zero out the number counts array

  cout << "How long should I compute for?" << endl;
  cin >> running_time;
  start = getTimeAsDoubleSeconds();

  
  for(int i = 0; i < 13; i++){
    numberCounts[i] = 0;
  }

  /*simulateDie(20000000);

  int total_throws = 0;
  for(int i = 0; i < 13; i++){
    total_throws += numberCounts[i];
  }

  cout << "Total throws: " << total_throws << endl;
  // print out numbers
  for(int i = 0; i < 13; i++){
    cout << i << " : " << (double)numberCounts[i] * 100 / total_throws << " %" << endl;
  }

  return 0; */


  pthread_t threads[NUM_THREADS];

  pthread_mutex_init(&lock, NULL);
  
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for(int i = 0; i < NUM_THREADS; i++){
    pthread_create(&threads[i], &attr, doStuff, (void*)NULL);
  }


  for(int i = 0; i < NUM_THREADS; i++){
    pthread_join(threads[i], NULL);
    cout << "Thread " << i << " done." << endl;
  }

  pthread_attr_destroy(&attr);

  pthread_mutex_destroy(&lock);


  int total_throws = 0;
  for(int i = 0; i < 13; i++){
    total_throws += numberCounts[i];
  }

  cout << "Total throws: " << total_throws << endl;
  // print out numbers
  for(int i = 0; i < 13; i++){
    cout << i << " : " << (double)numberCounts[i] * 100 / total_throws << " %" << endl;
  }
   
  return 0;

}
