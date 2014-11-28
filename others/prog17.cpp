#include <iostream>
#include <typeinfo>
#include <exception>
using std::cout;
using std::exception;
//typeid¾ÙÀý
class Base { virtual void f(){} };
class Derived : public Base {};

int main()
{
  int * a,b;
  a=0; b=0;
  if (typeid(a) != typeid(b))
  {
    cout << "a and b are of different types:\n";
    cout << "a is: " << typeid(a).name() << '\n';
    cout << "b is: " << typeid(b).name() << '\n';
  }
  try 
  {
    Base* a = new Base;
    Base* b = new Derived;
    cout << "a is: " << typeid(a).name() << '\n';
    cout << "b is: " << typeid(b).name() << '\n';
    cout << "*a is: " << typeid(*a).name() << '\n';
    cout << "*b is: " << typeid(*b).name() << '\n';
  } 
  catch (exception& e) 
  { 
	  cout << "Exception: " << e.what() << '\n'; 
  }
  return 0;
}
