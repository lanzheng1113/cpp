#include <iostream>
using namespace std;

// unexpected effects of type promotion in overload resolution
void do_something(short arg)
{
    cout << "Doing something with a short" << endl;
}
 
void do_something(int arg)
{
    cout << "Doing something with an int" << endl;
}
 
int main(int argc, char **argv)
{
    short val = 12;
 
    do_something(val); // Prints "Doing something with a short"
    do_something(val * val); // Prints "Doing something with an int"
}
