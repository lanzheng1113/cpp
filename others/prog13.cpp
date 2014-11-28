#include <iostream>
//static_cast使用举例
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
	
	char ch = static_cast<char>(dval);//表面这是有意所为
	cout<<ch<<"\n";

	Dummy d;
	//提示错误或者通过，与具体编译器有关
    Addition * padd = static_cast<Addition*>(&d);
    cout << padd->result();

	return 0;
}
