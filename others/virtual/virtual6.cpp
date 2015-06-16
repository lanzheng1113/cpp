#include <iostream>

class Base {
public:
  void method1() { std::cout << "Base::method1" << std::endl;}
  virtual void method2() { std::cout << "Base::method2" << std::endl;}
};

class Derived : public Base {
public:
  void method1() { std::cout << "Derived::method1" << std::endl;}
  void method2() { std::cout << "Derived::method2" << std::endl;}
};

int main() {
 //  Note - constructed as Derived, but pointer stored as Base*
 Base* obj = new Derived();
 
 obj->method1(); // print "Base::method1"
 obj->method2(); // print "Derived::method2"
}
