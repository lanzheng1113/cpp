// 转换与继承的关系
#include <iostream>
#include <cassert>
using namespace std;
class Animal {
public:
   virtual void noiseMake(){ cout << "making generic noise" << endl; }
};

class Dog : public Animal {
public:
  void noiseMake() { cout << "dog bark..." << endl;}
};

class Cat : public Animal {
public:
  void noiseMake() { cout << "cat mew..." << endl;}
};

class Chiken : public Animal {
public:
 void noiseMake() { cout<< "chiken crow..." << endl;}
};

void makeNoise(Animal& animal) {
  animal.noiseMake();
}

int main() {
  Dog dog;
  Cat cat;
  // no cast required. Base class reference or pointer to subclass
  Animal& AnimalRef1 = dog;
  Animal& AnimalRef2 = cat;
  Animal* AnimalPtr1 = &dog;
  Animal* AnimalPtr2 = &cat;
  // error: std::bad_cast since AnimalRef1 is a dog
  // Cat& catRef1 = dynamic_cast<Cat&>(AnimalRef1);
 
  // NULL since AnimalPtr1 is a dog
  //Cat* catPtr1 = dynamic_cast<Cat*>(AnimalPtr1);
  //assert(catPtr1 != 0); // assertion will failed

  //ok
  Cat& catRef2 = dynamic_cast<Cat&>(AnimalRef2);
  Cat* catPtr2 = dynamic_cast<Cat*>(AnimalPtr2);
  
  Animal a;
  // these cast make no sense,since Animal is not a cat
  // Cat& catRef3 = dynamic_cast<Cat&>(a); // error : std::bad_cast
  // Cat* catPtr3 = dynamic_cast<Cat*>(&a);// NULL
  
  // this works. But is slices the cat part out and just
  // assigns the animal part of the object.
  Animal animal = cat;
   
  //Cat bigCat = animal; // make no sense, An animal is not a cat

  //Dog bigDog = bigCat; // make no sense,A cat is not a dog.

  Chiken chiken;
  makeNoise(dog);
  makeNoise(cat);
  makeNoise(chiken);   
}
