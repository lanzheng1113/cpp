#include <iostream>
#include <cstring>
using std::cout;
using std::endl;
//���ƹ��캯������2

struct Node
{
	Node(char *n="",int a = 0)
	{  
       name = strdup(n);
       strcpy(name,n);
	   age = a ;
	}
	//���ƹ��캯��
	Node(const Node& node)
	{  
	   name = strdup(node.name);
	   age = node.age;
	}
	//��ֵ������
	Node& operator=(const Node& n)
	{   
		if(this != &n)
		{
			if(name != NULL)
				delete [] name;//�ͷ���ǰ�ռ�
		    name = strdup(n.name);//���·����ڴ�
			age = n.age;
		}
	    return *this;
	}
	//��������
	~Node()
	{
		delete[] name;
	}
	char *name;
	int age;
};
int main()
{
	Node node1("Roger",20),node2(node1),node3("Tom",22);
	//print Roger 20 Roger 20
	cout<<node1.name<<" "<<node1.age<<" "
		<<node2.name<<" "<<node2.age<<endl;
	
	strcpy(node2.name,"Wendy");
	node2.age = 30;
	//print Roger 20 Wendy 30
	cout<<node1.name<<" "<<node1.age<<" "
		<<node2.name<<" "<<node2.age<<endl;

	//��ֵ������
	node2 = node3;
	//print Tom 22 Tom 22
	cout<<node2.name<<" "<<node2.age<<" "
		<<node3.name<<" "<<node3.age<<endl;
    
	return 0;
}
