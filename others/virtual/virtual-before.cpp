#include <iostream>

// before we implement method as virtual
class Animal {
public:
  void eat() { std::cout << "I'm eating generic food." << std::endl;}
};

class Cat : public Animal {
public:
  void eat() { std::cout << "I'm eating a rat." << std::endl;;}
};

// an intermediate function
void func(Animal* p) { p->eat();}

int main() {
  Animal *animal = new Animal;
  Cat *cat = new Cat;
  func(animal);
  func(cat);
}
