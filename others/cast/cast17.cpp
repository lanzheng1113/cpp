// 当使用子类对基类进行初始化或者赋值时  存在子类引用到基类引用的转换
// 然后使用基类带一个基类const引用形参的复制构造函数或者赋值操作符函数进行基类对象的构造
#include <iostream>
using namespace std;

class Foo {
public:
    Foo(){}
    Foo(const Foo& x) { cout << "Foo copy ctor called." << endl;}
    Foo& operator=(const Foo& x) { cout<< "Foo assignment operator called." << endl; return *this;}
};

class Bar : public Foo {
};

int main() {
  Bar bar1,bar2;
  Foo foo1(bar1); // direct-initialization calls Foo copy ctor
  Foo foo2 = bar1; // copy-initialization  calls Foo copy ctor 
  
  foo2 = bar2;  // calls Foo assignment operator
}
