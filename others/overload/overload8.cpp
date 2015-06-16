struct Base {
  virtual void foo(){}
  virtual void foo(int){}
  virtual void bar(){}
};

struct Derived: Base {
 virtual void foo(){}
};

int main() {
  Derived d;
  d.foo(1); // Error foo(int) is hidden
  d.bar();  // Fine calls Base::bar()
}
