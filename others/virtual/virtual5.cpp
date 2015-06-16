/*example of calling virtual function in  subclass from superclass*/
#include <iostream>
using namespace std;

class A {
public:
    void foo() { cout << "A::foo "; bar(); }
protected: 
   virtual void bar() { cout << "A::bar" << endl; }
};

class B1 : public A {
};

class B2 : public A {
private:
    virtual void bar() { cout << "B2::bar" << endl; }
};

class C : public B2 {
private:
    virtual void bar() { cout << "C::bar" << endl; }
};

int main()
{   
    A  a;
    B1 b1;
    B2 b2;
    C   c;

    A* p = &a;
    cout << "visit A: ";
    p->foo();
    
    p = &b1;
    cout << "visit B1: ";
    p->foo();

    p = &b2;
    cout << "visit B2: ";
    p->foo();

    p = &c;
    cout << "visit C: ";
    p->foo();
   
    return 0;
   
}
