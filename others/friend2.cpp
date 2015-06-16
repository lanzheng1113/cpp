// friend class example

#include <iostream>
using namespace std;

class Square;

class Rectangle {
private:
   int width,height;
public:
   int area() const {
   	return width*height;
   }
   void convert(Square a);
};

class Square {
 friend class Rectangle; // friend class declaration
 private:
   int side;
 public:
    Square(int a):side(a){}
};

void Rectangle::convert(Square a) {
    width = a.side;
    height = a.side;
}

int main() {
 Rectangle rect;
 Square sqr(4);
 rect.convert(sqr);
 cout << rect.area() << std::endl;
 return 0;
}
