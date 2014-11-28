#include <iostream>
#include <string>
#include <utility>
//pairÊ¹ÓÃ¾ÙÀı
int main()
{
	typedef std::pair<std::string,std::string> Author;
	std::string first,second;
	Author next_auth;
	while(std::cin>>first>>second)
	{
	   next_auth = std::make_pair(first,second);
	   std::cout<<"First Author:	"<<next_auth.first
				<<"	Second Author:	"<<next_auth.second<<std::endl;
	}
	return 0;
}
