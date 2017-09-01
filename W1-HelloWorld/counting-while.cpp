/*  Program to find the sum of numbers between two given integers given
    as program parameters.
    Paul Talaga
    Sept. 2017                                                                              
*/

#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]){
  if(argc < 3){
    cout << " I need 2 numbers you idiot!" << endl;
    return 0;
  }
  //argv[0] ./a.out
  //argv[1] = "10"
  //argv[2] = "1000"
  unsigned int sum = 0;
  unsigned i = atoi(argv[1]);
  // By creating a new variable end (using more memory) we can get away
  // with running the atoi function once before the loop, rather than
  // in every loop itteration.  This gives a 100x speedup!
  unsigned end = atoi(argv[2]);
  while(i <= end){
    //cout << i << " ";
    sum += i;
    i++;
  }
  cout << "sum: " << sum << endl;

  return 0;
}
