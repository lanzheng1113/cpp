#include <iostream>
#include <cctype>
#include <string>
#include <vector>

using std::string;
using std::vector;

//下标方式遍历容器
int main(int argc, char *argv[])
{
	string str("The quick fox jump over the lazy dog!");
	const size_t array_size = 10;
	int ia[array_size];
	vector<int> ivec;
	//下标操作
	for(string::size_type index = 0;index != str.size();++index)
		if(islower(str[index]))
			str[index] = toupper(str[index]);//转换为大写字母

	for(size_t ix = 0;ix != array_size;++ix)
		ia[ix] = ix;

	for(vector<int>::size_type ix = 0;ix != array_size;++ix )
		ivec.push_back(ia[ix]);

	//迭代器操作
	for ( std::string::iterator it = str.begin(); it != str.end(); ++it)
		std::cout << *it;
	std::cout<<std::endl;
	for(vector<int>::iterator it = ivec.begin();it != ivec.end();++it)
		std::cout << *it<<" ";
	
	//指针操作
	std::cout<<std::endl;
	for(int *pbegin =ia,*pend = ia+array_size;pbegin != pend;++pbegin )
		std::cout << *pbegin<<" ";

	return 0;
}
