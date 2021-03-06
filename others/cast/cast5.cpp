// dynamic cast example
struct A {
    virtual void f() { }
};
struct B : public A { };
struct C { };

int main() {
  A a;
  B b;

  A* ap = &b;
  B* b1 = dynamic_cast<B*> (&a);  // NULL, because 'a' is not a 'B'
  B* b2 = dynamic_cast<B*> (ap);  // 'b'
  C* c =  dynamic_cast<C*> (ap);   // NULL.

  A& ar = dynamic_cast<A&> (*ap); // Ok.
  B& br = dynamic_cast<B&> (*ap); // Ok.
  C& cr = dynamic_cast<C&> (*ap); // std::bad_cast
}
