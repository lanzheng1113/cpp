#include <iostream>
#include <cstring>
using std::cout;
using std::endl;
//���ƹ��캯������1
//��������ָ���Ա��û�и��ƹ��캯������

struct Node
{
	Node(char *n="",int a = 0)
	{  
       name = strdup(n);
       strcpy(name,n);
	   age = a ;
	}
	~Node()
	{   
		delete[] name;
	}
	char *name;
	int age;
};
int main()
{
	Node node1("Roger",20),node2(node1);
	//print Roger 20 Roger 20
	cout<<node1.name<<" "<<node1.age<<" "
		<<node2.name<<" "<<node2.age<<endl;

	strcpy(node2.name,"Wendy");
	node2.age = 30;
	//print Wendy 20 Wendy 30
	cout<<node1.name<<" "<<node1.age<<" "
		<<node2.name<<" "<<node2.age<<endl;
}

