// overload not working
#include <iostream>
#include <string>

using namespace std;

struct Base
{
    void foo(int x) const
    {
       cout << "Base::foo" << x << endl;
    }
};

struct Derived : public Base
{
    void foo(const std::string& s) 
     {
        cout << "Derived:foo" << s << endl;
     }
};


int main()
{
    Derived d;
    d.foo("abc");
    d.foo(123); // Will not compile! Base::foo is hidden!
}
