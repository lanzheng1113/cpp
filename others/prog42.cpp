#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

using std::vector;
using std::cout;
using std::fill_n;
using std::list;

//插入迭代器举例
int main()
{   
	int ia[] = {1,5,3,3,4};
	const int array_size = sizeof(ia)/sizeof(*ia);
	vector<int> ivec;
	list<int> ilist(ia,ia+array_size);
	//fill_n(ivec.begin(),10,0);//写入位置 0x00000000 时发生访问冲突
	//fill_n(back_inserter(ivec),10,0);//ok
    copy(ia,ia+array_size,back_inserter(ivec));

	//替换并保存到目标位置
	vector<int> temp;
    replace_copy(ilist.begin(),ilist.end(),
		back_inserter(temp),3,22);
	//插入迭代器
    vector<int> temp2;
	copy(ilist.begin(),ilist.end(),
		back_inserter(temp2));
    copy(ilist.begin(),ilist.end(),
		inserter(temp2,temp2.begin()));//在指定位置实现插入的迭代器
	return 0;
}
