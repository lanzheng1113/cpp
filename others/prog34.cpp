#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
//������ʧЧ����-����洢end�������صĵ�����
int main()
{
	vector<int>	ivec;
	ivec.push_back(3);
	ivec.push_back(5);
	ivec.push_back(7);
	vector<int>::iterator end = ivec.end();
    
	for(vector<int>::iterator first = ivec.begin();first != end;++first)
		cout<<*first<<endl;
	
	ivec.insert(ivec.begin(),1);
	//cause fatal error
	for(vector<int>::iterator first = ivec.begin();first != end;++first)
		cout<<*first<<endl;
	return 0;
}
