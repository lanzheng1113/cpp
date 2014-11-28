#include <iostream>
using namespace std;
//流使用举例2-流的状态查询与控制
int main()
{
	int ival,sum = 0;
	while(cin >> ival,!cin.eof())
	{  
	   if(cin.bad())
		 throw runtime_error("IO stream corrupted.");
	   if(cin.fail())
	   {
		   cerr<<"bad data,try agin."<<endl;
	       cin.clear();//清除错误状态
		   //丢弃错误输入，直到遇到行结束符
		   cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		   continue;
	   }
       sum += ival;
	}
	cout<<"sum is:	"<<sum<<endl;
	return 0;
}
