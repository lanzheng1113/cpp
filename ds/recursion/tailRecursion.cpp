#include <iostream>
#include <list>
#include <string>
using namespace std;

void printListi(list<int>::iterator itCur,list<int>::iterator end);
void printListr(list<int>::iterator itCur,list<int>::iterator end);

int main(int argc,char** argv)
{  
   list<int> iList;
   for(int i = 0;i < 10 ;i++)
       iList.push_back(i);
   if ( argc == 2 && string(argv[1]) == "-r") 
      printListr(iList.begin(),iList.end());      
   else
      printListi(iList.begin(),iList.end());    
}

//using tail recursion
void printListr(list<int>::iterator itCur,list<int>::iterator end)
{
    if( itCur == end)
    {
      std::cout<<std::endl;  
      return;
    }    
    std::cout<<*itCur++<<" ";
    printListr(itCur,end);//at tail ,call itself
}
//using iteration
void printListi(list<int>::iterator itCur,list<int>::iterator end)
{
    while(itCur != end)
        std::cout<<*itCur++<<" ";
    std::cout<<std::endl;
}

