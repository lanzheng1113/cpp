#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
   std::vector<int> Num_Array;
	
   srand(unsigned(time(NULL)));
	
   for(int x=0; x<1001; x++) Num_Array.push_back(x);

   random_shuffle(Num_Array.begin(), Num_Array.end());

   for(int x=0; x<10; x++) cout << Num_Array[x] << '\t';
   cout<<endl;
   return 0;
}
