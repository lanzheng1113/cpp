#include <stdio.h>
#include <vector>
using namespace std;

//顺序容器举例
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
	vector<Foo> bad(10);//出错，没有合适的默认构造函数
	vector<Foo> ok(10,1);
	return 0;
}
