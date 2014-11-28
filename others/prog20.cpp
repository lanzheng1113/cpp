#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
//返回引用的函数返回左值需要注意
class CStu
{   
public:
	CStu(){}
	CStu(string sname,int iage)
			:name(sname),age(iage){}
    string & getName(){return name;}//应声明返回const引用
private:
	string name;
	int age;
};
int main(int argc, char *argv[])
{
	
	CStu stu("Tom",22);
	cout<<"name:	"<<stu.getName()<<endl;
    stu.getName() = "Jack";//修改了私有成员，违背原意
	cout<<"name:	"<<stu.getName()<<endl;
	return 0;
}
