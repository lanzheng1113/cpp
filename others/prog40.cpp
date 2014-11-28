#include <iostream>
#include <string>
#include <utility>
#include <map>

using std::string;
using std::make_pair;
using std::pair;
using std::multimap;
using std::cout;
using std::endl;

int main()
{
	multimap<string,string> authors;
	typedef multimap<string,string>::size_type sz_type;
	typedef multimap<string,string>::iterator authors_it;
	authors.insert(make_pair(
		string("Barth,John"),
		string("Sot-weed Factor")
		));
	authors.insert(make_pair(
		string("Barth,John"),
		string("Lost in the Funhouse")
		));
	string delete_item("Kazuo Ishiguro");
	//删除指定键绑定的元素，并返回删除元素个数
	sz_type cnt = authors.erase(delete_item);
	cout << "erase:	" << cnt << endl;
	//查找元素方式1
	//count求出某键出现的次数
	string search_item("Barth,John");
	sz_type entries = authors.count(search_item);
	cout << "find:	" << entries << endl;
	//find操作返回一个迭代器，指向第一个拥有正在查找的键的实例
	authors_it iter = authors.find(search_item);
	for(sz_type cnt = 0;cnt != entries;++cnt,++iter)
		cout << iter->second << endl;
    
	//查找元素方式2
    authors_it beg = authors.lower_bound(search_item);
	authors_it end = authors.upper_bound(search_item);
	while(beg != end)
	{
		cout<< beg->second << endl;
		++beg;
	}
    //查找元素方式3
	pair<authors_it,authors_it> pos =
					authors.equal_range(search_item);
	while(pos.first != pos.second)
	{
		cout<<pos.first->second<< endl;
	    ++pos.first;
	}
	return 0;
}
