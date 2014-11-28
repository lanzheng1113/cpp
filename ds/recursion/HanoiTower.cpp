// example of Hanoi Tower
#include <iostream>
#include <string>
#include <stack>

using namespace std;

void hanoiRecursion(int n,char src,char mid,char target);
void hanoiIteration(int n);
int  g_stepCnt = 0;

int main(int argc,char** argv)
{
   if ( argc < 3) 
   {
       cout << "usage example: \t -r 5 //using recursion  \n\t\t -i 5 //using iteration"<<endl;
       return 0;
   }
   int n = std::stoi(argv[2]);
   if ( n <= 0) return 0;
   cout<<"Tower Of Hanoi with "<<n<<" stack:"<<endl;
   if (string(argv[1]) == "-r" || string(argv[1]) == "-R")
       hanoiRecursion(n,'X','Y','Z');
   else
       hanoiIteration(n);
   cout<<"Moved:"<<g_stepCnt<<" steps."<<endl;
   return 0;
}

// using recursion
void hanoiRecursion(int n,char src,char mid,char target)
{   
    if(n == 0)
    {
      return; // do nothing
    }
    hanoiRecursion(n-1,src,target,mid); // move the up n-1 stack to mid    
    ++g_stepCnt;
    cout<<"("<<n<<","<<src<<"-->"<<target<<")"<<endl;// move the n-th stack to target
    hanoiRecursion(n-1,mid,src,target);// move the up n-1 stack from mid to target
}
// using iteration
// if n odd then final post is 1,else is 2
void hanoiIteration(int n)
{
   stack<int> dStack[3];
   
   if (n <= 0) return;
   
   // put n disk at stack 0
   for(int i = n;i > 0;i--)    
     dStack[0].push(i);
   int lastItem = -1; //record last moved disk

   while(!dStack[0].empty() || !dStack[n%2+1].empty()) 
   {
      //pick the smallest and not the last moved disk to move
      int stackNum = 0,moveItem = n+1;
      for(int i = 0;i < 3;i++)
      {
         if(dStack[i].empty() || dStack[i].top() == lastItem)
             continue;
         if(dStack[i].top() < moveItem) 
         {
             stackNum = i;
             moveItem = dStack[i].top();
         }
      }
      lastItem = moveItem;
      ++g_stepCnt;
      //move odd-numbered disk clockwise ,move even-numbered disk counter-clockwise
      int target = (moveItem % 2 == 0 )?(stackNum+2)%3:(stackNum+1)%3;
      cout<<"("<<moveItem<<","<<stackNum<<"-->"<<target<<")"<<endl;
      dStack[target].push(moveItem);
      dStack[stackNum].pop();
   }
}

