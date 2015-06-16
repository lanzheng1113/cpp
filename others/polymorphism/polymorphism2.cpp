// abstract base class
#include <iostream>
using namespace std;

class Polygon {
  protected:
    int width, height;
  public:
    void setValues (int a, int b)
      { width=a; height=b; }
    virtual int area (void) const =0;
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
  // Polygon poly;// can not instaniate abstract base class
  Rectangle rect;
  Triangle trgl;
  Polygon * ppoly1 = &rect;
  Polygon * ppoly2 = &trgl;
  ppoly1->setValues (4,5);
  ppoly2->setValues (4,5);
  cout << ppoly1->area() << '\n';
  cout << ppoly2->area() << '\n';
  return 0;
}
