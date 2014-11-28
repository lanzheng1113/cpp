//const成员初始化
#include <iostream>
using std::cout;
class ConstInit {
public:
	ConstInit(int i=0):ival(i),cival(i),rival(i){}
private:
	int ival;
    const int cival;
	int &rival;
	//只要初始化表达式是一个常量，可以再定义体中进行初始化
    static const int period = 30;
public:
	static const unsigned int ARRAY[3];//静态常量数组
};
const unsigned int ConstInit::ARRAY[3] = {1,3,5};
int main(int argc, char *argv[])
{
	ConstInit ci;
	cout<<ConstInit::ARRAY[1];
}
