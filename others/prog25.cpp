#include <iostream>
#include <sstream>
using namespace std;
//����ʹ��4-�ַ������ĸ�ʽ��
int main()
{
	int ival = 1024;
	double dval = 3.14;
	ostringstream format_message;
	//д�뵽�ַ�����
	format_message<<"ival:	"<<ival<<"\n"
				  <<"dval:	"<<dval<<"\n";
	istringstream input_string(format_message.str());	
	string dump;
	//���ַ�������ȡ����
	input_string>>dump>>ival>>dump>>dval;//ע���ȡ�ͺ����޹ص��ַ�
	cout<<"ival:	"<<ival<<"	dval:	"<<dval<<endl;
	return 0;
}
