#include <iostream>
#include "List.h"
#include "CSLL.h"
template<class T>
CSLL<T>::CSLL()
{
    tail = 0;
}
template<class T>
CSLL<T>::~CSLL()
{
   if(tail != 0)
   {
      SNode<T>* pTmp = tail->next;
	  SNode<T>* pNext = 0;
	  while(pTmp != tail)
	  {
	     pNext = pTmp->next;
		 delete pTmp;
		 pTmp = pNext;
	  }
	  delete tail;
	  tail = 0;
   }
   std::cout<<"Free CSLL space"<<std::endl;
}
template<class T>
void CSLL<T>::addFromHead(const T& data)
{
    if(tail == 0)
	{
	    tail = new SNode<T>(data);
        tail->next = tail;
	}else
	{
	   tail->next = new SNode<T>(data,tail->next);
	}
}
template<class T>
void CSLL<T>::addFromTail(const T& data)
{
	if(tail == 0)
	{
	    tail = new SNode<T>(data);
        tail->next = tail;
	}else
	{   
		tail->next = new SNode<T>(data,tail->next);
		tail = tail->next;
	}
}
template<class T>
void CSLL<T>::removeFromHead()
{
   if(tail == tail->next) //only one node
   {
      delete tail;
	  tail = 0;
   }else
   {
      SNode<T>* head = tail->next;
	  tail->next = head->next;
	  delete head;
   }
}
template<class T>
void CSLL<T>::removeFromTail()
{  
   if(tail != 0 )
   {
	  if(tail == tail->next) //only one node
	   {
		  delete tail;
		  tail = 0;
	   }else    //more than one node
	   {
		   SNode<T>* prior = tail->next;
		   while(prior->next != tail)
				 prior = prior->next;
		   prior->next = tail->next;
		   delete tail;
		   tail = prior;
	   }
   }
}
template<class T>
void CSLL<T>::remove(const T& data)
{
    if(tail != 0)
	{  
	   SNode<T> *prior=tail,*pRemove = tail->next;
	   while(pRemove != tail && pRemove->data != data)
	   {
		   prior = prior->next;
		   pRemove = pRemove->next;
	   }
	   if(pRemove != tail )
	   {
		  prior->next = pRemove->next;
		  delete pRemove;
	   }else if(tail->data == data)
	   {   
		   if(tail->next == tail) //only one node
		   {
		      delete tail;
			  tail = 0;
		   }else
		   {
		      prior->next = tail->next;
		      delete tail;
		      tail = prior;
		   }
	   }
	}
}
template<class T>
bool CSLL<T>::containsOf(const T& data)
{
    if(tail != 0)
	{
	   SNode<T>* pTmp = tail->next;
	   while(pTmp != tail && pTmp->data != data)
			pTmp = pTmp->next;
	   if(pTmp != tail)
		   return true;
	   else
		   return tail->data == data;
	}
	return false;
}
template<class T>
bool CSLL<T>::isEmpty()
{
   return tail == 0;
}
template<class T>
int  CSLL<T>::getSize()
{
   if(tail != 0)
	{
	   int cnt = 1;
	   SNode<T>* pTmp = tail->next;
	   while(pTmp != tail)
	   {
		  cnt++;
		  pTmp = pTmp->next;
	   }
	   return cnt;
	}
    return 0;
}
template<class T>
void CSLL<T>::print()
{
   if(tail == 0)
   {
	   std::cout<<"CSLL []"<<std::endl;
   }else
   {
      std::cout<<"CSLL [";
      SNode<T>* pTmp = tail->next;
      while(pTmp != tail)
	  { 
		std::cout<<pTmp->data<<" ";
	    pTmp = pTmp->next;
	  }
      std::cout<<tail->data<<"]"<<std::endl;
   }
}
