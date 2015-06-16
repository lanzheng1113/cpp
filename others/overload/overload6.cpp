// will not inherit base class private member
#include <iostream>
using namespace std;

struct Base
{
private:
    void foo(float) {}
};

struct Derived: public Base
{
public:
    void foo(int x)
    {
      cout << "Derived:foo: " << x << endl;
    }
    
};

int main()
{
    Derived d;
    d.foo(5.0f);
}
