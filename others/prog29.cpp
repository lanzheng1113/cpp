#include <iostream>
using std::cout;
using std::endl;
//Ϊ�˽�ֹ���ƣ��������ʽ�����临�ƹ��캯��Ϊprivate
//Ҫ��ֹ�����Ԫ�ͳ�Ա���ƶ��󣬿��������������帴�ƹ��캯��
class Foo
{
public:
	Foo(int i=0):ival(i){}
    int getVal() const {return ival;}
private:
	Foo(const Foo& orig){ival = orig.ival;};//����Ϊ˽��
private:
	int ival;
};
int main(int argc, char *argv[])
{
	Foo foo1(1);//ok,���ù��캯��
	cout<<foo1.getVal()<<endl;

	Foo foo2;
	foo2 = foo1;//ok,ʹ�úϳɵĸ�ֵ������
	cout<<foo2.getVal()<<endl;

	Foo foo3(foo1);//error,�޷����ø��ƹ��캯��
	cout<<foo3.getVal()<<endl;
	return 0;
}
