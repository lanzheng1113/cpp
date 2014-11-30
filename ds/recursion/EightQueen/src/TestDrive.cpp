#include <iostream>
#include <string>
#include "queen.h"

int main(int argc,char** argv)
{
	int n = -1;
	if (argc == 2)
	{
		n = std::stoi (std::string(argv[1]));
	}
	else
	{
		std::cout << "Please input how many row you take?"<<std::endl;
		std::cin >> n;
	}
    Queen queen(n);
    queen.putQueen(0);
    std::cout<<"Find: "<<queen.getHowMany()<<" Solutions"<<std::endl;
}
