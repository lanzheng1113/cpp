#include <iostream>

using std::cout;//ʹ�������ռ�һ������
using std::endl;

int count = 0;
int increment()
{
    return ++count;
}
int main()
{   
	increment();
	cout<<"count=	"<<count<<endl;
	return 0;
}