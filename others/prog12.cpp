#include <iostream>
using std::cout;

//旧式类型转换引起运行时错误或者未知结果

class Dummy {
    double i,j;
};

class Addition {
    int x,y;
  public:
    Addition (int a, int b) { x=a; y=b; }
    int result() { return x+y;}
};

int main()
{
  Dummy d;
  Addition * padd;
  padd = (Addition*) &d;//强制类型转换
  cout << padd->result();
  return 0;
}
