/* Name: <fill me in>
   Date: <fill me in>
   Desc: Functions for manipulating data at the bit/byte level.
*/
#include <cstring>
#include <stdlib.h>

using namespace std;

// ASSUME LITTLE-ENDIAN

template <typename myType>
void printBits(myType a){   // Thus any type thing can be printed
  // To get around the type conversion (which we don't want)
  // we copy the data into a char array and operate on it there.
  char* data = (char*)malloc(sizeof(myType));  // Create an array of characters (1 byte) the same size of the incoming thing
  memcpy(data, &a, sizeof(a));            // Copy the data into the array

  string ret = "";                        // Since we 'look' at the LSB first, we need to flip the order
  for(unsigned i = 0; i < sizeof(a);i++){
    ret = " " + ret;
    for(unsigned j = 0; j < 8; j++){
      if(data[i] & 1){                    // Is there a 1 in the LSB now?  %2 same
	ret =  "1" + ret;
      }else{
	ret = "0" + ret;
      }
      data[i] = data[i]>>1;               // Bit shift down by 1
    }
  }
  cout << a << " is " << sizeof(myType) << " bytes -> " << ret << endl;
}


// You may only use &, |, ~, ^, !, >>, << for ALL functions below, unless
// otherwise specified.
bool isZero(int a){
  // TODO Fix me
  return true;
}

bool isNegative(int a){
  // TODO Fix me
  return true;
}

unsigned short multBy2(int a, unsigned char amt){  // Returns a * 2^amt
  // TODO Fix me
  return 0;
}

long insert(long data, unsigned char value){  // Treat data as a set and insert value into it
  // TODO Fix me
  return 0;
}

bool contains(long data, unsigned char value){
  // TODO Fix me
  return true;
}

long remove(long data, unsigned char value){
  // TODO Fix me
  return 0;
}

long join(long data1, long data2){  // Should be called union, but that is a keyword
  // TODO Fix me
  return 0;
}

long subtract(long data1, long data2){
  // TODO Fix me
  return 0;
}
