#include <stdio.h>
#include <vector>
using namespace std;

//˳����������
class Foo
{
public:
	Foo(int i):ival(i){}
private:
	int ival;
};
int main(int argc, char *argv[])
{
	vector<Foo> empty;
	vector<Foo> bad(10);//����û�к��ʵ�Ĭ�Ϲ��캯��
	vector<Foo> ok(10,1);
	return 0;
}
