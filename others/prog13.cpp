#include <iostream>
//static_castʹ�þ���
using std::cout;

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
	double dval = 97.0;
	
	char ch = static_cast<char>(dval);//��������������Ϊ
	cout<<ch<<"\n";

	Dummy d;
	//��ʾ�������ͨ���������������й�
    Addition * padd = static_cast<Addition*>(&d);
    cout << padd->result();

	return 0;
}
