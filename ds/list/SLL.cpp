#include <iostream>
#include "SLL.h"
template <class T>
SLL<T>::SLL()
{
  head = tail = 0;
}
template <class T>
SLL<T>::~SLL()
{
   SNode<T>* pTmp = head;
   SNode<T>* pNext = 0;
   while(pTmp != 0)
   {
       pNext = pTmp->next;
	   delete pTmp;
	   pTmp = pNext;
   }
   head = tail = 0;
   std::cout<<"Free SLL space"<<std::endl;
}
template <class T>
void SLL<T>::addFromHead(const T& data)
{  
   head = new SNode<T>(data,head);
   if(tail == 0)
	  tail = head;
}
template <class T>
void SLL<T>::addFromTail(const T& data)
{
   if(head == 0)
   {
	   tail = new SNode<T>(data);
	   head = tail;
   }else
   {
	   tail->next = new SNode<T>(data);
	   tail = tail->next;
   }
}
template <class T>
void SLL<T>::removeFromHead()
{
    if(head != 0) //if not empty,remove
	{
	   if(head == tail) //only one node
	   {
		  delete head;
		  tail = head = 0;
	   }else
	   {
	        SNode<T>* pTmp = head->next;
			delete head;
			head = pTmp;
	   }
	}
}
template <class T>
void SLL<T>::removeFromTail()
{
	if(head != 0)  //if not empty,remove
	{
	    if(head == tail) //only one node
		{
		   delete tail;
		   head = tail = 0;
		}else
		{
		   SNode<T>* prior = head;
		   while(prior->next != tail)
		         prior = prior->next;
		   delete tail;
		   prior->next = 0;
		   tail = prior;
		}
	}
}
template <class T>
void SLL<T>::remove(const T& data)
{ 
  if(head == 0)
	  return;
  if(head->data == data) 
  {
	 removeFromHead();//delete head node
  }else
  {
	   SNode<T>* prior = head;
	   while(prior->next != 0 && prior->next->data != data)
			 prior = prior->next;
	   if(prior->next != 0)
	   {
		  SNode<T>* pRmove = prior->next;
		  prior->next = pRmove->next;
		  if(pRmove->next == 0)
			  tail = prior;//if remove last node,reset the tail
		  delete pRmove; //delete middle node
	   }
  }
}
template <class T>
bool SLL<T>::containsOf(const T& data)
{
   SNode<T>* pTmp = head;
   while(pTmp != 0 && pTmp->data != data)
	     pTmp = pTmp->next;
   return pTmp != 0;
}
template <class T>
bool SLL<T>::isEmpty()
{
	return head == 0;
}
template <class T>
int  SLL<T>::getSize()
{  
   int cnt = 0;
   SNode<T>* pTmp = head;
   while(pTmp != 0)
	{  
	   cnt++;
	   pTmp = pTmp->next;
	}
   return cnt;
}
//for testing
template <class T>
void SLL<T>::print()
{
  std::cout<<"SLL [";
  SNode<T>* pTmp = head;
  while(pTmp != 0)
  { 
	std::cout<<pTmp->data<<" ";
	pTmp = pTmp->next;
  }
  std::cout<<"]"<<std::endl;
}
