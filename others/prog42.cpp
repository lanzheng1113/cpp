#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

using std::vector;
using std::cout;
using std::fill_n;
using std::list;

//�������������
int main()
{   
	int ia[] = {1,5,3,3,4};
	const int array_size = sizeof(ia)/sizeof(*ia);
	vector<int> ivec;
	list<int> ilist(ia,ia+array_size);
	//fill_n(ivec.begin(),10,0);//д��λ�� 0x00000000 ʱ�������ʳ�ͻ
	//fill_n(back_inserter(ivec),10,0);//ok
    copy(ia,ia+array_size,back_inserter(ivec));

	//�滻�����浽Ŀ��λ��
	vector<int> temp;
    replace_copy(ilist.begin(),ilist.end(),
		back_inserter(temp),3,22);
	//���������
    vector<int> temp2;
	copy(ilist.begin(),ilist.end(),
		back_inserter(temp2));
    copy(ilist.begin(),ilist.end(),
		inserter(temp2,temp2.begin()));//��ָ��λ��ʵ�ֲ���ĵ�����
	return 0;
}
