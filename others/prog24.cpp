#include <iostream>
using namespace std;
//��ʹ�þ���2-����״̬��ѯ�����
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
	       cin.clear();//�������״̬
		   //�����������룬ֱ�������н�����
		   cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		   continue;
	   }
       sum += ival;
	}
	cout<<"sum is:	"<<sum<<endl;
	return 0;
}
