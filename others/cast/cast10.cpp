// this example show paramaters matching process
// note SmallInt is a bad design
// from: <c++ primer 4th edtion>

#include <iostream>
using namespace std;
class SmallInt {
public:
    SmallInt(int x=0):val(x){ cout << "int ctor" << endl; }
    SmallInt(double x):val(x){ cout << "double ctor" << endl;}
    operator int() const { cout << "int conversion " << endl;return val;}
    operator double() const { cout << "double conversion" << endl; return val;}
private:
    std::size_t val;
};

void compute(int x){}
void fp_compute(double x){}
void extended_compute(long double x){}
void manip(const SmallInt& x){}

int main() {
  SmallInt si;
  compute(si); // using SmallInt::operator int() const
  fp_compute(si); // using SmallInt::operator double() const
  //extended_compute(si); // error: ambiguous
  
  double d;
  int i;
  long l;
  manip(d); // using SmallInt(double) ctor
  manip(i); // using SmallInt(int) ctor
  //manip(l); // error: ambiguous
    
  return 0;
}
