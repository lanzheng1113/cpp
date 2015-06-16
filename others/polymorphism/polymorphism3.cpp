// pure virtual members can be called
// from the abstract base class
#include <iostream>
using namespace std;

class Polygon {
  protected:
    int width, height;
  public:
    void setValues (int a, int b)
      { width=a; height=b; }
    virtual int area() const =0;
    void printarea()
      { cout << this->area() << '\n'; }
};

class Rectangle: public Polygon {
  public:
    int area (void) const
      { return (width * height); }
};

class Triangle: public Polygon {
  public:
    int area (void) const
      { return (width * height / 2); }
};

int main () {
  Rectangle rect;
  Triangle trgl;
  Polygon * ppoly1 = &rect;
  Polygon * ppoly2 = &trgl;
  ppoly1->setValues (4,5);
  ppoly2->setValues (4,5);
  ppoly1->printarea();
  ppoly2->printarea();
  return 0;
}
