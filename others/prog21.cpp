#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
//����ָ�����

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
//����typedef�򻯺���ָ��Ķ���,�뺯�����޹�
typedef int (*strCmpFcn) (const string &,const string &);
typedef int (*intCmpFcn) (int,int);

int main(int argc, char *argv[])
{   
	void (*greetpf)(const string&) = greet;
	int (*intpf)(int,int) = &compare;//ָ�����غ�����ָ��

	greetpf("Hello!");//���ú���
	cout<<"compare(1,2):	"<<intpf(1,2)<<endl;
	return 0;
}
