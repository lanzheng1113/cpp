#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
//sizeof����
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
	cout<<"sizeof(stru_stu):	"<<sizeof(stru_stu)<<endl;//������������
    cout<<"sizeof(stu1):	"<<sizeof(stu1)<<endl;//�����ڶ���
	cout<<"sizeof(refStu):	"<<sizeof(refStu)<<endl;//��������������
	cout<<"sizeof(pstu):	"<<sizeof(pstu)<<endl;//������ָ��
	cout<<"sizeof(*pstu):	"<<sizeof(*pstu)<<endl;//������ָ��Ľ�����
	cout<<"sizeof(stu_array):	"<<sizeof(stu_array)<<endl;//����������
	cout<<"sizeof(stu_array)/sizeof(stru_stu):	"
		<<sizeof(stu_array)/sizeof(stru_stu)<<endl;//��������Ԫ�ظ���
	return 0;
}
