#include <iostream>
using std::cout;
using std::endl;

//ָ������ľ���
void reset(int *ip)
{
   *ip = 0;//������ָ������ֵΪ0
   ip = 0;//�޸��βξֲ���������Ӱ��ʵ��ָ��
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
