#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
//sizeof操作
int main()
{
	typedef struct student
	{
		char	name[20];
		int	age;
	}stru_stu;
	stru_stu stu1;
	stru_stu &refStu = stu1;
	stru_stu stu_array[2];
	stru_stu *pstu = &stu1;
	cout<<"sizeof(stru_stu):	"<<sizeof(stru_stu)<<endl;//作用于类型名
    cout<<"sizeof(stu1):	"<<sizeof(stu1)<<endl;//作用于对象
	cout<<"sizeof(refStu):	"<<sizeof(refStu)<<endl;//作用于引用类型
	cout<<"sizeof(pstu):	"<<sizeof(pstu)<<endl;//作用于指针
	cout<<"sizeof(*pstu):	"<<sizeof(*pstu)<<endl;//作用于指针的解引用
	cout<<"sizeof(stu_array):	"<<sizeof(stu_array)<<endl;//作用于数组
	cout<<"sizeof(stu_array)/sizeof(stru_stu):	"
		<<sizeof(stu_array)/sizeof(stru_stu)<<endl;//计算数组元素个数
	return 0;
}
