int main()
{  
   //dereference a null pointer,can cause segmentation fault
   int *p = 0;
   *p = 1;
   return 0;
}
