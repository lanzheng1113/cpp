#include <iostream>
using std::cout;
using std::endl;
//为了禁止复制，类必须显式声明其复制构造函数为private
//要禁止类的友元和成员复制对象，可以声明但不定义复制构造函数
class Foo
{
public:
	Foo(int i=0):ival(i){}
    int getVal() const {return ival;}
private:
	Foo(const Foo& orig){ival = orig.ival;};//声明为私有
private:
	int ival;
};
int main(int argc, char *argv[])
{
	Foo foo1(1);//ok,调用构造函数
	cout<<foo1.getVal()<<endl;

	Foo foo2;
	foo2 = foo1;//ok,使用合成的赋值操作符
	cout<<foo2.getVal()<<endl;

	Foo foo3(foo1);//error,无法调用复制构造函数
	cout<<foo3.getVal()<<endl;
	return 0;
}
