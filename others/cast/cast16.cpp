// slicing obejct example  when pass subclass to baseclass by value
#include <iostream>
using namespace std;
 
class Base
{
protected:
    int i;
public:
    Base(int a)     { i = a; }
    Base(const Base& b):i(b.i) { cout << "calls Base copy ctor" << endl;}
    virtual void display()
    { cout << "I am Base class object, i = " << i << endl; }
};
 
class Derived : public Base
{
    int j;
public:
    Derived(int a, int b) : Base(a) { j = b; }
    virtual void display()
    { cout << "I am Derived class object, i = "
           << i << ", j = " << j << endl;  }
};
 
// Global method, Base class object is passed by value
void somefuncByVal (Base obj)
{
    obj.display();
}

// Global method, Base class object is passed by reference
void somefuncByRef (Base &obj)
{
    obj.display();
} 

// Global method, Base class object is passed by pointer
void somefuncByPtr (Base *obj)
{
    obj->display();
} 

int main()
{
    Base b(33);
    Derived d(45, 54);
   
    cout << "pass-by-value:" << endl; 
    somefuncByVal(b);
    somefuncByVal(d); // Object Slicing, the member j of d is sliced off
    
    cout << endl << "pass-by-reference:" << endl;    
    somefuncByRef(b);
    somefuncByRef(d);  // No Object Slicing
    
    cout << endl << "pass-by-pointer:" << endl;
    somefuncByPtr(&b);
    somefuncByPtr(&d); // No Object Slicing

    return 0;
}
