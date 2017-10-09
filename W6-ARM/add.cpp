#include <iostream>

using namespace std;

int main(){
  int a = 5;
  int b = 10;
  int result = 0;
  
  asm volatile("add %0, %1, %2 \n"
	       "add %0, %0, #9 \n"
	       : "=r" (result)
	       : "r" (a), "r" (b)
	       );

  cout << "a: " << a << " b: " << b << " result: " << result << endl;
}
