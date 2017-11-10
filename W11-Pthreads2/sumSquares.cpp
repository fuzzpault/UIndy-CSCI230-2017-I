/*                                                                                                                     
  Name: Paul Talaga
  Date: Oct 30, 2017
  Desc: This probram finds the sum of squares from 0 to 100000000,
        it is used to verify the threaded fast version (sumSquaresFast) 
        is correct.
    
        Compile: g++ -O3 sumSquares.cpp      (With full optimizations enabled)
        Time: time ./a.out
*/

#include <iostream>

using namespace std;

const unsigned long MAX = 100000000;

int main(){
    unsigned long long sum = 0;

    for(unsigned long long i = 0; i <= MAX; i++){
      sum += i * i;
    }
    
    cout << "Sum of squares from 0 to " << MAX << endl;
    cout << "Sum: " << sum << endl;
    
    return 0;

}
