/*  Stuff here

 */
#include <iostream>
#include <string>

using namespace std;

template <typename T>
void printBits(T number){
  string ret = "";
  T thing = number;
  for(int i = 0; i < 8 * sizeof(T); i++){
    //cout << number % 2;
    ret = " "  + ret;
    //ret[0] = number % 2 + '0';
    ret[0] = (number & 1) + '0';
    //number = number / 2;
    number = (int)number >> 1;
  }
  cout << thing << " : " << ret << endl;
}

int main(){
  printBits(0xFF);
  printBits(256);
  printBits(-2);
  printBits(-1);
  printBits(0);
  printBits(1);
  short a = 5;
  printBits(a);
  printBits(5.5);
}
