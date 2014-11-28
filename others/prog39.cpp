#include <iostream>
#include <map>
#include <utility>
#include <string>
//map使用举例
//map使用时注意点
// 1)键类型必须定义<操作符并且该操作能正确地工作
// 2)map下标访问时不存在则添加的特性
int main()
{
	std::map<std::string,int> prog;
	//插入方法
	prog["c"] = 400;
    prog["c++"] = 500;
	prog.insert(std::make_pair("c#",600));
	typedef std::map<std::string,int>::value_type valType;
	prog.insert(valType("java",800));
    
	//iterator
	std::map<std::string,int>::iterator map_it = prog.begin();
	std::cout<<map_it->first<<" "
			 <<map_it->second<<std::endl;

    //使用insert返回值
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
