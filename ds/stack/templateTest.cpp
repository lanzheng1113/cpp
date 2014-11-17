// template_default_arg.cpp
// compile with: /EHsc
#include <iostream>
using namespace std;

template <class T,int size = 10> class Array
{
   T* array;
public:
   Array()
   {
      array = new T[size];
      memset(array, 0, size * sizeof(T));
   }
   T& operator[](int i)
   {
      return *(array + i);
   }
   const int Length() { return size; }
   void print()
   {
      for (int i = 0; i < size; i++)
      {
         cout << (*this)[i] << " ";
      }
      cout << endl;
   }
};

int main()
{
   // Explicitly specify the template arguments:
   Array<char, 26> ac;
   for (int i = 0; i < ac.Length(); i++)
   {
      ac[i] = 'A' + i;
   }
   ac.print();
   
   // Accept the default template arguments:
   Array<int> a; // You must include the angle brackets.
   for (int i = 0; i < a.Length(); i++)
   {
      a[i] = i*10;
   }
   a.print();
   std::cout<<a.Length()<<std::endl;
}