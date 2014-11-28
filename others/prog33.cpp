#include <iostream>
#include <vector>
#include <list>
#include <string>
using std::string;
using std::vector;
using std::list;
using std::cout;
//容器初始化举例
int main()
{
	vector<int>	ivec;//使用默认构造函数
	vector<int>	ivec2(ivec);//初始化为同型容器的副本
	//list<int>	ilist(ivec);//错误，容器类型不同
	//vector<double>	dvec(ivec);//错误，容器元素类型不同
    list<int>   ilist(ivec.begin(),ivec.end());
	vector<double>	dvec(ivec.begin(),ivec.end());

	char *words[] = {"Red","Blue","Yellow"};
	std::size_t words_size = sizeof(words)/sizeof(char *);
	list<string> words2(words,words+words_size);
	
	return 0;
}
