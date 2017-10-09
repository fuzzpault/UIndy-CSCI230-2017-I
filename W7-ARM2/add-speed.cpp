#include <iostream>

using namespace std;

#define TIMES 100000

int add4asm(int a, int b, int c, int d){
  //return a + b + c + d;
  int result;
  asm volatile("ldr %0, [%1] \n"
	       "ldr r6, [%2] \n"
	       "ldr r7, [%3] \n"
	       "ldr r8, [%4] \n"
	       "add %0, %0, r6 \n"
	       "add %0, %0, r7 \n"
	       "add %0, %0, r8 \n"
	       : "=r" (result)
	       : "r" (&a), "r" (&b), "r" (&c), "r" (&d)
	       );
  return result;
}

int add4(int a, int b, int c, int d){
  return a + b + c + d;
}

int main(){
  int a = 5;
  int b = 6;
  int c = 9;
  int d = 10;
  int sum = a + b + c + d;
  
  clock_t start = clock();
  for(int i = 0; i < TIMES; i++){
    if(add4asm(a,b,c,d) != sum){
      cout << "add4asm error! " << add4asm(a,b,c,d) << " " << sum <<  endl;
      break;
    }
  }
  clock_t end1 = clock();
  for(int i = 0; i < TIMES; i++){
    if(add4(a,b,c,d) != sum){
      cout << "add4 error!" << endl;
      break;
    }
  }
  clock_t end = clock();

  cout << "  C: " << (float)(end - end1) / (float)CLOCKS_PER_SEC << endl;
  cout << "acm: " << (float)(end1 - start) / (float)CLOCKS_PER_SEC << endl;

}
