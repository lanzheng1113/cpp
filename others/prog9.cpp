#include <iostream>
#include <cctype>
#include <string>
#include <vector>

using std::string;
using std::vector;

//�±귽ʽ��������
int main(int argc, char *argv[])
{
	string str("The quick fox jump over the lazy dog!");
	const size_t array_size = 10;
	int ia[array_size];
	vector<int> ivec;
	//�±����
	for(string::size_type index = 0;index != str.size();++index)
		if(islower(str[index]))
			str[index] = toupper(str[index]);//ת��Ϊ��д��ĸ

	for(size_t ix = 0;ix != array_size;++ix)
		ia[ix] = ix;

	for(vector<int>::size_type ix = 0;ix != array_size;++ix )
		ivec.push_back(ia[ix]);

	//����������
	for ( std::string::iterator it = str.begin(); it != str.end(); ++it)
		std::cout << *it;
	std::cout<<std::endl;
	for(vector<int>::iterator it = ivec.begin();it != ivec.end();++it)
		std::cout << *it<<" ";
	
	//ָ�����
	std::cout<<std::endl;
	for(int *pbegin =ia,*pend = ia+array_size;pbegin != pend;++pbegin )
		std::cout << *pbegin<<" ";

	return 0;
}
