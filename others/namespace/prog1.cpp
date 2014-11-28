#include <iostream>
using namespace std;

namespace global {
	int count = 0;//重新定义一个命名空间
}
int increment()
{
    return ++global::count;
}
int main()
{   
	increment();
	cout<<"count=	"<<global::count<<endl;
	return 0;
}