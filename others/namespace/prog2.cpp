#include <iostream>

using std::cout;//使用命名空间一个名字
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