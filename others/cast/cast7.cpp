#include <iostream>
int main() {
 char c = 10;
 int *p = static_cast<int*>(&c); // compile-time error 
 *p = 5; 
 std::cout << *p << std::endl;
}
