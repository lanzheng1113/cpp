#include <iostream>
#include <map>
#include <utility>
#include <string>
//mapʹ�þ���
//mapʹ��ʱע���
// 1)�����ͱ��붨��<���������Ҹò�������ȷ�ع���
// 2)map�±����ʱ����������ӵ�����
int main()
{
	std::map<std::string,int> prog;
	//���뷽��
	prog["c"] = 400;
    prog["c++"] = 500;
	prog.insert(std::make_pair("c#",600));
	typedef std::map<std::string,int>::value_type valType;
	prog.insert(valType("java",800));
    
	//iterator
	std::map<std::string,int>::iterator map_it = prog.begin();
	std::cout<<map_it->first<<" "
			 <<map_it->second<<std::endl;

    //ʹ��insert����ֵ
	std::pair<std::map<std::string,int>::iterator,bool> ret = 
		 prog.insert(std::make_pair("python",700));
	if(ret.second)
		std::cout<<++ret.first->second<<std::endl;

    //count
	std::cout<<prog.count("c++")<<std::endl;
	//find
	std::map<std::string,int>::iterator it = prog.find("java");
	if(it != prog.end())
		std::cout<<it->first<<" "<<it->second<<std::endl;
	return 0;
}
