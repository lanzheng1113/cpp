#include <iostream>
#include "List.h"
#include "CDLL.h"

template<class T>
CDLL<T>::CDLL()
{
    tail = 0;
}

template<class T>
CDLL<T>::~CDLL()
{  
   if(tail != 0)
   {
      DNode<T>* pTmp = tail->next;
	  DNode<T>* pNext = 0;
	  while(pTmp != tail)
	  {
	     pNext = pTmp->next;
		 delete pTmp;
		 pTmp = pNext;
	  }
	  delete tail;
	  tail = 0;
   }
   std::cout<<"Free CDLL space"<<std::endl;
}

template<class T>
void CDLL<T>::addFromHead(const T& data)
{
    if(tail == 0)
	{
	   tail = new DNode<T>(data,0,0);
	   tail->next = tail->prev = tail;
	}else
	{
	   tail->next->prev = new DNode<T>(data,tail,tail->next);
	   tail->next = tail->next->prev;
	}
}

template<class T>
void CDLL<T>::addFromTail(const T& data)
{
	if(tail == 0)
	{
	   tail = new DNode<T>(data,0,0);
	   tail->next = tail->prev = tail;
	}else
	{  
       tail->next = new DNode<T>(data,tail,tail->next);
	   tail = tail->next;
	   tail->next->prev = tail;
	}
}

template<class T>
void CDLL<T>::removeFromHead()
{
    if(tail != 0)
	{
       if(tail == tail->next)
	   {
		   delete tail;
		   tail = 0;
	   }else
	   {  
          DNode<T>* head = tail->next;
		  tail->next = head->next;
		  head->next->prev = tail;
		  delete head;
	   }
	}
}

template<class T>
void CDLL<T>::removeFromTail()
{
    if(tail != 0)
	{
       if(tail == tail->next)
       {
		   delete tail;
		   tail = 0;
	   }else
	   {
           tail->prev->next = tail->next;
		   tail->next->prev = tail->prev;
		   DNode<T>* pTmp = tail->prev;
		   delete tail;
		   tail = pTmp;
	   }
	}
}

template<class T>
void CDLL<T>::remove(const T& data)
{
    if(tail != 0)
	{
       DNode<T>* pTmp = tail->next;
	   while(pTmp != tail && pTmp->data != data)
	         pTmp = pTmp->next;
       if(pTmp != tail)     //match 1..tail-1 node
	   {   
		   pTmp->prev->next = pTmp->next;
		   pTmp->next->prev = pTmp->prev;
           delete pTmp;
	   }else if(tail->data == data)  //match tail node
	   {
		   if(tail == tail->next) //only one node
		   {
               delete tail;
			   tail = 0;
		   }else
		   {
			   tail->prev->next = tail->next;
			   tail->next->prev = tail->prev;
			   DNode<T>* pTmp = tail->prev;
			   delete tail;
		       tail = pTmp;
		   }
	   }
	}
}

template<class T>
bool CDLL<T>::containsOf(const T& data)
{
	if(tail != 0)
	{
	   DNode<T>* pTmp = tail->next;
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
bool CDLL<T>::isEmpty()
{
   return tail == 0;
}

template<class T>
int  CDLL<T>::getSize()
{
   if(tail != 0)
	{
	   int cnt = 1;
	   DNode<T>* pTmp = tail->next;
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
void CDLL<T>::print()
{
	if(tail == 0)
   {
	   std::cout<<"CDLL []"<<std::endl;
   }else
   {
      std::cout<<"CDLL [";
      DNode<T>* pTmp = tail->next;
      while(pTmp != tail)
	  { 
		std::cout<<pTmp->data<<" ";
	    pTmp = pTmp->next;
	  }
      std::cout<<tail->data<<"]"<<std::endl;
   }
}
template<class T>
void CDLL<T>::printInverse()
{
   if(tail == 0)
   {
	   std::cout<<"CDLL []"<<std::endl;
   }else
   {
      std::cout<<"CDLL ["<<tail->data;
      DNode<T>* pTmp = tail->prev;
      while(pTmp != tail)
	  { 
		std::cout<<" "<<pTmp->data;
	    pTmp = pTmp->prev;
	  }
	  std::cout<<"]"<<std::endl;
   }
}
