#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using std::vector;
using std::list;
using std::cout;
using std::endl;
using std::find;

//泛型算法举例1-算法基于迭代器实现与具体的容器类型无关
int main()
{   
	int ia[] = {1,7,5,3,11,2,4,8,6};
	int search_value = 4;
    const int array_size = sizeof(ia)/sizeof(*ia);

	vector<int> ivec(ia,ia+array_size);
	list<int> ilist(ia,ia+array_size);
    //find in array
	int *result = find(ia,ia+array_size,search_value);
	cout << "In array the value " << search_value
		 << ( result == ia+array_size ? " is not present": " is present") << endl;
	//find in vector
	vector<int>::const_iterator vecIt = find(
			ivec.begin(),ivec.end(),search_value);
    cout << "In vector the value " << search_value
		 << ( vecIt == ivec.end() ? " is not present": " is present") << endl;
	//find in list
	list<int>::const_iterator listIt = find(
		ilist.begin(),ilist.end(),search_value);
    cout << "In list the value " << search_value 
		 << ( listIt == ilist.end() ? " is not present": " is present") << endl;
    
	return 0;
}
