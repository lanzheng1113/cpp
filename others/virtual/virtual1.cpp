#include <iostream>
using namespace std;
class B
{
    public:
       void display()
         { cout<<"Content of base class.\n"; }
};

class D : public B
{
    public:
       void display()
         { cout<<"Content of derived class.\n"; }
};

int main()
{
    B *b;
    D d;
    b->display();

    b = &d;    
    b->display();	// 因为基类display没有使用virtual关键字声明  不会产生多态调用 
    return 0;
}
