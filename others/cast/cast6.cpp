#include <iostream>
int main() {
 char c = 10;
 int *p = (int*)&c; //C-style cast convert 1 byte char address to 4 byte address
 *p = 5; 
 std::cout << *p << std::endl;// run-time error
}
