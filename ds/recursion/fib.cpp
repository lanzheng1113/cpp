// example of Fibonacci series
// just a demo,it can not handle integer out of int range
#include <iostream>
#include <string>
using namespace std;

long long fibi(int n);
long long fibr(int n);

long long g_callCnt = 0;

int main(int argc,char** argv)
{  
   string cmd = string(argv[1]);
   for(int i=2;i < argc;i++)
   {
       int n = std::stoi(argv[i]);
       if(cmd == "-r" || cmd== "-R") 
       {  
          g_callCnt = 0;
          cout<<"Recursion,Fib("<<n<<")="<<fibr(n)<<endl;
          cout<<"\t call function fibr "<<g_callCnt<<" times"<<endl;
       }
       else
       {
          cout<<"Iteration,Fib("<<n<<")="<<fibi(n)<<endl;
       }
   }
}

//using iteration
long long fibi(int n)
{
   if(n < 2)
       return n;
    else
    {
       long long last =0;
       long long cur = 1;
       for(;n > 1;n--)        
       {
           long long tmp = cur;
           cur += last;
           last = tmp;
       }
       return cur;     
    }
}

//using recursion
long long fibr(int n)
{  
   g_callCnt += 1;
   if(n < 2)
       return n;
   return fibr(n-1)+fibr(n-2);    
}
