#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
//函数指针举例

void greet(const string &str)
{
   cout<<"greeting:	"<<str<<endl;
}
int compare(const string &s1,const string &s2)
{
   return s1.compare(s2);
}
int compare(int ival1,int ival2)
{
    return ival1-ival2;
}
//利用typedef简化函数指针的定义,与函数名无关
typedef int (*strCmpFcn) (const string &,const string &);
typedef int (*intCmpFcn) (int,int);

int main(int argc, char *argv[])
{   
	void (*greetpf)(const string&) = greet;
	int (*intpf)(int,int) = &compare;//指向重载函数的指针

	greetpf("Hello!");//调用函数
	cout<<"compare(1,2):	"<<intpf(1,2)<<endl;
	return 0;
}
