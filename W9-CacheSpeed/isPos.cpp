#include <iostream>
#include <assert.h>

using namespace std;

bool isPos(int a){
  return  !(a & 0x80000000);
}

bool isEven(int a){
  return !(a & 0x01);
}

bool contains(unsigned data, unsigned char element){
  return data & (0x1 << element);
}

int main(){
  assert(isPos(5));
  assert(isPos(2));
  assert(isPos(0));
  assert(!isPos(-3));
  assert(!isPos(-8));
  assert(isPos(123456789));

  assert(!isEven(5));
  assert(isEven(2));
  assert(isEven(0));
  assert(!isEven(-3));
  assert(isEven(-8));
  assert(!isEven(123456789));

  assert(!contains(0xaaaaaaaa,0));
  assert(contains(0xaaaaaaaa,1));
  assert(!contains(0xaaaaaaaa,2));
  
  cout << "Success!" << endl;
  
  return 0;
}
