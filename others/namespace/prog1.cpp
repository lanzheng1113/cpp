#include <iostream>
using namespace std;

namespace global {
	int count = 0;//���¶���һ�������ռ�
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