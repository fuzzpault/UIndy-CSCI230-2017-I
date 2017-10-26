#include <iostream>
#include <assert.h>

using namespace std;


int main(){
  int message = 0;
  int key = 0;
  cout << "Give me your message as an int" << endl;
  cin >> message;
  cout << "What is the key?" << endl;
  cin >> key;
  cout << "Answer: " <<(int)( message ^ key) << endl;

  return 0;

}
