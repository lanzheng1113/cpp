// implicit conversion can only do once

#include <iostream>
using namespace std;

class Class2;

class Class1 {
public:
  Class1(Class2);
};

class Class2{
public:
  Class2(int e) { cout << "Class2 int-ctor" << endl;}
};

Class1::Class1(Class2 x) { cout << "Class1 Class2-ctor" << endl;}
void doThing(Class1 x) { cout << "do thing" << endl;}

int main() {
  //doThing(5); // error: implicit conversion only do once
  doThing(Class2(5)); // ok
}
