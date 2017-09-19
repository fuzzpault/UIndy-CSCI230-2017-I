/*  Author: Paul Talaga
    Date: Sept 18, 2017
    Desc: Some demonstrations of issues with using floats
          and doubles in C/C++.
 */

#include <iostream>
#include <cmath>

using namespace std;

int main(){
  float a = 3000000000000000.0;
  float b = 0.000000002;
  cout << "a: " << a << endl;
  cout << "b: " << b << endl;
  cout << "(a - a) + b: " << (a - a) + b << endl;
  cout << "a + (b - a): " << a + (b - a) << endl;

  float first = (a - a) + b;
  float second = a + (b - a);


  // Bad way to compare floats
  if(first == second){
    cout << "first == second" << endl;
  }else{
    cout << "first != second" << endl;
  }

  // Better way to compare floats:
  if(abs(first - second) < 0.0001){
    cout << "abs same" << endl;
  }else{
    cout << "abs diff" << endl;
  }

  // More bad stuff with floats
  float d = 1.0/5;
  cout << "d * 5 = " << (d * 5.0 == 1.0) << endl;

  float e = 1.0 / 3;
  cout << "e * 3 = " << (e * 3.0 == 1.0) << endl;

  return 0;
}
