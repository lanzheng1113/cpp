#include<iostream>
// 说明explicit构造函数的例子
class MyString {
public:
      MyString(int n);
      MyString(const char*p);
}

int main() {

    MyString str = 'x';
    std::cout << str << std::endl;
}
