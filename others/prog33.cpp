#include <iostream>
#include <vector>
#include <list>
#include <string>
using std::string;
using std::vector;
using std::list;
using std::cout;
//������ʼ������
int main()
{
	vector<int>	ivec;//ʹ��Ĭ�Ϲ��캯��
	vector<int>	ivec2(ivec);//��ʼ��Ϊͬ�������ĸ���
	//list<int>	ilist(ivec);//�����������Ͳ�ͬ
	//vector<double>	dvec(ivec);//��������Ԫ�����Ͳ�ͬ
    list<int>   ilist(ivec.begin(),ivec.end());
	vector<double>	dvec(ivec.begin(),ivec.end());

	char *words[] = {"Red","Blue","Yellow"};
	std::size_t words_size = sizeof(words)/sizeof(char *);
	list<string> words2(words,words+words_size);
	
	return 0;
}
