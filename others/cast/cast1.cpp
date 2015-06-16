#include <iostream>
using namespace std;

class Base {
public:
  Base() {};
  virtual  ~Base() {}; // make it polymorphic
};

template<class T>
class Derived: public Base {
  T _val;
public:
  Derived() {}
  Derived(T val): _val(val) {}
  T raw() {return _val;}
};

int main()
{
  Base * b = new Derived<int>(1);
  Derived<int> * d = dynamic_cast<Derived<int>* >(b);
  cout << d->raw() << endl;
  return 0;
}
