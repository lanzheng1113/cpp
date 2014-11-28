#include <iostream>
using namespace std;

int count = 0;
int increment()
{
    return ++count;// error, identifier count is ambiguous
}
int main()
{   
	increment();
	cout<<"count=	"<<count<<endl;
	return 0;
}
