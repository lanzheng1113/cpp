#include <iostream>
using std::cout;

//��ʽ����ת����������ʱ�������δ֪���

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
  padd = (Addition*) &d;//ǿ������ת��
  cout << padd->result();
  return 0;
}
