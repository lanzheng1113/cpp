#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
//复制构造函数举例1
class SomeData {
public:
	SomeData(string name,int ival=0)
	{ 
		pi = new int(ival) ;
		id=name;
		cout << "Constructor for " << id << endl;
	}
	~SomeData() 
	{
     cout << "Destructor for " << id << endl;
     delete pi;
	}
public:
	int * pi;
    string id;
};
int main()
{
	SomeData data1("ID1",3),data2(data1);
	cout<<data1.id<<" "<<*data1.pi<<" "
		<<data2.id<<" "<<*data2.pi<<endl;
    *data2.pi = 5;
	cout<<data1.id<<" "<<*data1.pi<<" "
		<<data2.id<<" "<<*data2.pi<<endl;
	return 0;
}
