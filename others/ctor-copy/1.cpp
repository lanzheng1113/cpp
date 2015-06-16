// this example shows when copy-construtor and copy-assignment operator called.
#include <iostream>
using namespace std;

class Foo {
public:
  Foo() {
    cout << "ctor called." << endl;
  }
  Foo(const Foo& other) {
     cout << "copy ctor called." << endl;
  }    
  Foo& operator=(const Foo& other) {
     cout << "copy assignment operator called." << endl;
  }
};

void bar(Foo f) { cout << "function para by value" << endl;}


//By using the compiler option -fno-elide-constructors
//you can disable copy-elison and see that the copy-constructor would indeed be called in these situations.
Foo  bar() { 
  cout << "function return by value" << endl; 
  Foo tmp; // ctor called.
  return tmp;// copy ctor called.
}

int main() {
  Foo a; // ctor called.
  Foo b; // ctor called.
  
  a = b; // copy assignment operator called.
  Foo c(b); // copy ctor called.
  Foo d = b; // copy ctor called.
  
  bar(a); // copy ctor called: pass by value,as a local obejct created in stack
  bar(); // copy ctor called: return by value from function
}

