/* Name: Paul Talaga
   Date: 9/16/2016
   Desc: Testing program for cbitslib.cpp.
*/

#include <iostream>
#include <cassert>

#include "cbitslib.cpp"

using namespace std;

int main(){

  // Is the integer zero?
  assert(isZero(0));
  assert(!isZero(89));
  assert(!isZero(-1));
  assert(!isZero(-3));


  // Integer is negative?
  assert(isNegative(-5));
  assert(isNegative(-10));
  assert( !isNegative(10));
  assert( !isNegative(0));

  // Mult by 2
  assert(multBy2(3,1) == 6);
  assert(multBy2(4,3) == 32);
  assert(multBy2(5,4) == 40);

  // Bit set checks
  long set = 0x0;
  assert( ! contains(set, 5) );
  set = insert(set, 5);
  assert( contains(set, 5) );
  assert( ! contains(set, 10));
  set = insert(set, 5);
  assert( contains(set, 5) );
  set = insert(set,10);
  set = insert(set, 9);
  assert( contains(set, 9) );
  
  long set2 = 0x0;
  set2 = insert(set2, 9);
  set2 = insert(set2, 2);

  long set3 = join(set, set2);
  assert( contains(set3, 9) );
  assert( contains(set3, 2) );
  set3 = subtract(set, set2);
  assert( !contains(set3, 9) );
  assert( contains(set3, 10) );
  assert( !contains(set3, 2) );

  set = remove(set,10);
  assert( contains(set, 9) );
  assert( !contains(set, 10) );
  set = remove(set, 11);
  assert( !contains(set,11));

  assert( contains(set,30) == 0x0);

  cout << "Success!\n";
  
  return 0;
}
