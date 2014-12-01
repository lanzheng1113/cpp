#include <iostream>
#include <string>

void reverse1();
void reverse2();
void reverse3();

int main(int argc,char** argv)
{  
   std::cout<< "input somethind:"<<std::endl;
   reverse2();
   std::cout<<std::endl; 
}
//all chars reverse,no newline
void reverse1()
{
   char ch;
   std::cin.get(ch);
   if( ch != '\n')
   {
      reverse1();
      std::cout.put(ch);
   }
}
//with newline at head line,other chars reverse
void reverse2()
{
   char ch;
   std::cin.get(ch);
   if( ch != '\n')
      reverse2();
   std::cout.put(ch);
}
//output only newlines
void reverse3()
{
   static char ch;//note the static
   std::cin.get(ch);
   if( ch != '\n')
      reverse3();
   std::cout.put(ch);
}
