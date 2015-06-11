#include <iostream>
class Foo
{
public:
  // single parameter constructor, can be used as an implicit conversion
  Foo (int foo) : m_foo (foo) 
  {
     std::cout << "constructor called. " << std::endl;
  }

  int GetFoo () { return m_foo; }

private:
  int m_foo;
};
void DoBar (Foo foo)
{
  int i = foo.GetFoo ();
  std::cout << i << std::endl;
}
int main() {
  DoBar(42);
}
