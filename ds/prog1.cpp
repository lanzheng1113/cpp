//求数组中最长升序子数组的长度
#include <iostream>
using namespace std;

int getMaxLength1(int* a,int n);
int getMaxLength2(int* a,int n);
int getMaxLength3(int* a,int n);
int main()
{
   int array[] ={1,8,1,2,5,0,11,12};
   //int array[] = {1,3,2,0,1,4,3,2,5,6,7,8,1};
   //int array[] = {1,3,2,1,4,5,2,5};
   //int array[] = {1,2,3,4,5,6,7,5,4};
   //int array[] = {7,6,5,4,3,2,1};
   cout<<"Max sub array length:"<<getMaxLength3(array,
	   sizeof(array)/sizeof(*array))<<endl;
}


int getMaxLength3(int* a,int n)
{  
   int len = 1;
   for(int i=0,j=0;i< n-1 && len < n-i;i = j+1)
   {
      for(j = i;j+1 < n && a[j+1] > a[j];j++);
	  if(j-i+1 > len)
		  len = j-i+1;
      cout<<"has a length= "<<j-i+1<<endl;
   }
   return len;
}
int getMaxLength2(int* a,int n)
{
   int len = 1;
   for(int i=0,j=0;i< n-1 && len < n-i;i++)
   {
      for(j = i;j+1 < n && a[j+1] > a[j];j++);
	  if(j-i+1 > len)
		  len = j-i+1;
      cout<<"has a length= "<<j-i+1<<endl;
   }
   return len;
}
int getMaxLength1(int* a,int n)
{
   int len = 1;
   for(int i=0,j=0;i< n-1;i++)
   {
      for(j = i;j+1 < n && a[j+1] > a[j];j++);
	  if(j-i+1 > len)
		  len = j-i+1;
      cout<<"has a length= "<<j-i+1<<endl;
   }
   return len;
}