#include <iostream>
#include <string>

struct Person {
   std::string name;
   Person(std::string n):name(n){}
};
// should return a reference to std::ostream
std::ostream operator<<(std::ostream& s,const Person &p) {
  s << p.name;
  return s;
}

int main() {
   Person p(std::string("Tom"));
   std::cout<<p<<std::endl;
}

