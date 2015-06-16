#include <iostream>

void print(int *p) // take a non-const pointer but not modify data
{
   std::cout << *p << std::endl;
}

int main() {
 const int myConst = 5;
 int *nonConst = const_cast<int*>(&myConst);
 
 //print(&myConst); // error: can not convert const int* to int*
 print(nonConst); // ok
 
 *nonConst = 10 ; // undefined behavior 
 std::cout << myConst << std::endl;
}
