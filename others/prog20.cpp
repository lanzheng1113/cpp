#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
//�������õĺ���������ֵ��Ҫע��
class CStu
{   
public:
	CStu(){}
	CStu(string sname,int iage)
			:name(sname),age(iage){}
    string & getName(){return name;}//Ӧ��������const����
private:
	string name;
	int age;
};
int main(int argc, char *argv[])
{
	
	CStu stu("Tom",22);
	cout<<"name:	"<<stu.getName()<<endl;
    stu.getName() = "Jack";//�޸���˽�г�Ա��Υ��ԭ��
	cout<<"name:	"<<stu.getName()<<endl;
	return 0;
}
