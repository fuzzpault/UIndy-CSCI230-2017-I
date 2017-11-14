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

  double start;
  start = getTimeAsDoubleSeconds();

  unsigned count = 0;

  cout << "Running for 4 seconds..." << endl;
  while(true){

    // Our 'work' is the count++ command, so by putting it in a loop
    // we do lots of work and rarely check the time.  This leads to much
    // more work being done as we are not constantly checking the time.
    // To see this effect, comment out the for and ending } so only
    // one count++ is executed per time check.
    // If this loop was too large then our program would run for too much
    // before knowing it needs to stop, so it can't be too large.
    // Test with 'time ./a.out' to see how close it gets.
    for(int i = 0; i < 100000; i++){
      count++;
    }

    if(getTimeAsDoubleSeconds() - start > 4){
      break;
    }
  }

  cout << "Count: " << count << endl;


}
