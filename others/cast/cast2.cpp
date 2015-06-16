// from: http://stackoverflow.com/questions/2253168/dynamic-cast-and-static-cast-in-c
#include <iostream>
#include <stdlib.h>  // srand rand
using namespace std;

class Base
{
public:
    virtual void DoIt() = 0;    // pure virtual
    virtual ~Base() {};
};

class Foo : public Base
{
public:
    virtual void DoIt() { cout << "Foo" << endl; }; 
    void FooIt() { cout << "Fooing It..." << endl; }
};

class Bar : public Base
{
public :
    virtual void DoIt() { cout << "Bar" << endl; }
    void BarIt() { cout << "baring It..." << endl; }
};

Base* CreateRandom()
{
    if( (rand()%2) == 0 )
        return new Foo;
    else
        return new Bar;
}


int main()
{
    for( int n = 0; n < 10; ++n )
    {
        Base* base = CreateRandom();

        base->DoIt();
        /* unsafe way to make cast
        Bar* bar = (Bar*)base;
        bar->BarIt();
        */
        // use dynamic_cast
        Bar *bar = dynamic_cast<Bar*>(base);
        Foo *foo = dynamic_cast<Foo*>(base);
        if(bar)
          bar->BarIt();
        if(foo)
          foo->FooIt();    
    }
    return 0;
}
