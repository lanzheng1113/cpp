// 例子来自: c++ primer 4th edition
#include <iostream>
using namespace std;

class Integral;

class SmallInt {
public:
  SmallInt(){}
  SmallInt(Integral);  // convert from Integral to SmallInt
  // ...
};

class Integral {
public:
  operator SmallInt() const { cout << "Integral oper" << endl; return SmallInt();} // convert from Integral to SmallInt
};

SmallInt::SmallInt(Integral x) {cout << "SmallInt ctor" << endl;}

void compute(SmallInt x){} 

int main() {
   Integral int_val;
   compute(int_val); 
   return 0;
}


