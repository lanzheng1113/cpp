#include <iostream>
using std::cout;
using std::endl;

//指针参数的举例
void reset(int *ip)
{
   *ip = 0;//重置其指向对象的值为0
   ip = 0;//修改形参局部副本，不影响实参指针
}
int main()
{
	int i = 1024;
	int *p = &i;
	cout<<"i:	"<<*p<<endl;
	reset(p);
	cout<<"i:	"<<*p<<endl;
	return 0;
}
