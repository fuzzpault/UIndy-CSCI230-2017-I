/*                                                                                                                     
  Name: Paul Talaga
  Date: Oct 30, 2017
  Desc: Program to demonstrate the use of pthreads
        This reads and writes to a shared variable with a lock around the critical 
	section so no two threads update the variable at the same time.  This is 
	SLOW as only one thread can execute their loop at a time, but at least it is
	correct.  Bad threading implementation!

  To compile this, do: g++ -lpthread thread1.cpp
*/

#include <iostream>
#include <pthread.h>

using namespace std;

int main(){
    unsigned long long sum = 0;

    for(unsigned long long i = 0; i <= 100000000; i++){
      unsigned long long pre = sum;
      sum += i * i;
    }
    
    cout << "Sum: " << sum << endl;
    
    return 0;

}
