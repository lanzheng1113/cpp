//const��Ա��ʼ��
#include <iostream>
using std::cout;
class ConstInit {
public:
	ConstInit(int i=0):ival(i),cival(i),rival(i){}
private:
	int ival;
    const int cival;
	int &rival;
	//ֻҪ��ʼ�����ʽ��һ�������������ٶ������н��г�ʼ��
    static const int period = 30;
public:
	static const unsigned int ARRAY[3];//��̬��������
};
const unsigned int ConstInit::ARRAY[3] = {1,3,5};
int main(int argc, char *argv[])
{
	ConstInit ci;
	cout<<ConstInit::ARRAY[1];
}
