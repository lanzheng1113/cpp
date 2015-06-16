/* Example to demonstrate the working of virtual function in C++ programming. */

#include <iostream>
using namespace std;
class B
{
    public:
     virtual void display()      /* Virtual function */
         { cout<<"Content of base class.\n"; }
};

class D1 : public B
{
    public:
       void display()
         { cout<<"Content of first derived class.\n"; }
};

class D2 : public B
{
    public:
       void display()
         { cout<<"Content of second derived class.\n"; }
};

int main()
{
    B *b;
    B  b1;
    D1 d1;
    D2 d2;
    
    b = &b1;
    b->display();  /* calls dispaly() of class B */  

    b = &d1;
    b->display();   /* calls display() of class derived D1 */

    b = &d2;           
    b->display();   /* calls display() of class derived D2 */
    return 0;
}
