/*example of calling virtual function in  subclass from superclass*/
#include <iostream>
using namespace std;

class A {
public:
    void foo() { cout << "A::foo "; bar(); }
    virtual void bar() { }
};

class B : public A {
public:
    virtual void bar() { cout << "B::bar" << endl; }
};

class C : public B {
public:
    virtual void bar() { cout << "C::bar" << endl; }
};

int main()
{
    B* c = new C();
    c->foo();
    delete c;
    return 0;
}
