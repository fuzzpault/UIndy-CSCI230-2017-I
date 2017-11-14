/*                                                                                                                     
  Name: Paul Talaga
  Date: Nov 14, 2017
  Desc: Demo of how to limit a program to running for a set time.
*/

#include <iostream>
#include <sys/time.h>
#include <cstdlib>

using namespace std;

// Convenience function to get the current time as a double.
double getTimeAsDoubleSeconds(){
  struct timeval now;
  gettimeofday(&now, NULL);
  return (double)now.tv_sec + (double)now.tv_usec / 1000000.0;
}

int main(){

  double start = getTimeAsDoubleSeconds();

  cout << "Running for 4 seconds..." << endl;
  while(true){

    cout << ".";

    // If the time from 'start' till now is more than 4 seconds, exit the loop.
    if(getTimeAsDoubleSeconds() - start > 4){
      break;
    }

  }

}
