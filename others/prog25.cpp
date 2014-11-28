#include <iostream>
#include <sstream>
using namespace std;
//流的使用4-字符串流的格式化
int main()
{
	int ival = 1024;
	double dval = 3.14;
	ostringstream format_message;
	//写入到字符串流
	format_message<<"ival:	"<<ival<<"\n"
				  <<"dval:	"<<dval<<"\n";
	istringstream input_string(format_message.str());	
	string dump;
	//从字符串流抽取数据
	input_string>>dump>>ival>>dump>>dval;//注意读取和忽略无关的字符
	cout<<"ival:	"<<ival<<"	dval:	"<<dval<<endl;
	return 0;
}
