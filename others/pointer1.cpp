#include <iostream>
int main() {
    int a = 0;
    delete &a; // 段错误
    std::cout << a << std::endl;
}

