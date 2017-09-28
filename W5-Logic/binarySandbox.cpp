/*  Name: Paul Talaga
    Date: Sept 28, 2017
    Desc: Example for bit-wise operations with use of a bit-printing function.

 */
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <iomanip>

using namespace std;

template <typename T>
void printBits(T number){
  string ret = "";
  // Copy the bits into a char array so we can look at floats
  char* buf = (char*)malloc(sizeof(T));
  memcpy(buf, &number, sizeof(T));

  for(int j = 0; j < sizeof(T); j++){
    for(int i = 0; i < 8; i++){
      //cout << number % 2;
      ret = " "  + ret;
      //ret[0] = number % 2 + '0';
      ret[0] = (buf[j] & 1) + '0';
      //number = number / 2;
      buf[j] = buf[j] >> 1;
    }
    ret = ret + " ";
  }

  cout << setw(5) << number  << " : " << ret << endl;

  free(buf);
}

int main(){
  
  printBits(0xFF);
  printBits(256);
  printBits(-2);
  printBits(-1);
  printBits(0);
  printBits(1);
  printBits((float)0.5);
  printBits((double)0.5);

  // Bitwise operation examples.
  char a = 34;
  char b = 231;
  printBits(a);
  printBits(b);
  printBits((char)(a & b));
  printBits((char)(a | b));
  printBits((char)(a && b));
  printBits((char)(a || b));
  //printBits(5.5);
}
